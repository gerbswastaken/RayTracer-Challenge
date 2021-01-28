#include "Cube.h"

Cube::~Cube() {
	//Nothing in here for now
}

Cube::Cube(int id, const Matrix& transformationMatrix, const Material& material) : Hitable(id, transformationMatrix, material) { 

}

void Cube::checkAxis(float& t_min, float& t_max, float origin, float direction) {
	float t_minNumerator = (-1.0f - origin);
	float t_maxNumerator = (1.0f - origin);

	if (std::abs(direction) >= constants::gEpsilon) {
		t_min = t_minNumerator / direction;
		t_max = t_maxNumerator / direction;
	}
	else {
		t_min = t_minNumerator * 999999999.9f;	//Very Large numbers imply infinity
		t_max = t_maxNumerator * 999999999.9f;
	}

	if (t_min > t_max) {
		std::swap(t_min, t_max);
	}
}

bool Cube::localIntersect(const Ray& localRay, Intersections& intersections) {
	float x_tmin, x_tmax;
	Cube::checkAxis(x_tmin, x_tmax, localRay.getOrigin().getX(), localRay.getDirection().getX());
	float y_tmin, y_tmax;
	Cube::checkAxis(y_tmin, y_tmax, localRay.getOrigin().getY(), localRay.getDirection().getY());
	float z_tmin, z_tmax;
	Cube::checkAxis(z_tmin, z_tmax, localRay.getOrigin().getZ(), localRay.getDirection().getZ());

	float t_max = std::min({ x_tmax, y_tmax, z_tmax });
	float t_min = std::max({ x_tmin, y_tmin, z_tmin });

	if (t_min > t_max) {	//implies that the ray has completely missed the cube!
		//Hence, do nothing with intersections and stuff like that.
		return false;
	}

	intersections.m_intersections.push_back(Intersection(t_min, this));
	intersections.m_intersections.push_back(Intersection(t_max, this));
	intersections.m_intersectionCount += 2;
	return intersections.hit();
}

Vector Cube::getLocalNormalAtPoint(const Point& point) {
	float maxc = std::max({std::abs(point.getX()), std::abs(point.getY()), std::abs(point.getZ())});
	if (maxc == std::abs(point.getX())) {
		return Vector(point.getX(), 0.0f, 0.0f);
	}
	if (maxc == std::abs(point.getY())) {
		return Vector(0.0f, point.getY(), 0.0f);
	}
	return Vector(0.0f, 0.0f, point.getZ());
}