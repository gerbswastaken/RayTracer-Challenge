#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"
#include "Tuple.h"
#include "Matrix.h"

#include <iostream>

class Ray {
	private:
		Point m_origin;
		Vector m_direction;
	public:	
		Ray(const Point& origin, const Vector& direction);
		Ray();
		~Ray();

		const Point& getOrigin() const;
		Point& getOrigin();

		const Vector& getDirection() const;
		Vector& getDirection();

		friend std::ostream& operator<<(std::ostream& out, const Ray& ray);

		Point getPoint(float t) const;

		Ray getTransformedRay(const Matrix& matrix) const;
};

#endif