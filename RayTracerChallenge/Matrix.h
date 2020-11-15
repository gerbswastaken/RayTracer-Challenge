#ifndef MATRIX_H
#define MATRIX_H

#include "Point.h"
#include "Vector.h"
#include "Tuple.h"
#include "MathToolbox.h"
#include "Constants.h"

#include <vector>
#include <iostream>
#include <cmath>

class Matrix {
	private:
		int m_rows;
		int m_columns;
		int m_length;
		std::vector<float> m_matrix;
	public:
		Matrix();
		Matrix(int rows, int columns);
		Matrix(int rows, int columns, const std::vector<float>& matrix);
		Matrix(const Tuple& tuple);

		~Matrix();

		float& getElement(int row, int column);
		void setElement(int row, int column, float value);

		float getElement(int row, int column) const;

		friend bool areEqual(const Matrix& m1, const Matrix& m2);
		friend bool operator==(const Matrix& m1, const Matrix& m2);
		friend bool operator!=(const Matrix& m1, const Matrix& m2);

		friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

		friend Matrix operator*(const Matrix& m1, const Matrix& m2);
		friend Matrix operator*(float f1, const Matrix& m1);
		friend Matrix operator*(const Matrix& m1, float f1);
		friend Matrix operator/(const Matrix& m1, float f1);


		friend Tuple operator*(const Matrix& m1, const Tuple& t1);

		Matrix getTransposeMatrix() const;
		Matrix getInverseMatrix() const;
		void transpose();

		float getDeterminant() const;
		float getCofactor(int row, int column) const;

		static Matrix createIdentityMatrix(int order);

		Matrix getSubMatrix(int deleteRow, int deleteColumn) const;

		bool isSquareMatrix() const;
		bool isInvertible() const;

		//Matrix transformations
		static Matrix createTranslationMatrix(float xTransform, float yTransform, float zTransform);
		static Matrix createScalingMatrix(float xScale, float yScale, float zScale);
		static Matrix createRotationMatrix(char rotationAxis, float angle, bool clockwise);
		static Matrix createShearMatrix(float xProportionalY, float xProportionalZ, float yProportionalX, float yProportionalZ, float zProportionalX, float zProportionalY);
		static Matrix createViewTransformationMatrix(const Point& to, const Point& from, const Vector& up);
};

#endif

