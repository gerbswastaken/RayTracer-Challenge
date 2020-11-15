#ifndef TUPLE_H
#define TUPLE_H

#include "MathToolbox.h"

#include <iostream>
#include <cmath>


class Tuple {
	private:
		float m_tuple[4] {0.0f,0.0f,0.0f,0.0f};

	public:
		float& operator[](int index);
		float getX() const;
		float getY() const;
		float getZ() const;
		//W = 0 is Vector, W = 1 is a Point, W = 2 is a Color
		float getW() const;

		Tuple(float x, float y, float z, float w);
		Tuple(const Tuple& tuple);

		bool isVector() const;
		bool isPoint() const;

		float operator[](int index) const;

		friend std::ostream& operator<<(std::ostream& out, const Tuple& tuple);

		friend bool isEqual(const Tuple& t1, const Tuple& t2);

		//Adding Tuples together
		friend Tuple operator+(const Tuple& t1, const Tuple& t2);
		void operator+=(const Tuple& tuple);

		//Subtracting Tuples
		friend Tuple operator-(const Tuple& t1, const Tuple& t2);
		void operator-=(const Tuple& tuple);

		//Negating a Tuple
		Tuple operator-();

		//Scalar Multiplication
		friend Tuple operator*(const Tuple& tuple, float f);
		friend Tuple operator*(float f, const Tuple& tuple);
		void operator*=(float f);

		//Scalar Division
		friend Tuple operator/(const Tuple& tuple, float f);
		void operator/=(float f);

		//Dot Product (only with vectors!)
		friend float dotProduct(const Tuple& t1, const Tuple& t2);
		//Cross Product (only with vectors!)
		friend Tuple crossProduct(const Tuple& t1, const Tuple& t2);

		//Calculating Vector Magnitudes
		virtual float getMagnitude() const;
		Tuple getNormalizedTuple() const;
		virtual void normalize();


};

#endif