#ifndef CHECKERSPATTERN_H
#define CHECKERSPATTERN_H

#include "Color.h"
#include "Pattern.h"

#include <cmath>

class CheckersPattern : public Pattern {
	private:
		Color m_color1;
		Color m_color2;

	public:
		CheckersPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2);
		CheckersPattern(const Color& color1, const Color& color2);

		virtual Color getLocalColor(const Point& localPoint) override;
};

#endif

