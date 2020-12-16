#include "IntersectionComputations.h"

IntersectionComputations::IntersectionComputations() {

}

IntersectionComputations::IntersectionComputations(const Ray& ray, const Intersection& intersection) {
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

void IntersectionComputations::prepareComputations(const Ray& ray, const Intersection& intersection) {
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