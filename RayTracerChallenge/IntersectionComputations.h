#ifndef INTERSECTIONCOMPUTATIONS_H
#define INTERSECTIONCOMPUTATIONS_H

#include "Hitable.h"
#include "Vector.h"
#include "Point.h"
#include "Intersection.h"
#include "Ray.h"

#include "Constants.h"

class IntersectionComputations {
	public:
		//If the ray strikes the surface from the inside of said object, then the normal needs to be inverted!
		bool m_insideObject;
		float m_parameter;
		Hitable* m_object;
		Point m_intersectionPoint;
		Point m_pointOverIntersection;
		Point m_pointUnderIntersection;
		Vector m_eyeVector;
		Vector m_normalAtIntersectionPoint;
		Vector m_reflectedVector;
		//For Refractions
		std::vector<Hitable*> m_intersectionObjectContainer;
		float m_n1;
		float m_n2;

		IntersectionComputations(const Ray& ray, const Intersection& intersection, const Intersections& intersections);
		IntersectionComputations();

		void prepareComputations(const Ray& ray, const Intersection& intersection, const Intersections& intersections);

};

#endif
