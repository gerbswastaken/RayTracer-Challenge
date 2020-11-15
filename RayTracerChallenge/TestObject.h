#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include "Hitable.h"

class TestObject : public Hitable {
	private:
		bool m_isTestObject;

	public:
	TestObject(int id, const Matrix& transformationMatrix, const Material& material, bool isTestObject);

	bool hit(const Ray& ray, Intersections& intersections) override;
	Vector getNormalAtPoint(const Point& point) override;

};

#endif

