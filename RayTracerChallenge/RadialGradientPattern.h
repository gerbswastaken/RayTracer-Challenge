#ifndef RADIALGRADIENTPATTERN_H
#define RADIALGRADIENTPATTERN_H

#include "Pattern.h"
#include "Color.h"

class RadialGradientPattern : public Pattern {
	private:
		Color m_color1;
		Color m_color2;
	public:
		RadialGradientPattern(const Color& color1, const Color& color2);
		RadialGradientPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2);

		Color getLocalColor(const Point& localPoint) override;
};

#endif

