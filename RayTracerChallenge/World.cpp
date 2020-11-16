#include "World.h"

World::World(const std::vector<Hitable*>& objectList, const std::vector<PointLight>& lightList) {
	m_objectList = objectList;
	m_lightList = lightList;
}

World::~World() {
	//Nothing in here for now
}

void World::addObject(Hitable* objectPointer) {
	m_objectList.push_back(objectPointer);
}

void World::addLight(const PointLight& light) {
	m_lightList.push_back(light);
}

Hitable* World::getObject(int index) {
	return m_objectList[index];
}

PointLight& World::getLight(int index) {
	return m_lightList[index];
}

bool World::hit(const Ray& ray, Intersections& intersections, Hitable** hitObject) {
	bool hitAnything = false;
	//Iterate through all of the objects in the m_objectList
	for (int i = 0; i < m_objectList.size(); ++i) {
		//If any intersection occurs
		if (m_objectList[i]->hit(ray, intersections)) {
			hitAnything = true;
			*hitObject = (intersections.m_intersections[intersections.m_firstIntersectionIndex].getObject());
		}
	}

	return hitAnything;
}

bool World::hit(const Ray& ray, Intersections& intersections, const IntersectionComputations& intersectionComputations) {
	bool hitAnything = false;
	//Iterate through all of the objects in the 
	for (int i = 0; i < m_objectList.size(); ++i) {
		//If any intersection occurs
		if (m_objectList[i]->hit(ray, intersections)) {
			hitAnything = true;
		}
	}

	return hitAnything;
}