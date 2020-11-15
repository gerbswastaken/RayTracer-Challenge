#include "Tuple.h"

float& Tuple::operator[](int index) {
	if (index >= 0 && index < 4) {
		return m_tuple[index];
	}
	std::cout << "Error! Accessing A member outside Tuple array!\n";
	return m_tuple[3];
}

bool Tuple::isVector() const {
	return (MathToolbox::equal(getW(), 0.0f));
}

bool Tuple::isPoint() const {
	return (MathToolbox::equal(getW(), 1.0f));
}

float Tuple::getX() const{
	return m_tuple[0];
}

float Tuple::getY() const {
	return m_tuple[1];
}

float Tuple::getZ() const {
	return m_tuple[2];
}

float Tuple::getW() const {
	return m_tuple[3];
}

float Tuple::operator[](int index) const {
	if (index >= 0 && index < 4) {
		return m_tuple[index];
	}
	std::cout << "Error! Accessing A member outside Tuple array!\n";
	return m_tuple[3];
}

Tuple::Tuple(float x, float y, float z, float w) {
	m_tuple[0] = x;
	m_tuple[1] = y;
	m_tuple[2] = z;
	m_tuple[3] = w;
}

Tuple::Tuple(const Tuple& tuple) {
	m_tuple[0] = tuple.getX();
	m_tuple[1] = tuple.getY();
	m_tuple[2] = tuple.getZ();
	m_tuple[3] = tuple.getW();
}

bool isEqual(const Tuple& t1, const Tuple& t2) {
	for(int i = 0; i < 4; i++) {
		if (!MathToolbox::equal(t1.m_tuple[i], t2.m_tuple[i])) return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& out, const Tuple& tuple) {
	out << "Tuple( " << tuple.m_tuple[0] << ", " << tuple.m_tuple[1] << ", " << tuple.m_tuple[2] << ", " << tuple.m_tuple[3] << " )";
	return out;
}


//Addition
void Tuple::operator+=(const Tuple& tuple) {
	m_tuple[0] += tuple.getX();
	m_tuple[1] += tuple.getY();
	m_tuple[2] += tuple.getZ();
	m_tuple[3] += tuple.getW();
}

Tuple operator+(const Tuple& t1, const Tuple& t2) {
	return Tuple(t1.m_tuple[0] + t2.m_tuple[0], t1.m_tuple[1] + t2.m_tuple[1], t1.m_tuple[2] + t2.m_tuple[2], t1.m_tuple[3] + t2.m_tuple[3]);
}

//Subtraction
Tuple operator-(const Tuple& t1, const Tuple& t2) {
	return Tuple(t1.m_tuple[0] - t2.m_tuple[0], t1.m_tuple[1] - t2.m_tuple[1], t1.m_tuple[2] - t2.m_tuple[2], t1.m_tuple[3] - t2.m_tuple[3]);
}

void Tuple::operator-=(const Tuple& tuple) {
	m_tuple[0] -= tuple.getX();
	m_tuple[1] -= tuple.getY();
	m_tuple[2] -= tuple.getZ();
	m_tuple[3] -= tuple.getW();
}

//Negation
Tuple Tuple::operator-()
{
	return Tuple(-m_tuple[0], -m_tuple[1], -m_tuple[2], -m_tuple[3]);
}

//Scalar Multiplication
Tuple operator*(const Tuple& tuple, float f) {
	return Tuple((tuple.getX() * f), (tuple.getY() * f), (tuple.getZ() * f), (tuple.getW() * f));
}

Tuple operator*(float f, const Tuple& tuple) {
	return Tuple((tuple.getX() * f), (tuple.getY() * f), (tuple.getZ() * f), (tuple.getW() * f));
}

void Tuple::operator*=(float f) {
	m_tuple[0] *= f;
	m_tuple[1] *= f;
	m_tuple[2] *= f;
	m_tuple[3] *= f;
}

//Scalar Divison
Tuple operator/(const Tuple& tuple, float f) {
	return Tuple((tuple.getX() / f), (tuple.getY() / f), (tuple.getZ() / f), (tuple.getW() / f));
}

void Tuple::operator/=(float f) {
	m_tuple[0] /= f;
	m_tuple[1] /= f;
	m_tuple[2] /= f;
	m_tuple[3] /= f;
}

//Dot Product
float dotProduct(const Tuple& t1, const Tuple& t2) {
	if (t1.getW() == 0 && t2.getW() == 0) {
		return( (t1.getX() * t2.getX()) + (t1.getY() * t2.getY()) + (t1.getZ() * t2.getZ()) );
	}
	std::cout << "Error calculating dot product with non-vector tuples!\n";
	return 0.0f;
}

//Cross Product
Tuple crossProduct(const Tuple& t1, const Tuple& t2) {
	if (t1.getW() == 0 && t2.getW() == 0) {
		float crossX = (t1.getY() * t2.getZ() - t1.getZ() * t2.getY());
		float crossY = (t1.getZ() * t2.getX() - t1.getX() * t2.getZ());
		float crossZ = (t1.getX() * t2.getY() - t1.getY() * t2.getX());
		return Tuple(crossX, crossY, crossZ, 0.0f);
	}
	std::cout << "Error calculating cross product with non-vector tuples!\n";
	return Tuple(0.0f,0.0f,0.0f,0.0f);
}

//Magnitudes and Normalization
float Tuple::getMagnitude() const {
	return sqrt( (m_tuple[0] * m_tuple[0]) + (m_tuple[1] * m_tuple[1]) + (m_tuple[2] * m_tuple[2]) + (m_tuple[3] * m_tuple[3]));
}

Tuple Tuple::getNormalizedTuple() const {
	return (*this / getMagnitude()) ;
}

void Tuple::normalize() {
	*this /= getMagnitude();
}
