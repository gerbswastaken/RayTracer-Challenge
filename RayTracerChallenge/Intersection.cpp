#include "Intersection.h"

Intersection::Intersection(float parameter, Hitable* object) {
	m_parameter = parameter;
	m_object = object;
}

Intersection::~Intersection() {
	//Nothing in here for now
}

float Intersection::getParameter() const {
	return m_parameter;
}

Hitable* Intersection::getObject() const {
	return m_object;
}