#include "RadialGradientPattern.h"

RadialGradientPattern::RadialGradientPattern(const Color& color1, const Color& color2) {
	m_color1 = color1;
	m_color2 = color2;
}

RadialGradientPattern::RadialGradientPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2) : Pattern(transformationMatrix) {
	m_color1 = color1;
	m_color2 = color2;
}

Color RadialGradientPattern::getLocalColor(const Point& localPoint) {
	Color colorDifference = (Color)(m_color1 - m_color2);
	float fractionRadius = (sqrt((localPoint.getX() * localPoint.getX()) + (localPoint.getZ() * localPoint.getZ()))) - (int)(sqrt((localPoint.getX() * localPoint.getX()) + (localPoint.getZ() * localPoint.getZ())));
	return (Color)(m_color1 + (fractionRadius * colorDifference));
}