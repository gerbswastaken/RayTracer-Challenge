#ifndef PLANE_H
#define PLANE_H

#include "Hitable.h"

#include "MathToolbox.h"

class Plane : public Hitable{
	//This will be a plane along the XZ plane, with the normal being the Y axis
	private:

	public:
		Plane(int id, const Matrix& transformationMatrix, const Material& material);

		Vector getLocalNormalAtPoint(const Point& point) override;
		virtual bool localIntersect(const Ray& localRay, Intersections& intersections) override;

};


#endif