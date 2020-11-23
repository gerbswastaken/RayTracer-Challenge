#include "Hitable.h"

Hitable::Hitable(int id, const Matrix& transformationMatrix, const Material& material) {
	m_id = id;
	m_transformationMatrix = transformationMatrix;
	m_material = material;
	m_savedRay = Ray(Point(0.0f, 0.0f, 0.0f), Vector(1.0f, 1.0f, 1.0f));
}

void Hitable::setSavedRay(const Ray& localRay) {
	m_savedRay = localRay;
}

Ray Hitable::getLocalRay(const Ray& incidentRay) {
	return incidentRay.getTransformedRay(this->getTransformationMatrix().getInverseMatrix());;
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

bool Hitable::hit(const Ray& ray, Intersections& intersections) {
	setSavedRay(getLocalRay(ray));
	return localIntersect(getLocalRay(ray), intersections);
}

Vector Hitable::getNormalAtPoint(const Point& point) {
	Point localPoint = ((this->getTransformationMatrix()).getInverseMatrix() * point);
	Vector localNormal = this->getLocalNormalAtPoint(localPoint);
	Vector worldNormal = (((this->getTransformationMatrix()).getInverseMatrix()).getTransposeMatrix() * localNormal);
	worldNormal[3] = 0.0f;
	return worldNormal.getNormalizedVector();
}

Color Hitable::getMaterialColor(const Point& point) {
	if (m_material.m_hasPattern) return m_material.m_pattern->getColor(point);
	return m_material.m_color;
}