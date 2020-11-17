#include "Sphere.h"

Sphere::Sphere(int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material){

}


Sphere::~Sphere() {
	//Nothing in here for now
}

Vector Sphere::getLocalNormalAtPoint(const Point& localPoint) {
	//Here, (0,0,0) is the center of the circle!
	return ((Vector)(localPoint - Point(0.0f, 0.0f, 0.0f)));;
}

bool Sphere::localIntersect(const Ray& localRay, Intersections& intersections) {
	//Here, the equation of the sphere is dot(point, point) = 1 as it is a unit sphere with center at origin
	//Hence, dot ( (ray.m_origin + t * ray.m_direction) , (ray.m_origin + t * ray.m_direction) ) = 1
	//Simplifying out to:
	//t^2 * dot(ray.m_direction, ray.m_direction) + t * 2.0f * dot(ray.m_origin, ray.m_direction) + dot(ray.m_origin, ray.m_origin) - 1 = 0
	//Comparing to at^2 + bt + c = 0....
	//a = dot(ray.m_direction, ray.m_direction)
	//b = 2.0f * dot(ray.m_origin, ray.m_direction)
	//c = dot(ray.m_origin, ray.m_origin) - 1
	//Solutions to this equation are given by: t = (-b + (b^2 - 4ac)^(1/2) ) / 2a or (-b - (b^2 - 4ac)^(1/2) ) / 2a
	//Also: discriminant = (b^2 - 4ac)
	//if discriminant > 0: 2 solutions (real)
	//if discriminant < 0: no solutions (imaginary)
	//if discriminant = 0: 1 solution (tangent)

	float a = dotProduct(localRay.getDirection(), localRay.getDirection());
	float b = 2.0f * dotProduct(localRay.getDirection(), (Vector)localRay.getOrigin());
	float c = dotProduct((Vector)localRay.getOrigin(), (Vector)localRay.getOrigin()) - 1.0f;
	float discriminant = (b * b) - (4.0f * a * c);

	if (discriminant > 0) {	//the ray intersects the sphere at two points
		intersections.m_intersections.push_back(Intersection((-b - sqrt(discriminant)) / (2.0f * a), this));
		intersections.m_intersections.push_back(Intersection((-b + sqrt(discriminant)) / (2.0f * a), this));
		intersections.m_intersectionCount += 2;
		return intersections.hit();
	}
	else if (discriminant == 0) { //the ray is a tangent to the sphere, intersects at a single point
		intersections.m_intersections.push_back(Intersection(-b / (2.0f * a), this));
		intersections.m_intersectionCount += 1;
		return intersections.hit();
	}
	else { //discriminant > 0, implying no ray-sphere intersection at all
		return intersections.hit();
	}
}


/*
	//We first have to transform the incident ray, as the sphere has its own transformationMatrix
	//We apply the inverse of that transformationMatrix to the incident Ray to get the same effect as that
	//incident ray interacting with the transformed object
	Ray transformedRay = ray.getTransformedRay(this->getTransformationMatrix().getInverseMatrix());

	//Here, the equation of the sphere is dot(point, point) = 1 as it is a unit sphere with center at origin
	//Hence, dot ( (ray.m_origin + t * ray.m_direction) , (ray.m_origin + t * ray.m_direction) ) = 1
	//Simplifying out to:
	//t^2 * dot(ray.m_direction, ray.m_direction) + t * 2.0f * dot(ray.m_origin, ray.m_direction) + dot(ray.m_origin, ray.m_origin) - 1 = 0
	//Comparing to at^2 + bt + c = 0....
	//a = dot(ray.m_direction, ray.m_direction)
	//b = 2.0f * dot(ray.m_origin, ray.m_direction)
	//c = dot(ray.m_origin, ray.m_origin) - 1
	//Solutions to this equation are given by: t = (-b + (b^2 - 4ac)^(1/2) ) / 2a or (-b - (b^2 - 4ac)^(1/2) ) / 2a
	//Also: discriminant = (b^2 - 4ac)
	//if discriminant > 0: 2 solutions (real)
	//if discriminant < 0: no solutions (imaginary)
	//if discriminant = 0: 1 solution (tangent)

	float a = dotProduct(transformedRay.getDirection(), transformedRay.getDirection());
	float b = 2.0f * dotProduct(transformedRay.getDirection(), (Vector)transformedRay.getOrigin());
	float c = dotProduct((Vector)transformedRay.getOrigin(), (Vector)transformedRay.getOrigin()) - 1.0f;
	float discriminant = (b * b) - (4.0f * a * c);

	if (discriminant > 0) {	//the ray intersects the sphere at two points
		intersections.m_intersections.push_back(Intersection((-b - sqrt(discriminant)) / (2.0f * a), this));
		intersections.m_intersections.push_back(Intersection((-b + sqrt(discriminant)) / (2.0f * a), this));
		intersections.m_intersectionCount += 2;
		return intersections.hit();
	}
	else if (discriminant == 0) { //the ray is a tangent to the sphere, intersects at a single point
	intersections.m_intersections.push_back(Intersection(-b / (2.0f * a), this));
	intersections.m_intersectionCount += 1;
	return intersections.hit();
	}
	else { //discriminant > 0, implying no ray-sphere intersection at all
	return intersections.hit();
	}
*/