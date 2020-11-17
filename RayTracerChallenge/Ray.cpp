#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction) : m_origin{ origin }, m_direction{ direction } {
	//Nothin' in here for now LOL
}

Ray::Ray() {
	m_origin = Point(0.0f, 0.0f, 0.0f);
	m_direction = Vector(1.0f, 1.0f, 1.0f);
}

Ray::~Ray() {
	//Nothing in here for now LOL
}

const Point& Ray::getOrigin() const {
	return m_origin;
}

Point& Ray::getOrigin() {
	return m_origin;
}

const Vector& Ray::getDirection() const {
	return m_direction;
}

Vector& Ray::getDirection() {
	return m_direction;
}

std::ostream& operator<<(std::ostream& out, const Ray& ray) {
	out << "Ray | Origin:" << ray.getOrigin() << " | Direction:" << ray.getDirection();
	return out;
}

Point Ray::getPoint(float t) const {
	return (this->getOrigin() + (t * this->getDirection()));
}

Ray Ray::getTransformedRay(const Matrix& matrix) const{
	return Ray(matrix * (this->getOrigin()), matrix * (this->getDirection()) );
}