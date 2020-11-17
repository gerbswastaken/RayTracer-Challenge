#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"
#include "Material.h"
#include "Matrix.h"
#include "Vector.h"
#include "Intersections.h"

class Hitable {
	private:
		int m_id;
		Matrix m_transformationMatrix;
		Material m_material;
		Ray m_savedRay;

	public:
		Hitable(int id, const Matrix& transformationMatrix, const Material& material);

		int getID() const;
		Matrix getTransformationMatrix() const;
		void setTransformationMatrix(const Matrix& transformationMatrix);
		Material getMaterial() const;
		void setMaterial(const Material& material);
		void setSavedRay(const Ray& localRay);

		virtual Ray getLocalRay(const Ray& incidentRay);

		virtual bool localIntersect(const Ray& localRay, Intersections& intersections) = 0;
		virtual bool hit(const Ray& ray, Intersections& intersections);

		virtual Vector getLocalNormalAtPoint(const Point& point) = 0;
		virtual Vector getNormalAtPoint(const Point& point);
		

};

#endif

