#include "Intersections.h"

Intersections::Intersections() {
	m_firstIntersectionIndex = -1;
	m_intersectionCount = 0;
	//We're creating a new Intersections object for us to populate with values
}

Intersections::~Intersections() {
	//Nothing in here for now
}

Intersections::Intersections(const std::vector<Intersection>& intersections, int intersectionCount) {
	m_intersections = intersections;
	m_intersectionCount = intersectionCount;
	m_firstIntersectionIndex = -1;
}

bool Intersections::hit() {
	//If this function returns true, that means that there is at least one intersection with a non-negative parameter
	//If it's false, then there is NO intersection with a non-negative parameter;
	//We'll also order the m_parameters std::vector in ascending order (ignoring all negative parameters)
	//This means that that the first element in the std::vector will be the first intersection that the ray will have
	
	//This sorts the m_intersections vector in ascending order of parameters
	std::sort(m_intersections.begin(), m_intersections.end(), [](Intersection& a, Intersection& b) {
		return (a.getParameter() < b.getParameter());
		});

	//Now that the "intersections" vector is ordered, we need to cycle through it and return the first possible non-negative value.
	for (int i = 0; i < m_intersectionCount; ++i) {
		if (m_intersections[i].getParameter() > 0.0f) {
			m_firstIntersectionIndex = i;
			return true;
		}
	}

	//If true isn't returned, then no intersection parameter is positive, hence no intersection is possible
	m_firstIntersectionIndex = -1;
	return false;	
}