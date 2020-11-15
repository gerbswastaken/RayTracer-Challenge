#include "Point.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Constants.h"

#include "Ray.h"
#include "Sphere.h"
#include "PointLight.h"
#include "World.h"
#include "Camera.h"

#include "Intersection.h"
#include "IntersectionComputations.h"

#include "Hitable.h"
#include "TestObject.h"

#include "PPMWriter.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <functional>

Ray getRayForPixel(int xPixel, int yPixel, const Camera& camera) {
	//The x and y offset values that point to the point in space that represents the center of the pixel we want to draw a ray to
	//The 0.5f gives us the center of that pixel. Without the 0.5f, we would get the top left corner, which might look weird
	float xOffset = (0.5f + xPixel) * camera.getCameraPixelSize();
	float yOffset = (0.5f + yPixel) * camera.getCameraPixelSize();

	// This gives the position of the pixel in world space
	float worldX = camera.m_cameraHalfWidth - xOffset;
	float worldY = camera.m_cameraHalfHeight - yOffset;
	float worldZ = -1.0f; //This is true for the camera; the distance between the camera and the plane is 1 unit

	Point pixel = (camera.m_transformationMatrix.getInverseMatrix()) * Point(worldX, worldY, worldZ);
	Point origin = (camera.m_transformationMatrix.getInverseMatrix()) * Point(0.0f, 0.0f, 0.0f);	//The origin in the standard position of the camera
	Vector direction = ((Vector)(pixel - origin)).getNormalizedVector();

	return Ray(origin, direction);
}


void prepareThread(std::vector<Color>& colorArray, const Camera& camera, World& world, int beginY, int endY) {
	for (int y = beginY; y < endY; ++y) {
		for (int x = 0; x < camera.m_horizontalSizePixels; ++x) {
			std::cout << "Working on Pixel #" << (x + (y * constants::gWidth)) << '\n';

			Ray tempRay = getRayForPixel(x, y, camera);

			Intersections intersections;
			IntersectionComputations computations;

			if (world.hit(tempRay, intersections, computations)) {
				std::cout << "World hit!\n";
				computations.prepareComputations(tempRay, intersections.m_intersections[intersections.m_firstIntersectionIndex]);
				colorArray.push_back(PointLight::getLighting(computations.m_object->getMaterial(), world.m_lightList, computations.m_pointOverIntersection, computations.m_eyeVector, computations.m_normalAtIntersectionPoint, world));
			}
			else {
				colorArray.push_back(Color(0.0f, 0.0f, 0.0f));
			}
		}
	}
}

int getLowerLimit(int currentIndex, int height) {
	return(currentIndex * (height / constants::gNumOfThreads));
}

int getUpperLimit(int currentIndex, int maxIndex, int height) {
	if (currentIndex == maxIndex) return height;
	return ((currentIndex + 1) * (height / constants::gNumOfThreads));
}

//This is the new main function, with Hitable object
int main() {
	Point cameraFrom(10.0f, 10.0f, 6.25f);
	Point cameraTo(0.0f, 0.0f, 0.0f);
	Vector cameraUpVector(0.0f, 1.0f, 0.0f);
	Camera camera(constants::gWidth, constants::gHeight, (constants::gPI / 3.0f), Matrix::createViewTransformationMatrix(cameraTo, cameraFrom, cameraUpVector));

	Material materialRed(Color(0.99f, 0.0f, 0.0f), 0.2f, 0.4f, 0.7f, 200.0f);
	Material materialGreen(Color(0.0f, 0.99f, 0.0f), 0.2f, 0.4f, 0.7f, 200.0f);
	Material materialBlue(Color(0.0f, 0.0f, 0.99f), 0.2f, 0.4f, 0.7f, 200.0f);

	std::vector<Hitable*> objectList;
	objectList.push_back(new Sphere(1, Matrix::createTranslationMatrix(0.0f, 0.0f, 2.0f), materialRed));
	objectList.push_back(new Sphere(2, Matrix::createTranslationMatrix(0.0f, 0.0f, -15.0f) * Matrix::createScalingMatrix(10.0f, 10.0f, 10.0f), materialGreen));
	objectList.push_back(new Sphere(3, Matrix::createTranslationMatrix(0.0f, 0.0f, 10.0f) * Matrix::createScalingMatrix(1.5f, 1.5f, 1.5f), materialBlue));

	std::vector<PointLight> lightList;
	lightList.push_back(PointLight(Point(0.0f, 0.0f, 8.0f), Color(1.0f, 1.0f, 1.0f)));

	World world(objectList, lightList);

	std::vector<std::vector<Color>> colorArrayParts;
	colorArrayParts.reserve(constants::gNumOfThreads);

	for (int i = 0; i < constants::gNumOfThreads; ++i) {
		std::vector<Color> temp;
		colorArrayParts.push_back(temp);
		colorArrayParts[i].reserve(((constants::gWidth * constants::gHeight) / constants::gNumOfThreads) + 1);
	}

	std::vector<std::thread> threadVector;
	threadVector.reserve(constants::gNumOfThreads);

	for (int i = 0; i < constants::gNumOfThreads; ++i) {
		threadVector.push_back(std::thread(prepareThread, std::ref(colorArrayParts[i]), std::ref(camera), std::ref(world), getLowerLimit(i, constants::gHeight), getUpperLimit(i, (constants::gNumOfThreads - 1), constants::gHeight)));
	}

	for (int i = 0; i < constants::gNumOfThreads; ++i) {
		threadVector[i].join();
	}

	std::vector<Color> completeColorArray;
	completeColorArray.reserve(constants::gWidth * constants::gHeight);
	for (int i = 0; i < constants::gNumOfThreads; ++i) {
		for (int j = 0; j < colorArrayParts[i].size(); ++j) {
			completeColorArray.push_back((colorArrayParts[i])[j]);
		}
	}

	for (int i = 0; i < world.m_objectList.size(); ++i) {
		delete world.m_objectList[i];
	}

	std::cout << "Completed the Canvas, generating PPM file...n\n";

	Canvas canvas(constants::gWidth, constants::gHeight, completeColorArray);
	PPMWriter::generatePPM(canvas);

	return 0;
}
