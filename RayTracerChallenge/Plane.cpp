#include "Plane.h"

Plane::Plane(int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material){
	//Nothing in here for now
}

Vector Plane::getLocalNormalAtPoint(const Point& point) {
	return Vector(0.0f, 1.0f, 0.0f);
}

bool Plane::localIntersect(const Ray& localRay, Intersections& intersections) {
	//There are 4 cases:
	//1. The Ray is parallel to the plane, hence will never intersect it
	//2. The Ray is coplanar with the plane, and hence will have an infintie number of intersections
	//	 However, since we're assuming the plane to be infinitesimally thin, we'll assume no intersection in this case
	//3. The Ray is above the plane (remember standard position of the plane is XZ plane)
	//4. The Ray is below the plane

	//Case #1 & 2: If the ray has a very small y component, then it's parallel with the plane, or its coplanar.
	//In both cases, there will be no intersection!
	if (MathToolbox::equal( (localRay.getDirection().getY()), 0.0f) ) {
		return false;
	}
	//Case #3 & 4: Here, we know that each ray will form a right angled triangle. 
	//To find the parameter of the intersection, we'll use the following formula:
	// t = -localRay.origin.y / localRay.direction.y
	else {
		intersections.m_intersections.push_back(Intersection(((-1.0f * localRay.getOrigin().getY()) / localRay.getDirection().getY()), this));
		intersections.m_intersectionCount += 1;
		return intersections.hit();
	}
	
}