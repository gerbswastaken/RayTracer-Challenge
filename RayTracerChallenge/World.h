#ifndef WORLD_H
#define WORLD_H

#include "PointLight.h"
#include "Hitable.h"
#include "Ray.h"
#include "IntersectionComputations.h"

#include <vector>

class PointLight;

class World {
	public:
		std::vector<Hitable*> m_objectList;
		std::vector<PointLight> m_lightList;

		World() = delete;
		World(const std::vector<Hitable*>& objectList, const std::vector<PointLight>& lightList);

		void addObject(Hitable* objectPointer);
		void addLight(const PointLight& light);

		Hitable* getObject(int index);
		PointLight& getLight(int index);

		~World();

		bool hit(const Ray& ray, Intersections& intersections, Hitable** objectHit);
		bool hit(const Ray& ray, Intersections& intersections, const IntersectionComputations& intersectionComputations);

};

#endif

