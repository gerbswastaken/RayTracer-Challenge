#ifndef INTERSECTION_H
#define INTERSECTION_H

class Hitable;

class Intersection {
	private:
		float m_parameter;
		Hitable* m_object;
	public:
		Intersection() = delete;
		Intersection(float parameter, Hitable* object);
		~Intersection();

		float getParameter() const;

		Hitable* getObject() const;

};

#endif

