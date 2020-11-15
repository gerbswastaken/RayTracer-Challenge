#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector.h";
#include "Point.h";
#include "Tuple.h"

#include <iostream>

class Projectile {
	private:
		Point m_position;
		Vector m_velocity;

	public:
		Projectile() = delete;
		Projectile(const Point& position, const Vector& velocity);

		void changePosition(Point finalPosition);
		void updatePosition();

		Vector& getVelocity();
		Point& getPosition();

		friend std::ostream& operator<<(std::ostream& out, const Projectile& projectile);
};

#endif

