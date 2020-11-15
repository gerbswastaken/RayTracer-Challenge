#ifndef POINT_H
#define POINT_H

#include "Tuple.h"

class Point : public Tuple {
	public:
		Point();
		Point(float x, float y, float z);
		Point(const Tuple& tuple);

		friend std::ostream& operator<<(std::ostream& out, const Point& point);
};


#endif

