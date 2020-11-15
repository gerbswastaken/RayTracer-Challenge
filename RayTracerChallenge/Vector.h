#ifndef VECTOR_H
#define VECTOR_H

#include "Tuple.h"

class Vector : public Tuple {
	public:
		Vector();
		Vector(float x, float y, float z);
		Vector(const Tuple& tuple);

		friend std::ostream& operator<<(std::ostream& out, const Vector& vector); 

		float getMagnitude() const override;

		Vector getNormalizedVector() const;

		static Vector getReflectedVector(const Vector& vectorIn, const Vector& normal);

		void normalize() override;
};

#endif

