#ifndef COLOR_H
#define COLOR_H

#include "Vector.h"

#include <iostream>

class Color : public Vector {
	public:
		Color();
		Color(float red, float green, float blue);
		Color(const Vector& vector);

		float getRed() const;
		float getGreen() const;
		float getBlue() const;
		
		friend std::ostream& operator<<(std::ostream& out, const Color& color);

		static Color halamardProduct(const Color& c1, const Color& c2);

};

#endif

