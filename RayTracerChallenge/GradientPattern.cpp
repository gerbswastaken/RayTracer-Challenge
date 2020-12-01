#include "GradientPattern.h"

GradientPattern::GradientPattern(const Color& color1, const Color& color2) {
	m_color1 = color1;
	m_color2 = color2;
}

GradientPattern::GradientPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2) : Pattern(transformationMatrix){
	m_color1 = color1;
	m_color2 = color2;
}

Color GradientPattern::getLocalColor(const Point& localPoint) {
	Color colorDifference = (Color)(m_color2 - m_color1);
	float fractionX = localPoint.getX() - floor(localPoint.getX());
	return (Color)(m_color1 + (fractionX * colorDifference));
}