#include "Point.h"

Point::Point() : Tuple(0.0f,0.0f,0.0f,1.0f) {

}

Point::Point(float x, float y, float z) : Tuple(x, y, z, 1.0f) {

}

Point::Point(const Tuple& tuple) : Tuple(tuple.getX(), tuple.getY(), tuple.getZ(), 1.0f) {

}

std::ostream& operator<<(std::ostream& out, const Point& point) {
	out << "Point( " << point.getX() << ", " << point.getY() << ", " << point.getZ() << ", " << point.getW() << " )";
	return out;
}