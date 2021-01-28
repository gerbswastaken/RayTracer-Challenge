#ifndef CUBE_H
#define CUBE_H

#include "Hitable.h"

class Cube : public Hitable { 
	public:
		Cube(int id, const Matrix& transformationMatrix, const Material& material);
		~Cube();
		static void checkAxis(float& t_min, float& t_max, float origin, float direction);
		bool localIntersect(const Ray& localRay, Intersections& intersections) override;
		Vector getLocalNormalAtPoint(const Point& point) override;

};

#endif