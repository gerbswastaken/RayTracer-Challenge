#ifndef PPMWRITER_H
#define PPMWRITER_H

#include "Canvas.h"
#include "Color.h"

#include <ctime> // For the Filename stuff
#include <iostream>
#include <fstream>

class PPMWriter {
	public:
		PPMWriter();

		void static generatePPM(Canvas& canvas);
};

#endif

