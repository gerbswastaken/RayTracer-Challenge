#include "Projectile.h"

Projectile::Projectile(const Point& position, const Vector& velocity) {
	m_position = position;
	m_velocity = velocity;
}

void Projectile::changePosition(Point finalPosition) {
	m_position = finalPosition;
}

void Projectile::updatePosition() {
	m_position += m_velocity;
}

Vector& Projectile::getVelocity() {
	return m_velocity;
}

Point& Projectile::getPosition() {
	return m_position;
}

std::ostream& operator<<(std::ostream& out, const Projectile& projectile) {
	out << "Projectile's Position: " << projectile.m_position << " | Projectile's Velocity: " << projectile.m_velocity << " | Projectile's Speed: "<< (projectile.m_velocity).getMagnitude() << '\n';
	return out;
}