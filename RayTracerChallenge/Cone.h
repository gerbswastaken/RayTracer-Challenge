#ifndef CONE_H
#define CONE_H

#include "Hitable.h"

//This implementation of a cone is in the form of right circular cone (45deg polar angle)
//With an upper and lower cone, similar to the figure that conic sections are defined from

class Cone : public Hitable {
	private:
		bool m_isClosed;
		float m_yMin;
		float m_yMax;
	public:
		Cone(int id, const Matrix& transformationMatrix, const Material& material);
		Cone(bool isClosed, float yMin, float yMax, int id, const Matrix& transformationMatrix, const Material& material);
		~Cone();

		bool checkCapIntersection(const Ray& ray, float parameter);
		void intersectCaps(const Ray& localRay, Intersections& intersections);

		bool localIntersect(const Ray& localRay, Intersections& intersections) override;
		Vector getLocalNormalAtPoint(const Point& point) override;

};

#endif

