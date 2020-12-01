#include "CheckersPattern.h"

CheckersPattern::CheckersPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2) : Pattern(transformationMatrix) {
	m_color1 = color1;
	m_color2 = color2;
}

CheckersPattern::CheckersPattern(const Color& color1, const Color& color2) {
	m_color1 = color1;
	m_color2 = color2;
}

Color CheckersPattern::getLocalColor(const Point& localPoint) {
	if ( (int)(floor(localPoint.getX()) + floor(localPoint.getY()) + floor(localPoint.getZ())) % 2 == 0) return m_color1;
	return m_color2;
}