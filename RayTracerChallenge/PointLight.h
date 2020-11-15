#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Color.h"
#include "Point.h"
#include "World.h"

#include "Material.h"
#include "IntersectionComputations.h"

#include <cmath>
#include <vector>

class World;

class PointLight {
	private:
		Point m_position;
		Color m_intensity;
	public:
		PointLight(const Point& position, const Color& intensity);
		~PointLight();

		const Point& getPosition() const;
		const Color& getIntensity() const;

		void setPosition(const Point& newPosition);
		void setIntensity(const Color& newIntensity);

		static Color getLighting(const Material& material, const PointLight& pointLight, const Point& position, const Vector& eyeVector, const Vector& normalVector, bool isInShadow);
		static Color getLighting(const Material& material, const std::vector<PointLight>& lightList, const Point& position, const Vector& eyeVector, const Vector& normalVector, World& world);

		static bool isInShadow(const Point& point, World& world, const PointLight& light);
};

#endif

