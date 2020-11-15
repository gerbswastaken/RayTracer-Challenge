#include "Matrix.h"

Matrix::Matrix() {
	m_rows = 3;
	m_columns = 3;
	m_length = 9;
	m_matrix.reserve(m_length);
	for (int i = 0; i < m_length; ++i) {
		m_matrix.push_back(0.0f);
	}

}

Matrix::Matrix(int rows, int columns) {
	m_rows = rows;
	m_columns = columns;
	m_length = rows * columns;
	m_matrix.reserve(m_length);
	for (int i = 0; i < m_length; ++i) {
		m_matrix.push_back(0.0f);
	}
}

Matrix::Matrix(int rows, int columns, const std::vector<float>& matrix) {
	m_rows = rows;
	m_columns = columns;
	m_length = rows * columns;
	m_matrix = matrix;	//Check if that works LOL
}

Matrix::Matrix(const Tuple& tuple) {
	m_rows = 4;
	m_columns = 1;
	m_length = 4;
	m_matrix.reserve(m_length);
	for (int i = 0; i < 4; ++i) {
		m_matrix.push_back(tuple[i]);
	}
}

Matrix::~Matrix() {
	//Nothing here for now -_-
}

float& Matrix::getElement(int row, int column) {
	if (row > 0 && row <= m_rows && column > 0 && column <= m_columns) {
		return m_matrix[(column - 1) + (m_columns * (row - 1) )];
	}
	std::cout << "Error Accessing Matrix: out of bounds exception! @ Row:" << row << " Column:" << column << '\n';
	return m_matrix[0];
}

float Matrix::getElement(int row, int column) const {
	if (row > 0 && row <= m_rows && column > 0 && column <= m_columns) {
		return m_matrix[(column - 1) + (m_columns * (row - 1) )];
	}
	std::cout << "Error Accessing Matrix: out of bounds exception! @ Row:" << row << " Column:" << column << '\n';
	return m_matrix[0];
}

void Matrix::setElement(int row, int column, float value) {
	if (row > 0 && row <= m_rows && column > 0 && column <= m_columns) {
		m_matrix[(column - 1) + ((row - 1) * m_columns)] = value;
	}
	else {
		std::cout << "Error Accessing Matrix: out of bounds exception! @ Row:" << row << " Column:" << column << '\n';
	}
}

bool Matrix::isSquareMatrix() const {
	return (m_rows == m_columns);
}

bool areEqual(const Matrix& m1, const Matrix& m2) {
	if (m1.m_columns != m2.m_columns || m1.m_rows != m2.m_rows) return false;
	for (int i = 0; i < m1.m_length; ++i) {
		if (!MathToolbox::equal(m1.m_matrix[i], m2.m_matrix[i])) return false;
	}
	return true;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
	return areEqual(m1, m2);
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
	return !(areEqual(m1,m2));
}

Matrix operator*(float f1, const Matrix& m1) {
	std::vector<float> newMatrix;
	newMatrix.reserve(m1.m_length);
	for (int i = 0; i < m1.m_length; ++i) {
		newMatrix.push_back(m1.m_matrix[i] * f1);
	}
	return Matrix(m1.m_rows, m1.m_columns, newMatrix);
}

Matrix operator*(const Matrix& m1, float f1) {
	return (f1 * m1);
}

Matrix operator/(const Matrix& m1, float f1) {
	std::vector<float> newMatrix;
	newMatrix.reserve(m1.m_length);
	for (int i = 0; i < m1.m_length; ++i) {
		newMatrix.push_back(m1.m_matrix[i] / f1);
	}
	return Matrix(m1.m_rows, m1.m_columns, newMatrix);
}

//Matrix Multiplication
Matrix operator*(const Matrix& m1, const Matrix& m2) {
	if (m1.m_columns != m2.m_rows) {
		std::cout << "Error Multiplying Matrices! m1.columns != m2.rows!\n";
		return m1;
	}
	int commonValue = m1.m_columns;
	int newMatrixRows = m1.m_rows;
	int newMatrixColumns = m2.m_columns;
	//Possible Memory Leak issue here! Fix!! (newMatrix is never deleted!) - Prolly convert to non-dynamically allocated array
	std::vector<float> newMatrix;
	newMatrix.reserve(newMatrixRows * newMatrixColumns);
	for (int r = 0; r < newMatrixRows; ++r) {
		for (int c = 0; c < newMatrixColumns; ++c) {
			float result = 0;
			for (int i = 0; i < commonValue; ++i) {
				result += (m1.getElement((r + 1), (i + 1)) * (m2.getElement((i + 1), (c + 1))));
			}
			newMatrix.push_back(result);
		}

	}
	return Matrix(m1.m_rows, m2.m_columns, newMatrix);
}

Tuple operator*(const Matrix& m1, const Tuple& t1) {
	return Tuple((m1 * (Matrix)t1).getElement(1,1), (m1 * (Matrix)t1).getElement(2, 1), (m1 * (Matrix)t1).getElement(3, 1), (m1 * (Matrix)t1).getElement(4, 1));
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
	for (int r = 0; r < m.m_rows; ++r) {
		for (int c = 0; c < m.m_columns; ++c) {
			out << m.getElement((r + 1), (c + 1)) << '\t';
		}
		out << '\n';
	}
	return out;
}

Matrix Matrix::createIdentityMatrix(int order) {
	std::vector<float> matrix;
	if (!(order > 0)) {
		std::cout << "Error creating Identity Matrix of order: " << order << "!\n";
		return Matrix(1, 1);
	}
	matrix.reserve(order * order);
	for (int i = 0; i < order * order; ++i) {
		matrix.push_back(0.0f);
	}
	for (int i = 0; i < order; ++i) {
		matrix[i + (i * order)] = 1.0f;
	}
	return Matrix(order, order, matrix);
}

Matrix Matrix::getTransposeMatrix() const {		//Check this!
	Matrix transposedMatrix(m_rows, m_columns);
	for (int r = 0; r < m_rows; ++r) {
		for (int c = 0; c < m_columns; ++c) {
			transposedMatrix.setElement((r + 1), (c + 1), getElement((c + 1), (r + 1)));
		}
	}
	return transposedMatrix;
}

void Matrix::transpose() {
	*this = getTransposeMatrix();
}


bool searchArray(const std::vector<int>& arrayToSearch, int arrayLength, int term) {	//Returns true if the term is found in the array
	for (int i = 0; i < arrayLength; ++i) {
		if (arrayToSearch[i] == term) return true;
	}
	return false;
}

Matrix Matrix::getSubMatrix(int deleteRow, int deleteColumn) const {
	std::vector<int> cellsToDelete;
	cellsToDelete.reserve(m_rows + m_columns);
	for (int i = 0; i < m_rows; ++i) {
		cellsToDelete.push_back( (deleteColumn - 1) + (i * m_rows) );
	}
	for (int i = 0; i < m_columns; ++i) {
		cellsToDelete.push_back( (i + ((deleteRow - 1) * m_rows)) );
	}

	std::vector<float> subMatrixArray;
	subMatrixArray.reserve((m_rows - 1) * (m_columns - 1));

	for (int r = 0; r < m_rows; ++r) {
		for (int c = 0; c < m_columns; ++c) {
			int currentIndex = (c + (r * m_rows));
			if (!searchArray(cellsToDelete, (m_rows + m_columns), currentIndex)) {
				subMatrixArray.push_back(m_matrix[currentIndex]);
			}
		}
	}

	return Matrix((m_rows - 1), (m_columns - 1), subMatrixArray);

}

float Matrix::getDeterminant() const {
	if (!isSquareMatrix()) {
		std::cout << "Error calculating Determinant! The Matrix is not a Square Matrix!\n";
		return 0.0f;
	}
	if (m_rows == 1 && m_columns == 1) {
		return m_matrix[0];
	}
	if (m_rows == 2 && m_columns == 2) {
		return((m_matrix[0] * m_matrix[3]) - (m_matrix[1] * m_matrix[2]));
	}

	//We'll only do the first row i guess lol
	float negation = 1.0f;
	float determinant = 0.0f;
	for (int i = 0; i < m_columns; ++i) {
		determinant += (negation * m_matrix[i] * getSubMatrix(1, i + 1).getDeterminant());
		negation *= -1.0f;
	}
	return determinant;
}

float Matrix::getCofactor(int row, int column) const{
	if ((row + column) % 2 == 0) { //even
		return getSubMatrix(row, column).getDeterminant();
	}
	//otherwise, return odd
	return (getSubMatrix(row, column).getDeterminant() * -1.0f);
}

bool Matrix::isInvertible() const {
	return !(getDeterminant() == 0);
}


Matrix Matrix::getInverseMatrix() const {
	if (isInvertible()) {
		std::vector<float> cofactorMatrix;
		cofactorMatrix.reserve(m_rows * m_columns);
		for (int r = 0; r < m_rows; ++r) { 
			for (int c = 0; c < m_columns; ++c) {
				cofactorMatrix.push_back(getCofactor((r+1), (c+1)));
			}
		}

		return ( Matrix(m_rows, m_columns, cofactorMatrix).getTransposeMatrix() / getDeterminant() );
		
	}
	std::cout << "The Matrix is NOT INVERTIBLE (Determinant = 0)\n";
	return Matrix::createIdentityMatrix(m_rows);
}

//Matrix Transformations

Matrix Matrix::createTranslationMatrix(float xTransform, float yTransform, float zTransform) {
	Matrix temp{ Matrix::createIdentityMatrix(4) };
	temp.setElement(1, 4, xTransform);
	temp.setElement(2, 4, yTransform);
	temp.setElement(3, 4, zTransform);

	return temp;
}

Matrix Matrix::createScalingMatrix(float xScale, float yScale, float zScale) {
	Matrix temp{ Matrix::createIdentityMatrix(4) };
	temp.setElement(1, 1, xScale);
	temp.setElement(2, 2, yScale);
	temp.setElement(3, 3, zScale);

	return temp;
}

Matrix Matrix::createRotationMatrix(char rotationAxis, float angle, bool clockwise) {
	Matrix temp{ Matrix::createIdentityMatrix(4) };

	switch (rotationAxis) {
	case 'x':
	case 'X':
		if (clockwise) {
			temp.setElement(2, 2, cos(angle));
			temp.setElement(2, 3, sin(angle));
			temp.setElement(3, 2, (-1.0f * sin(angle)) );
			temp.setElement(3, 3, cos(angle));
		}
		else {
			temp.setElement(2, 2, cos(angle));
			temp.setElement(2, 3, (-1.0f * sin(angle)));
			temp.setElement(3, 2, sin(angle));
			temp.setElement(3, 3, cos(angle));
		}
		break;

	case 'y':
	case 'Y':
		if (clockwise) {
			temp.setElement(1, 1, cos(angle));
			temp.setElement(1, 3, (-1.0f * sin(angle)));
			temp.setElement(3, 1, sin(angle));
			temp.setElement(3, 3, cos(angle));
		}
		else {
			temp.setElement(1, 1, cos(angle));
			temp.setElement(1, 3, sin(angle));
			temp.setElement(3, 1, (-1.0f * sin(angle)));
			temp.setElement(3, 3, cos(angle));
		}
		break;

	case 'z':
	case 'Z':
		if (clockwise) {
			temp.setElement(1, 1, cos(angle));
			temp.setElement(1, 2, sin(angle));
			temp.setElement(2, 1, (-1.0f * sin(angle)));
			temp.setElement(2, 2, cos(angle));
		}
		else {
			temp.setElement(1, 1, cos(angle));
			temp.setElement(1, 2, (-1.0f * sin(angle)));
			temp.setElement(2, 1, sin(angle));
			temp.setElement(2, 2, cos(angle));
		}
		break;

		break;

	default:
		std::cout << "Error in determining rotation axis! Returning Identity Matrix!\n";
		break;

	}

	return temp;
}

Matrix Matrix::createShearMatrix(float xProportionalY, float xProportionalZ, float yProportionalX, float yProportionalZ, float zProportionalX, float zProportionalY) {
	Matrix temp = Matrix::createIdentityMatrix(4);
	temp.setElement(1, 2, xProportionalY);
	temp.setElement(1, 3, xProportionalZ);
	temp.setElement(2, 1, yProportionalX);
	temp.setElement(2, 3, yProportionalZ);
	temp.setElement(3, 1, zProportionalX);
	temp.setElement(3, 2, zProportionalY);

	return temp;
}

Matrix Matrix::createViewTransformationMatrix(const Point& to, const Point& from, const Vector& up) {
	Matrix temp = Matrix::createIdentityMatrix(4);

	Vector forward = ((Vector)(to - from)).getNormalizedVector();
	Vector upVector = up.getNormalizedVector();
	Vector left = -crossProduct(forward, upVector);
	Vector trueUpVector = -crossProduct(left, forward);

	temp.setElement(1, 1, left.getX());
	temp.setElement(1, 2, left.getY());
	temp.setElement(1, 3, left.getZ());
	temp.setElement(2, 1, trueUpVector.getX());
	temp.setElement(2, 2, trueUpVector.getY());
	temp.setElement(2, 3, trueUpVector.getZ());
	temp.setElement(3, 1, -forward.getX());
	temp.setElement(3, 2, -forward.getY());
	temp.setElement(3, 3, -forward.getZ());

	return temp * Matrix::createTranslationMatrix(-from.getX(), -from.getY(), -from.getZ());
}
