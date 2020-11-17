#ifndef PLANE_H
#define PLANE_H

#include "Hitable.h"

class Plane : public Hitable{
	//This will be a plane along the XZ plane, with the normal being the Y axis
	private:

	public:
		
		Vector getNormalAtPoint(const Point& point) override;
		bool hit(const Ray& ray, Intersections& intersections) override;
};


#endif