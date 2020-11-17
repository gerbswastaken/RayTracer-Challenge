#include "TestObject.h"

TestObject::TestObject(int id, const Matrix& transformationMatrix, const Material& material, bool isTestObject) : Hitable(id, transformationMatrix, material) {
	m_isTestObject = isTestObject;
}

bool TestObject::localIntersect(const Ray& localRay, Intersections& intersections) {
	std::cout << "bool localIntersect(const Ray& localRay, Intersections& intersections) has been called!\n";
	return true;
}

Vector TestObject::getLocalNormalAtPoint(const Point& point) {
	std::cout << "Vector getLocalNormalAtPoint(const Point& point) has been called!\n";
	return (Vector)point;
}