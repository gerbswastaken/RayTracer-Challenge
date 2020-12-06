#include "SolidColorPattern.h"

SolidColorPattern::SolidColorPattern(const Color& color) {
	m_color = color;
}

SolidColorPattern::SolidColorPattern(const Matrix& transformationMatrix, const Color& color) : Pattern(transformationMatrix) {
	m_color = color;
}

Color SolidColorPattern::getLocalColor(const Point& localPoint) {
	return m_color;
}