#ifndef CYLINDER_H
#define CYLINDER_H

#include "Hitable.h"
#include "MathToolbox.h"

//This cylinder is one centered at the origin and extending along the y-axis

class Cylinder : public Hitable {
	private:
		bool m_isClosed;
		float m_yMin;
		float m_yMax;
	public:
		Cylinder(int id, const Matrix& transformationMatrix, const Material& material);
		Cylinder(bool isClosed, float yMin, float yMax, int id, const Matrix& transformationMatrix, const Material& material);
		~Cylinder();

		bool checkCapIntersection(const Ray& ray, float parameter);
		void intersectCaps(const Ray& localRay, Intersections& intersections);

		bool localIntersect(const Ray& localRay, Intersections& intersections) override;
		Vector getLocalNormalAtPoint(const Point& point) override;
};


#endif
