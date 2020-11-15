#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "Intersection.h"

#include <algorithm>
#include <vector>
#include <iostream>

class Intersections {
	public:
		std::vector<Intersection> m_intersections;
		int m_intersectionCount;
		int m_firstIntersectionIndex;

		Intersections();
		~Intersections();

		Intersections(const std::vector<Intersection>& intersections, int intersectionCount);

		bool hit();
};

#endif
