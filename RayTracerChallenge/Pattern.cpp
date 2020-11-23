#include "Pattern.h"

Pattern::Pattern() {
	m_transformationMatrix = Matrix::createIdentityMatrix(4);
}

Pattern::Pattern(const Matrix& transformationMatrix) {
	m_transformationMatrix = transformationMatrix;
}

Matrix Pattern::getTransformationMatrix() const {
	return m_transformationMatrix;
}

void Pattern::setTransformationMatrix(const Matrix& matrix) {
	m_transformationMatrix = matrix;
}

Color Pattern::getColor(const Point& worldPoint, Hitable* object) {
	//We first transform the point in world space, to that in object space.
	//We then transform it again according to the the Pattern's transformation matrix
	Point localPatternPoint = m_transformationMatrix.getInverseMatrix() * object->getTransformationMatrix().getInverseMatrix() * worldPoint;
	return getLocalColor(localPatternPoint);
}