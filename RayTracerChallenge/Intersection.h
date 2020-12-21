#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "MathToolbox.h"

class Hitable;

class Intersection {
	private:
		float m_parameter;
		Hitable* m_object;
	public:

		Intersection() = delete;
		Intersection(float parameter, Hitable* object);
		~Intersection();

		float getParameter() const;

		friend bool operator== (const Intersection& intersection1, const Intersection& intersection2);

		Hitable* getObject() const;

};

#endif

