#include "Vector.h"

Vector::Vector() : Tuple(0.0f,0.0f,0.0f,0.0f) {

}

Vector::Vector(float x, float y, float z) : Tuple(x, y, z, 0.0f) {

}

Vector::Vector(const Tuple& tuple) : Tuple(tuple.getX(), tuple.getY(), tuple.getZ(), 0.0f) {

}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
	out << "Vector( " << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ", " << vector.getW() << " )";
	return out;
}

float Vector::getMagnitude() const {
	return sqrt( (getX() * getX()) + (getY() * getY()) + (getZ() * getZ()) );
}

void Vector::normalize() {
	*this /= getMagnitude();
}

Vector Vector::getNormalizedVector() const {
	return ( *this / getMagnitude() );
}

Vector Vector::getReflectedVector(const Vector& vectorIn, const Vector& normal) {
	return (vectorIn - (2.0f * dotProduct(vectorIn, normal) * normal));
}