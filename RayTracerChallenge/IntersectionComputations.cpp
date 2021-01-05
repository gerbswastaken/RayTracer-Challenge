#include "IntersectionComputations.h"

IntersectionComputations::IntersectionComputations() {

}

IntersectionComputations::IntersectionComputations(const Ray& ray, const Intersection& intersection, const Intersections& intersections) {
	m_parameter = intersection.getParameter();
	m_object = intersection.getObject();
	m_intersectionPoint = ray.getPoint(intersection.getParameter());
	m_eyeVector = -1.0f * (ray.getDirection());
	//This gives the normal pointing outwards!
	m_normalAtIntersectionPoint = m_object->getNormalAtPoint(m_intersectionPoint);
	m_insideObject = false;
	if (dotProduct(m_normalAtIntersectionPoint, m_eyeVector) < 0.0f) {
		//Checking to see whether the angle between the normal and eyeVector is obtuse. 
		//If it is, then the ray intersects the surface from the inside. Hence we have to take the vector opposite to the normal pointing outwards
		m_normalAtIntersectionPoint = -(m_normalAtIntersectionPoint);
		m_insideObject = true;
	}
	m_reflectedVector = Vector::getReflectedVector(ray.getDirection(), m_normalAtIntersectionPoint);
	m_pointOverIntersection = m_intersectionPoint + (m_normalAtIntersectionPoint * constants::gEpsilon);

	
	
}

int containsObject(const std::vector<Hitable*>& objectContainer, Hitable* object) {
	for (int i = 0; i < objectContainer.size(); ++i) {
		if (objectContainer[i] == object) {
			return i;
		}
	}
	
	return -1;
}

void IntersectionComputations::prepareComputations(const Ray& ray, const Intersection& intersection, const Intersections& intersections) {
	m_parameter = intersection.getParameter();
	m_object = intersection.getObject();
	m_intersectionPoint = ray.getPoint(intersection.getParameter());
	m_eyeVector = -1.0f * (ray.getDirection());
	//This gives the normal pointing outwards!
	m_normalAtIntersectionPoint = m_object->getNormalAtPoint(m_intersectionPoint);
	m_insideObject = false;
	if (dotProduct(m_normalAtIntersectionPoint, m_eyeVector) < 0.0f) {
		//Checking to see whether the angle between the normal and eyeVector is obtuse. 
		//If it is, then the ray intersects the surface from the inside. Hence we have to take the vector opposite to the normal pointing outwards
		m_normalAtIntersectionPoint = -(m_normalAtIntersectionPoint);
		m_insideObject = true;
	}
	m_reflectedVector = Vector::getReflectedVector(ray.getDirection(), m_normalAtIntersectionPoint);
	m_pointOverIntersection = m_intersectionPoint + (m_normalAtIntersectionPoint * constants::gEpsilon);
	m_pointUnderIntersection = m_intersectionPoint - (m_normalAtIntersectionPoint * constants::gEpsilon);

	//Loop through all possible intersections
	for (int i = 0; i < intersections.m_intersectionCount; ++i) {

		if (intersections.m_intersections[i] == intersection) {
			if (m_intersectionObjectContainer.size() == 0) { //No refractive indices have been added, so we should start out with a vacuum, ie n1 = 1.0f
				m_n1 = 1.0f;
			}
			else {	//We take the last refractiveIndex in the container
				m_n1 = m_intersectionObjectContainer.back()->getMaterial().m_refractiveIndex;
			}
		}
		
		//If the container already contains the object, then it means that we're leaving the object, so we can remove it from the list
		if (containsObject(m_intersectionObjectContainer, intersections.m_intersections[i].getObject()) != -1) {
			m_intersectionObjectContainer.erase(m_intersectionObjectContainer.begin() + (containsObject(m_intersectionObjectContainer, intersections.m_intersections[i].getObject()) ));
		}
		//Otherwise, append it to the end of the list
		else {
			m_intersectionObjectContainer.push_back(intersections.m_intersections[i].getObject());
		}

		if (intersections.m_intersections[i] == intersection) {
			if (m_intersectionObjectContainer.size() == 0) { //No refractive indices have been added, so we should start out with a vacuum, ie n1 = 1.0f
				m_n2 = 1.0f;
			}
			else {	//We take the last refractiveIndex in the container
				m_n2 = m_intersectionObjectContainer.back()->getMaterial().m_refractiveIndex;
			}
		}

	}
}