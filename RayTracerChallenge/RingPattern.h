#ifndef RINGPATTERN_H
#define RINGPATTERN_H

#include "Color.h"
#include "Pattern.h"

#include <cmath>

class RingPattern : public Pattern {
	private:
		Color m_color1;
		Color m_color2;
	public:
		RingPattern(const Color& color1, const Color& color2);
		RingPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2);

		Color getLocalColor(const Point& localPoint) override;
};

#endif

