#ifndef NESTEDPATTERN_H
#define NESTEDPATTERN_H

#include "Pattern.h"

class NestedPattern : public Pattern {
	private:
		Pattern* m_pattern = nullptr;
		Pattern* m_nestedPattern = nullptr;

	public:
		NestedPattern(const Matrix& TransformationMatrix, Pattern* pattern, Pattern* nestedPattern);
		NestedPattern(Pattern* pattern, Pattern* nestedPattern);
		
		Color getLocalColor(const Point& localPoint) override;
		Color getColor(const Point& worldPoint, Hitable* object) override;
};

#endif

