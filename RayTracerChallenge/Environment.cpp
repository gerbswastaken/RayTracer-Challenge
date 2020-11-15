#include "Environment.h"

Environment::Environment(Vector gravity, Vector wind) {
	m_gravity = gravity;
	m_wind = wind;
}

Vector& Environment::getGravity() {
	return m_gravity;
}

Vector& Environment::getWind() {
	return m_wind;
}