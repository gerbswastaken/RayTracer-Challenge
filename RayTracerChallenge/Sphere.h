#ifndef SPHERE_H
#define SPHERE_H

#include "Point.h"
#include "Ray.h"
#include "Matrix.h"
#include "Material.h"
#include "Intersections.h"

#include "Hitable.h"

#include <vector>

class Sphere : public Hitable {
	private:
		int m_id;
		//The implementation of the Sphere is one at (0,0,0) with a unit radius
		//We'll move it around using matrix transformations
		Point m_center { 0.0f,0.0f,0.0f };
		float m_radius{ 1.0f };
		Matrix m_transformationMatrix{ Matrix::createIdentityMatrix(4) };
		Material m_material;

	public:
		Sphere() = delete;
		Sphere(int id, const Matrix& transformationMatrix, const Material& material);
		~Sphere();

		Vector getNormalAtPoint(const Point& point) override;

		bool hit(const Ray& ray, Intersections& intersections) override;
};

#endif

