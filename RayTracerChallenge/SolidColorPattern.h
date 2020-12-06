#ifndef SOLIDCOLORPATTERN_H
#define SOLIDCOLORPATTERN_H

#include "Pattern.h"

class SolidColorPattern : public Pattern {
	private:
		Color m_color;
	public:
		SolidColorPattern(const Matrix& transformationMatrix, const Color& color);
		SolidColorPattern(const Color& color);

		Color getLocalColor(const Point& localPoint) override;
};

#endif

