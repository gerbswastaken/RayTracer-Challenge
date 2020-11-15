#ifndef MATHTOOLBOX_H
#define MATHTOOLBOX_H

#include "Constants.h"

#include <cmath>

class MathToolbox {
	public:
		static bool equal(float a, float b) {
			return (std::abs(a - b) < constants::gEpsilon);
		}
};

#endif
