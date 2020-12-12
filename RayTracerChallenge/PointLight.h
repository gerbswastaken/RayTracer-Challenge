#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Color.h"
#include "Point.h"
#include "World.h"

#include "Material.h"
#include "IntersectionComputations.h"
#include "Pattern.h"
#include "MathToolbox.h"

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

		static Color getLighting(const PointLight& light, World& world, IntersectionComputations& comps, bool isInShadow);

		static Color getLighting(World& world, IntersectionComputations& comps);

		static Color getReflectedColor(World& world, IntersectionComputations& computations);

		static bool isInShadow(const Point& point, World& world, const PointLight& light);
};

#endif

