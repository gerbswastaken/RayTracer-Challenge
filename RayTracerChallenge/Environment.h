#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Vector.h";
#include "Tuple.h";

class Environment {
	private:
		Vector m_gravity;
		Vector m_wind;
	public:
		Environment(Vector gravity, Vector wind);

		Vector& getGravity();
		Vector& getWind();

};

#endif

