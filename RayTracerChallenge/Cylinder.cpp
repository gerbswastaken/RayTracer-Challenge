#include "Cylinder.h"

Cylinder::Cylinder(int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material) {
	m_isClosed = false;
	m_yMin = -99999.9f;
	m_yMax = 99999.9f;
}

Cylinder::Cylinder(bool isClosed, float yMin, float yMax, int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material) {
	m_isClosed = isClosed;
	m_yMin = yMin;
	m_yMax = yMax;
}

Cylinder::~Cylinder() {
	//Nothing in here for now
}

bool Cylinder::localIntersect(const Ray& localRay, Intersections& intersections) {
	float a = (localRay.getDirection().getX() * localRay.getDirection().getX()) + (localRay.getDirection().getZ() * localRay.getDirection().getZ());
	
	//Check whether the ray is parallel to the Y-axis
	//In such cases, the ray would never intersect the walls of the cylinder, though we should still call the function that checks for cap intersections
	if (!MathToolbox::equal(a, 0.0f)) {

		float b = (2.0f * localRay.getOrigin().getX() * localRay.getDirection().getX()) + (2.0f * localRay.getOrigin().getZ() * localRay.getDirection().getZ());
		float c = (localRay.getOrigin().getX() * localRay.getOrigin().getX()) + (localRay.getOrigin().getZ() * localRay.getOrigin().getZ()) - 1.0f;

		float discriminant = (b * b) - (4.0f * a * c);

		//Check whether the ray intersects the cylinder or not
		if (discriminant < 0.0f) return false;

		//Finally, calculate parameters of intersection
		float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
		float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

		if (t1 > t2) {
			float temp = t1;
			t1 = t2;
			t2 = temp;
		}

		//See whether the values of Y are within the constraints that we have provided
		float y1 = localRay.getPoint(t1).getY();
		if (y1 > m_yMin && y1 < m_yMax) {
			intersections.m_intersections.push_back(Intersection(t1, this));
			++intersections.m_intersectionCount;
		}

		float y2 = localRay.getPoint(t2).getY();
		if (y2 > m_yMin && y2 < m_yMax) {
			intersections.m_intersections.push_back(Intersection(t2, this));
			++intersections.m_intersectionCount;
		}

	}

	intersectCaps(localRay, intersections);

	return intersections.hit();

}

Vector Cylinder::getLocalNormalAtPoint(const Point& point) {
	float distSquared = (point.getX() * point.getX()) + (point.getZ() * point.getZ());
	
	//if the point lies on the upper disk cap (or slightly above, since we take a point slightly further from the surface, along the surface normal)
	if ((distSquared < 1.0f) && (point.getY() >= (m_yMax - constants::gEpsilon))) return Vector(0.0f, 1.0f, 0.0f);

	//similarly for the lower disk cap
	if ((distSquared < 1.0f) && (point.getY() <= (m_yMin + constants::gEpsilon))) return Vector(0.0f, -1.0f, 0.0f);

	return Vector(point.getX(), 0.0f, point.getZ());
}

bool Cylinder::checkCapIntersection(const Ray& ray, float parameter) {
	float x = ray.getOrigin().getX() + (parameter * ray.getDirection().getX());
	float z = ray.getOrigin().getZ() + (parameter * ray.getDirection().getZ());

	//if the point is within a radius of 1 from the y-axis, ie implying that it will intersect the cap
	return ( (x * x) + (z * z) <= 1.0f );
}

void Cylinder::intersectCaps(const Ray& localRay, Intersections& intersections) {
	//if the cylinder is capped, forget about it
	//also if the ray is parallel to the y-axis
	if (m_isClosed == false || MathToolbox::equal(localRay.getDirection().getY(), 0.0f)) return;

	//now we check for any intersections with the caps
	//This is done by intersecting the rays with planes at these values of y

	//firstly, yMin
	float tCap1 = (m_yMin - localRay.getOrigin().getY()) / localRay.getDirection().getY();
	if (checkCapIntersection(localRay, tCap1)) {
		intersections.m_intersections.push_back(Intersection(tCap1, this));
		++intersections.m_intersectionCount;
	}

	//then, yMax
	float tCap2 = (m_yMax - localRay.getOrigin().getY()) / localRay.getDirection().getY();
	if (checkCapIntersection(localRay, tCap2)) {
		intersections.m_intersections.push_back(Intersection(tCap2, this));
		++intersections.m_intersectionCount;
	}

}