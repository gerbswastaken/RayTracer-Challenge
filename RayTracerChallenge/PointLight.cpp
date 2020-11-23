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

Color PointLight::getLighting(const Material& material, const PointLight& pointLight, const Point& position, const Vector& eyeVector, const Vector& normalVector, bool isInShadow) {
	//The superposition of these three colors give the final color, according to the Phong Reflection Model
	Color ambientColor;
	Color diffuseColor;
	Color specularColor;

	Color effectiveColor;

	//Combining the Color of the Material and the Color of the Light Source itself
	if(material.m_hasPattern) effectiveColor = Color::halamardProduct(material.m_pattern->getColor(position), pointLight.getIntensity());
	else effectiveColor = Color::halamardProduct(material.m_color,  pointLight.getIntensity());

	ambientColor = (Color) (effectiveColor * material.m_ambient) ;

	if (!isInShadow) {
		//A vector that points from the position of incidence of the Ray to the given Light source
		Vector toLight = ((Vector)(pointLight.getPosition() - position)).getNormalizedVector();

		float toLight_dot_normalVector = dotProduct(toLight, normalVector);
		//If toLight_dot_normalVector is less than 0, then the cosine of the angle between toLight and normalVector is -ve, meaning that the angle is greater than pi/2 radians
		if (toLight_dot_normalVector < 0.0f) {
			//This implies that the toLight vector is on the other side of the normal
			//Thus there should be no contribution of diffuse and specular effects
			diffuseColor = Color(0.0f, 0.0f, 0.0f);
			specularColor = Color(0.0f, 0.0f, 0.0f);
		}
		else {
			diffuseColor = (Color)(effectiveColor * material.m_diffuse * toLight_dot_normalVector);

			//Now, we need to consider the Specular reflections
			Vector reflectionVector = Vector::getReflectedVector(-toLight, normalVector);
			float reflectionVector_dot_eyeVector = dotProduct(reflectionVector, eyeVector);
			//If reflectionVector_dot_eyeVector is less than 0, then the reflection points away from the eye Vector
			if (reflectionVector_dot_eyeVector <= 0) {
				specularColor = Color(0.0f, 0.0f, 0.0f);
			}
			else {
				specularColor = (Color)(pointLight.getIntensity() * material.m_specular * pow(reflectionVector_dot_eyeVector, material.m_shininess));
			}
		}

		return (Color)(ambientColor + specularColor + diffuseColor);
	}
	
	return ambientColor;
}

Color PointLight::getLighting(const Material& material, const std::vector<PointLight>& lightList, const Point& position, const Vector& eyeVector, const Vector& normalVector, World& world) {
	Color finalColor(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < lightList.size(); ++i) {
		finalColor += getLighting(material, lightList[i], position, eyeVector, normalVector, isInShadow(position, world, lightList[i]));
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