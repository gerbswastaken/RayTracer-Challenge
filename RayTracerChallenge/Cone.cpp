#include "Cone.h"

Cone::Cone(int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material) {
	m_isClosed = false;
	m_yMin = -99999.9f;
	m_yMax = 99999.9f;
}

Cone::Cone(bool isClosed, float yMin, float yMax, int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material) {
	m_isClosed = isClosed;
	m_yMax = yMax;
	m_yMin = yMin;
}

Cone::~Cone() {
	//Nothing in here -_-
}

bool Cone::localIntersect(const Ray& localRay, Intersections& intersections) {
	float a = ( (localRay.getDirection().getX() * localRay.getDirection().getX()) + (localRay.getDirection().getZ() * localRay.getDirection().getZ()) - (localRay.getDirection().getY() * localRay.getDirection().getY()) );
	float b = (2.0f * ((localRay.getDirection().getX() * localRay.getOrigin().getX()) + (localRay.getDirection().getZ() * localRay.getOrigin().getZ()) - (localRay.getDirection().getY() * localRay.getOrigin().getY()) ) );
	//If both a and b are close to or equal to zero, then the ray will miss 100%, so we can stop the function here!
	if (MathToolbox::equal(a, 0.0f) && MathToolbox::equal(b, 0.0f)) return false;

	float c = ((localRay.getOrigin().getX() * localRay.getOrigin().getX()) + (localRay.getOrigin().getZ() * localRay.getOrigin().getZ()) - (localRay.getOrigin().getY() * localRay.getOrigin().getY()));
	
	float discriminant = ((b * b) - (4.0f * a * c));
	//kinda obvious, in this case, sqrt(discriminant) that we call below would fail, since discriminant would be negative.
	if (discriminant < 0.0f) return false;

	//if only a is equal to zero, and not b, then there is only ONE point of intersection! that being: t = -c/2b
	if (MathToolbox::equal(a, 0.0f)) {
		float t0 = (-c / (2.0f * b));
		intersections.m_intersections.push_back(Intersection(t0, this));
		++intersections.m_intersectionCount;
	}
	//otherwise, we use the standard formula, the same as we used for a cylinder!
	else {
		float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
		float y1 = localRay.getPoint(t1).getY();
		if (y1 < m_yMax && y1 > m_yMin) {
			intersections.m_intersections.push_back(Intersection(t1, this));
			++intersections.m_intersectionCount;
		}
	
		float t2 = (-b + sqrt(discriminant)) / (2.0f * a);
		float y2 = localRay.getPoint(t2).getY();
		if (y2 < m_yMax && y2 > m_yMin) {
			intersections.m_intersections.push_back(Intersection(t2, this));
			++intersections.m_intersectionCount;
		}
	
	}

	intersectCaps(localRay, intersections);
	
	return intersections.hit();
}

Vector Cone::getLocalNormalAtPoint(const Point& point) {
	float distanceFromYAxis = sqrt((point.getX() * point.getX()) + (point.getZ() * point.getZ()));

	//if the point lies on the upper disk cap (or slightly above, since we take a point slightly further from the surface, along the surface normal)
	if ((distanceFromYAxis < point.getY()) && (point.getY() >= (m_yMax - constants::gEpsilon))) return Vector(0.0f, 1.0f, 0.0f);

	//similarly for the lower disk cap
	if ((distanceFromYAxis < point.getY()) && (point.getY() <= (m_yMin + constants::gEpsilon))) return Vector(0.0f, -1.0f, 0.0f);

	//for upper cone region, normals should point downwards
	if(point.getY() > 0.0f) return Vector(point.getX(), -distanceFromYAxis, point.getZ());
	//otherwise, upward normals are the correct ones
	return Vector(point.getX(), distanceFromYAxis, point.getZ());
}

bool Cone::checkCapIntersection(const Ray& ray, float parameter) {
	float x = ray.getOrigin().getX() + (parameter * ray.getDirection().getX());
	float y = ray.getOrigin().getY() + (parameter * ray.getDirection().getY());
	float z = ray.getOrigin().getZ() + (parameter * ray.getDirection().getZ());

	//if the point is within a radius |y| from the y-axis, ie implying that it will intersect the cap
	return ((x * x) + (z * z) <= std::abs(y));
}

void Cone::intersectCaps(const Ray& localRay, Intersections& intersections) {
	//if the cone is capped, forget about it
	
	if (m_isClosed == false) return;

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