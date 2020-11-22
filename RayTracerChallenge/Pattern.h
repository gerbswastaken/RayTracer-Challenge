#ifndef PATTERN_H
#define PATTERN_H

#include "Color.h"
#include "Constants.h"
#include "Point.h"

class Pattern {
	public:
		Pattern();
		virtual Color getColor(const Point& localPoint) = 0;
};

#endif