#ifndef BLENDEDPATTERN_H
#define BLENDEDPATTERN_H

#include "Pattern.h"

class BlendedPattern : public Pattern {
	private:
		Pattern* m_pPattern1;
		Pattern* m_pPattern2;
	public:
		BlendedPattern(Pattern* pPattern1, Pattern* pPattern2);
		BlendedPattern(const Matrix& transformationMatrix, Pattern* pPattern1, Pattern* pPattern2);

		Color getColor(const Point& worldPoint, Hitable* object) override;

		Color getLocalColor(const Point& localPoint) override;
};

#endif

