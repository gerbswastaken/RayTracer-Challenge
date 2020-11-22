#include "StripePattern.h"

StripePattern::StripePattern(const Color& color1, const Color& color2) {
	m_color1 = color1;
	m_color2 = color2;
}

Color StripePattern::getColor(const Point& localPoint) {
	if (((int)localPoint.getX()) % 2 == 0) return m_color1;
	return m_color2;
}