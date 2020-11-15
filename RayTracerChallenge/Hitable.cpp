#include "Hitable.h"

Hitable::Hitable(int id, const Matrix& transformationMatrix, const Material& material) {
	m_id = id;
	m_transformationMatrix = transformationMatrix;
	m_material = material;
}

int Hitable::getID() const {
	return m_id;
}

Matrix Hitable::getTransformationMatrix() const {
	return m_transformationMatrix;
}

void Hitable::setTransformationMatrix(const Matrix& transformationMatrix) {
	m_transformationMatrix = transformationMatrix;
}

Material Hitable::getMaterial() const {
	return m_material;
}

void Hitable::setMaterial(const Material& material) {
	m_material = material;
}