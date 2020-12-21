#include "PointLight.h"

PointLight::PointLight(const Point& position, const Color& intensity) {
	m_position = position;
	m_intensity = intensity;
}

PointLight::~PointLight() {
	//Nothing in here for now;
}

const Point& PointLight::getPosition() const {
	return m_position;
}

const Color& PointLight::getIntensity() const {
	return m_intensity;
}

void PointLight::setPosition(const Point& newPosition) {
	m_position = newPosition;
}

void PointLight::setIntensity(const Color& newIntensity) {
	m_intensity = newIntensity;
}


Color PointLight::getLighting(const PointLight& light, World& world, IntersectionComputations& comps, bool isInShadow) {
	//The superposition of these three colors give the final color, according to the Phong Reflection Model
	Color ambientColor;
	Color diffuseColor;
	Color specularColor;

	Color effectiveColor;

	//Combining the Color of the Material and the Color of the Light Source itself
	if (comps.m_object->getMaterial().m_hasPattern) effectiveColor = Color::halamardProduct(comps.m_object->getMaterial().m_pattern->getColor(comps.m_intersectionPoint, comps.m_object), light.getIntensity());
	else effectiveColor = Color::halamardProduct(comps.m_object->getMaterial().m_color, light.getIntensity());

	ambientColor = (Color)(effectiveColor * comps.m_object->getMaterial().m_ambient);

	if (!isInShadow) {
		//A vector that points from the position of incidence of the Ray to the given Light source
		Vector toLight = ((Vector)(light.getPosition() - comps.m_intersectionPoint)).getNormalizedVector();

		float toLight_dot_normalVector = dotProduct(toLight, comps.m_normalAtIntersectionPoint);
		//If toLight_dot_normalVector is less than 0, then the cosine of the angle between toLight and normalVector is -ve, meaning that the angle is greater than pi/2 radians
		if (toLight_dot_normalVector < 0.0f) {
			//This implies that the toLight vector is on the other side of the normal
			//Thus there should be no contribution of diffuse and specular effects
			diffuseColor = Color(0.0f, 0.0f, 0.0f);
			specularColor = Color(0.0f, 0.0f, 0.0f);
		}
		else {
			diffuseColor = (Color)(effectiveColor * comps.m_object->getMaterial().m_diffuse * toLight_dot_normalVector);

			//Now, we need to consider the Specular reflections
			Vector reflectionVector = Vector::getReflectedVector(-toLight, comps.m_normalAtIntersectionPoint);
			float reflectionVector_dot_eyeVector = dotProduct(reflectionVector, comps.m_eyeVector);
			//If reflectionVector_dot_eyeVector is less than 0, then the reflection points away from the eye Vector
			if (reflectionVector_dot_eyeVector <= 0) {
				specularColor = Color(0.0f, 0.0f, 0.0f);
			}
			else {
				specularColor = (Color)(light.getIntensity() * comps.m_object->getMaterial().m_specular * pow(reflectionVector_dot_eyeVector, comps.m_object->getMaterial().m_shininess));
			}
		}

		return (Color)(ambientColor + specularColor + diffuseColor);
	}

	return ambientColor;
}

Color PointLight::getLighting(World& world, IntersectionComputations& comps) {
	/* FOR DEBUGGING
	std::cout << "Called getLighting(World& , IntersectionComputations& ) for intersection at: " << comps.m_pointOverIntersection << '\n';
	std::cout << "Object Encountered: " << comps.m_object->getID() << '\n';
	*/
	Color finalColor(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < world.m_lightList.size(); ++i) {
		finalColor += getLighting(world.m_lightList[i], world, comps, isInShadow(comps.m_pointOverIntersection, world, world.m_lightList[i]));
	}
	return finalColor;
}

bool PointLight::isInShadow(const Point& point, World& world, const PointLight& light) {
	bool isInShadow = false;
	Vector direction = ((Vector)(light.getPosition() - point)).getNormalizedVector();
	float distance = ((Vector)(light.getPosition() - point)).getMagnitude();
	//This is a ray pointing from the Point of intersection to the light source
	Ray tempRay(point, direction);

	//Now to check whether it intersects anything in the world
	Intersections intersections;
	IntersectionComputations computations;

	if (world.hit(tempRay, intersections, computations)) {
		//If it does, we first have to make sure that the intersection is betweem the light source and the Point
		if (intersections.m_intersections[intersections.m_firstIntersectionIndex].getParameter() < distance) {
			isInShadow = true;
		}
	}

	return isInShadow;
}

Color PointLight::getReflectedColor(World& world, IntersectionComputations& computations, int remainingReflectionCalls) {
	if (MathToolbox::equal(computations.m_object->getMaterial().m_reflectivity, 0.0f) || remainingReflectionCalls <= 0 ) {
		return Color(0.0f, 0.0f, 0.0f);
	}
	Intersections tempIntersections;
	IntersectionComputations tempComps;
	Ray reflectedRay = Ray(computations.m_pointOverIntersection, computations.m_reflectedVector);
	Color reflectedColor = PointLight::getColorAt(reflectedRay, world, tempIntersections, tempComps, --remainingReflectionCalls );
	return (Color)( reflectedColor * computations.m_object->getMaterial().m_reflectivity );
}

Color PointLight::getColorAt(const Ray& tempRay, World& world, Intersections& intersections, IntersectionComputations& computations, int remainingReflectionCalls) {
	//static int numTimes = 0;
	if (world.hit(tempRay, intersections, computations)) {

		//Fix this Later!!!
		computations.prepareComputations(tempRay, intersections.m_intersections[intersections.m_firstIntersectionIndex], intersections);
		//Fix this later!!!!

		return (Color) (PointLight::getLighting(world, computations) + PointLight::getReflectedColor(world, computations, remainingReflectionCalls));
	}

	return Color(0.0f, 0.0f, 0.0f);
}
