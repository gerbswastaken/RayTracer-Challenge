#include "BlendedPattern.h"

BlendedPattern::BlendedPattern(Pattern* pPattern1, Pattern* pPattern2) {
	m_pPattern1 = pPattern1;
	m_pPattern2 = pPattern2;
}

BlendedPattern::BlendedPattern(const Matrix& transformationMatrix, Pattern* pPattern1, Pattern* pPattern2) : Pattern(transformationMatrix){
	m_pPattern1 = pPattern1;
	m_pPattern2 = pPattern2;
}

Color BlendedPattern::getColor(const Point& worldPoint, Hitable* object) {
	//We first transform the point in world space, to that in object space.
	//We then transform it again according to the the Pattern's transformation matrix
	Point localPatternPoint = this->getTransformationMatrix().getInverseMatrix() * worldPoint;
	return (Color)((m_pPattern1->getColor(localPatternPoint, object) + m_pPattern2->getColor(localPatternPoint, object)) / 2.0f);
}

Color BlendedPattern::getLocalColor(const Point& localPoint) {
	return (Color)( (m_pPattern1->getLocalColor(localPoint) + m_pPattern2->getLocalColor(localPoint)) / 2.0f );
}
