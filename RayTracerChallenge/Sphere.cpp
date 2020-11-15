#include "Sphere.h"

Sphere::Sphere(int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material){

}


Sphere::~Sphere() {
	//Nothing in here for now
}


Vector Sphere::getNormalAtPoint(const Point& point) {
	std::cout << "getNormalAtPoint for Sphere called!\n";
	//Here, (0,0,0) is the center of the circle!
	
	//objectPoint is the position of point once we transform the scene such that the sphere is at origin, and radius = 1
	Point objectPoint = ((this->getTransformationMatrix()).getInverseMatrix() * point);
	//objectNormal is the normal of the sphere at the given point, present in the Object's Space coordinate system
	Vector objectNormal = ((Vector)(objectPoint - Point(0.0f, 0.0f, 0.0f)));
	Vector worldNormal = (((this->getTransformationMatrix()).getInverseMatrix()).getTransposeMatrix() * objectNormal);
	worldNormal[3] = 0.0f;

	return worldNormal.getNormalizedVector();
}

bool Sphere::hit(const Ray& ray, Intersections& intersections) {
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
		/*
		parameterList.push_back((-b - sqrt(discriminant)) / (2.0f * a));
		parameterList.push_back((-b + sqrt(discriminant)) / (2.0f * a));
		intersectionCount = 2;
		*/
	}
	else if (discriminant == 0) { //the ray is a tangent to the sphere, intersects at a single point
		intersections.m_intersections.push_back(Intersection( -b / (2.0f * a), this));
		intersections.m_intersectionCount += 1;
		return intersections.hit();
		/*
		parameterList.push_back(-b / (2.0f * a));
		intersectionCount = 1;
		*/
	}
	else { //discriminant > 0, implying no ray-sphere intersection at all
		return intersections.hit();
		//intersectionCount = 0;
	}
}

 /*
std::vector<float> Sphere::getIntersectionParameters(const Ray& ray, int& intersectionCount) {
	std::vector<float> parameterList;
	parameterList.reserve(2);

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

	float a = dotProduct(ray.getDirection(), ray.getDirection());
	float b = 2.0f * dotProduct(ray.getDirection(), (Vector)ray.getOrigin());
	float c = dotProduct((Vector)ray.getOrigin(), (Vector)ray.getOrigin()) - 1.0f;
	float discriminant = (b * b) - (4.0f * a * c);

	if (discriminant > 0) {	//the ray intersects the sphere at two points
		parameterList.push_back((-b - sqrt(discriminant)) / (2.0f * a));
		parameterList.push_back((-b + sqrt(discriminant)) / (2.0f * a));
		intersectionCount = 2;
	}
	else if (discriminant == 0) { //the ray is a tangent to the sphere, intersects at a single point
		parameterList.push_back(-b / (2.0f * a));
		intersectionCount = 1;
	}
	else { //discriminant > 0, implying no ray-sphere intersection at all
		intersectionCount = 0;
	}
	return parameterList;
}

*/

