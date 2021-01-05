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

Color PointLight::getReflectedColor(World& world, IntersectionComputations& computations, int remainingReflectionCalls, int remainingRefractionCalls) {
	if (MathToolbox::equal(computations.m_object->getMaterial().m_reflectivity, 0.0f) || remainingReflectionCalls <= 0 ) {
		return Color(0.0f, 0.0f, 0.0f);
	}
	Intersections tempIntersections;
	IntersectionComputations tempComps;
	Ray reflectedRay = Ray(computations.m_pointOverIntersection, computations.m_reflectedVector);
	Color reflectedColor = PointLight::getColorAt(reflectedRay, world, tempIntersections, tempComps, --remainingReflectionCalls, remainingRefractionCalls );
	return (Color)( reflectedColor * computations.m_object->getMaterial().m_reflectivity );
}

Color PointLight::getRefractedColor(World& world, IntersectionComputations& computations, int remainingReflectionCalls, int remainingRefractiveCalls) {
	//Check whether the object is completely opaque or remainingRefractiveCalls = 0
	//In such cases, there will be no contribution of this light ray on getRefractedColor().
	if (MathToolbox::equal(computations.m_object->getMaterial().m_transparency, 0.0f) || remainingRefractiveCalls <= 0) {
		return Color(0.0f, 0.0f, 0.0f);
	}
	//Now to check whether Total Internal Reflection occurs:
	//Snell's Law states that n1 * sin(theta1) = n2 * sin(theta2)
	//if sin(theta2) > 1, then Total Internal Reflection occurs.
	//Hence, we need to test for the value of (n1 / n2) * sin(theta1), where theta1 is the angle of incidence
	float cosTheta1 = dotProduct(computations.m_eyeVector, computations.m_normalAtIntersectionPoint);
	float refractiveIndexRatio = computations.m_n1 / computations.m_n2;
	//sinSquaredTheta2 = (n1 / n2)^2 * sin^2(theta1) = (n1 / n2)^2 * (1 - cos^2(theta1))
	float sinSquaredTheta2 = (refractiveIndexRatio * refractiveIndexRatio) *  (1.0f - (cosTheta1 * cosTheta1));
	//No need to find square root, as if sinSquaredTheta1 > 1, sinTheta1 > 1
	if (sinSquaredTheta2 > 1.0f) {
		//We return Black because the light ray cannot escape, effectively nullifying its effect on getRefractedColor().
		return Color(0.0f, 0.0f, 0.0f);
	}
	std::cout << "getRefractedLight() called!\n";
	float cosTheta2 = sqrt(1.0f - sinSquaredTheta2);
	Vector refractedDirection = (computations.m_normalAtIntersectionPoint * ((refractiveIndexRatio * cosTheta1) - cosTheta2)) - (computations.m_eyeVector * refractiveIndexRatio);
	Ray refractedRay(computations.m_pointUnderIntersection, refractedDirection);
	Intersections tempIntersections;
	IntersectionComputations tempComputations;

	Color refractedColor = PointLight::getColorAt(refractedRay, world, tempIntersections, tempComputations, remainingReflectionCalls,  --remainingRefractiveCalls);
	return (Color)(refractedColor * computations.m_object->getMaterial().m_transparency);
}

Color PointLight::getColorAt(const Ray& tempRay, World& world, Intersections& intersections, IntersectionComputations& computations, int remainingReflectionCalls, int remainingRefractionCalls) {
	if (world.hit(tempRay, intersections, computations)) {
		computations.prepareComputations(tempRay, intersections.m_intersections[intersections.m_firstIntersectionIndex], intersections);
		//return (Color) (PointLight::getLighting(world, computations) + PointLight::getReflectedColor(world, computations, remainingReflectionCalls, remainingRefractionCalls) + PointLight::getRefractedColor(world, computations, remainingReflectionCalls, remainingRefractionCalls));

		if (computations.m_object->getMaterial().m_reflectivity > 0.0f && computations.m_object->getMaterial().m_transparency > 0.0f) {
			float reflectance = PointLight::schlickReflectance(computations);
			return (Color)(PointLight::getLighting(world, computations) + (reflectance * PointLight::getReflectedColor(world, computations, remainingReflectionCalls, remainingRefractionCalls)) + ( (1.0f - reflectance) * PointLight::getRefractedColor(world, computations, remainingReflectionCalls, remainingRefractionCalls)));
		}
		return (Color)(PointLight::getLighting(world, computations) + PointLight::getReflectedColor(world, computations, remainingReflectionCalls, remainingRefractionCalls) + PointLight::getRefractedColor(world, computations, remainingReflectionCalls, remainingRefractionCalls));
	}

	return Color(0.0f, 0.0f, 0.0f);
}

float PointLight::schlickReflectance(IntersectionComputations& computations) {
	float cosAngle = dotProduct(computations.m_eyeVector, computations.m_normalAtIntersectionPoint);

	//Total Internal Reflection can only occur if n1 > n2
	if (computations.m_n1 > computations.m_n2) {
		float nRatio = computations.m_n1 / computations.m_n2;
		float sinSquared_t = nRatio * nRatio * (1.0f - (cosAngle * cosAngle));
		if (sinSquared_t > 1.0f) return 1.0f;
	
		float cosAngle_t = sqrt(1.0f - sinSquared_t);
		//when n1 > n2, use cosAngle_t instead of cosAngle
		cosAngle = cosAngle_t;
	}

	float rNaught = ((computations.m_n1 - computations.m_n2) / (computations.m_n1 + computations.m_n2)) * ((computations.m_n1 - computations.m_n2) / (computations.m_n1 + computations.m_n2));
	float OneMinusCosRaisedTo5 = 1.0f;
	for (int i = 0; i < 5; ++i) {
		OneMinusCosRaisedTo5 *= (1.0f - cosAngle);
	}

	return rNaught + ((1.0f - rNaught) * OneMinusCosRaisedTo5);
}