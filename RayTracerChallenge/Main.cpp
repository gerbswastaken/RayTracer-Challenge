#include "Point.h"
#include "Color.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Constants.h"

#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Cone.h"
#include "PointLight.h"
#include "World.h"
#include "Camera.h"

#include "Intersection.h"
#include "IntersectionComputations.h"

#include "Hitable.h"
#include "TestObject.h"

#include "Pattern.h"
#include "StripePattern.h"
#include "GradientPattern.h"
#include "RingPattern.h"
#include "CheckersPattern.h"
#include "RadialGradientPattern.h"
#include "BlendedPattern.h"
#include "SolidColorPattern.h"

#include "PPMWriter.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <functional>


//Bunch of Forward Declarations
Ray getRayForPixel(int xPixel, int yPixel, const Camera& camera);
void prepareThread(std::vector<Color>& colorArray, const Camera& camera, World& world, int beginY, int endY);
int getLowerLimit(int currentIndex, int height);
int getUpperLimit(int currentIndex, int maxIndex, int height);

/*
int main() {

	Material materialGlass1(Color(0.0f, 1.0f, 0.0f), 1.0f, 0.7f, 0.3f, 100.0f, 0.5f, 1.5f, 1.0f);

	std::vector<Hitable*> objectList;
	objectList.push_back(new Sphere(1, Matrix::createIdentityMatrix(4), materialGlass1));

	std::vector<PointLight> lightList;
	lightList.push_back(PointLight(Point(7.0f, 5.0f, 3.0f), Color(1.0f, 1.0f, 1.0f)));

	//Generates a World object
	World world(objectList, lightList);

	float _1ByRoot2 = 1.0f / sqrt(2);

	Ray rayIn(Point(0.0f, 0.99f, 2.0f), Vector(0.0f, 0.0f, -1.0f));
	Intersection intersection(1.8589f, objectList[0]);

	std::vector<Intersection> intersectionVector;
	intersectionVector.push_back(Intersection(1.8589f, objectList[0]));
	
	Intersections intersections(intersectionVector, 1);
	
	IntersectionComputations computations(rayIn, intersection, intersections);
	computations.prepareComputations(rayIn, intersection, intersections);

	Hitable* cubeObject = new Cube(1, Matrix::createIdentityMatrix(4), materialGlass1);
	std::vector<Point> pointList;
	pointList.push_back(Point(1.0f, 0.5f, -0.8f));
	pointList.push_back(Point(-1.0f, -0.2f, 0.9f));
	pointList.push_back(Point(-0.4f, 1.0f, -0.1f));
	pointList.push_back(Point(0.3f, -1.0f, -0.7f));
	pointList.push_back(Point(-0.6f, 0.3f, 1.0f));
	pointList.push_back(Point(0.4f, 0.4f, -1.0f));
	pointList.push_back(Point(1.0f, 1.0f, 1.0f));
	pointList.push_back(Point(-1.0f, -1.0f, -1.0f));



	for (int i = 0; i < pointList.size(); ++i) {
		std::cout << cubeObject->getLocalNormalAtPoint(pointList[i]) << '\n';
	}

	return 0;
}

*/


//I'll give a quick rundown of how to use this thing
//I'm planning on adding a better system of doing this rather than changing main()
//Maybe with passing arguments via a file or something, but for now this will do

//Firstly, go to "Constants.h" to change some of the constants associated with the Ray-Tracing engine

//Now we begin the actual main() function

int main() {
	//This Ray-Tracer uses a Right-handed coordinate system:
	//X-axis is to the Right, Y-axis is vertically Upwards, and Z-axis is the cross product

	Point cameraFrom(-2.0f, 2.7f, 2.0f);
	Point cameraTo(0.0f, 1.5f, 0.0f);
	Vector cameraUpVector(0.0f, 1.0f, 0.0f);
	Camera camera(constants::gWidth, constants::gHeight, (constants::gPI / 2.0f), Matrix::createViewTransformationMatrix(cameraTo, cameraFrom, cameraUpVector));

	StripePattern* sPat1 = new StripePattern(Matrix::createIdentityMatrix(4), Color(0.0f, 0.0f, 0.0f), Color(1.0f, 1.0f, 1.0f));
	StripePattern* sPat2 = new StripePattern(Matrix::createRotationMatrix('y', constants::gPI / 2.0f, true), Color(0.1f, 0.1f, 0.1f), Color(1.0f, 1.0f, 1.0f));
	BlendedPattern* bPat1 = new BlendedPattern(Matrix::createIdentityMatrix(4), sPat1, sPat2);
	StripePattern* sPat3 = new StripePattern(Matrix::createScalingMatrix(0.3f, 0.3f, 0.3f), Color(1.0f, 1.0f, 0.0f), Color(1.0f, 0.0f, 1.0f));
	StripePattern* sPat4 = new StripePattern(Matrix::createScalingMatrix(0.3f, 0.3f, 0.3f) * Matrix::createRotationMatrix('y', constants::gPI / 2.0f, true), Color(1.0f, 1.0f, 0.0f), Color(1.0f, 0.0f, 1.0f));
	BlendedPattern* bPat2 = new BlendedPattern(Matrix::createIdentityMatrix(4), sPat3, sPat4);
	CheckersPattern* cPat1 = new CheckersPattern(Matrix::createIdentityMatrix(4), Color(1.0f, 1.0f, 1.0f), Color(0.0f, 0.0f, 0.0f));
	CheckersPattern* cPat2 = new CheckersPattern(Matrix::createIdentityMatrix(4), Color(0.6f, 0.0f, 0.6f), Color(0.9f, 0.9f, 0.0f));

	Material materialPlane(bPat1, 0.1f, 0.5f, 0.3f, 50.0f, 0.8f, 1.0f, 0.0f);
	Material materialBall(bPat2, 0.15f, 0.5f, 0.5f, 200.0f, 0.4f, 1.5f, 0.3f);

	std::vector<Hitable*> objectList;
	objectList.push_back(new Plane(1, Matrix::createIdentityMatrix(4), materialPlane));
	//objectList.push_back(new Cube(2, Matrix::createTranslationMatrix(0.0f, 2.0f, 0.0f) * Matrix::createRotationMatrix('x', constants::gPI / 4.0f,true) * Matrix::createRotationMatrix('z', constants::gPI / 4.0f, true) * Matrix::createRotationMatrix('y', constants::gPI / 4.0f, true), materialBall ));
	objectList.push_back(new Cone(true, -1.0f, 1.0f, 2, Matrix::createTranslationMatrix(0.0f, 2.0f, 0.0f), materialBall));

	std::vector<PointLight> lightList;
	lightList.push_back(PointLight(Point(-5.0f, 7.0f, 7.0f), Color(1.0f, 1.0f, 1.0f)));
	//lightList.push_back(PointLight(Point(-1.0f, 2.0f, 4.0f), Color(1.0f, 1.0f, 1.0f)));
	lightList.push_back(PointLight(Point(-1.0f, 5.0f, 2.0f), Color(1.0f, 1.0f, 1.0f)));

	//Generates a World object
	World world(objectList, lightList);

	//This stuff is for multithreading the program to run more efficiently
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

	//Once the program reaches here, the hard work of the Ray-Tracer is over.
	//Now there's just some cleanup left
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
	//And generates a ".ppm" file
	PPMWriter::generatePPM(canvas);

	//I use http://paulcuth.me.uk/netpbm-viewer/ to view them.
	//Maybe I should write some code to display a .ppm file? I might try in the future

	return 0;
}


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

			int tempReflectionCalls = constants::gReflectionRecursionLimit;
			int tempRefractionCalls = constants::gRefractionRecursionLimit;


			colorArray.push_back(PointLight::getColorAt(tempRay, world, intersections, computations, tempReflectionCalls, tempRefractionCalls));
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
