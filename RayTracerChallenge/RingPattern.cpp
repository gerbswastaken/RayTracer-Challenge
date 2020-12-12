#include "RingPattern.h"

RingPattern::RingPattern(const Color& color1, const Color& color2) {
	m_color1 = color1;
	m_color2 = color2;
}

RingPattern::RingPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2) : Pattern(transformationMatrix) {
	m_color1 = color1;
	m_color2 = color2;
}

Color RingPattern::getLocalColor(const Point& localPoint) {
	if (((int)sqrt((localPoint.getX() * localPoint.getX()) + (localPoint.getZ() * localPoint.getZ()))) % 2 == 0) return m_color1;
	return m_color2;
}