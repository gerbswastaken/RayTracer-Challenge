#ifndef PATTERN_H
#define PATTERN_H

#include "Hitable.h"
#include "Color.h"
#include "Point.h"
#include "Matrix.h"

#include <cmath>

class Pattern {
	private:
		Matrix m_transformationMatrix;
	public:
		Pattern();
		Pattern(const Matrix& transformationMatrix);

		Matrix getTransformationMatrix() const;
		void setTransformationMatrix(const Matrix& matrix);

		virtual Color getColor(const Point& worldPoint, Hitable* object);

		virtual Color getLocalColor(const Point& localPoint) = 0;
};

#endif