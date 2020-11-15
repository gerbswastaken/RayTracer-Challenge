#include "TestObject.h"

TestObject::TestObject(int id, const Matrix& transformationMatrix, const Material& material, bool isTestObject) : Hitable(id, transformationMatrix, material) {
	m_isTestObject = isTestObject;
}

bool TestObject::hit(const Ray& ray, Intersections& intersections) {
	std::cout << "bool hit(const Ray& ray, Intersections& intersections) has been called!\n";
	return false;
}

Vector TestObject::getNormalAtPoint(const Point& point) {
	std::cout << "Vector getNormalAtPoint(const Point& point) has been called!\n";
	return Vector(1.0f,1.0f,1.0f);
}