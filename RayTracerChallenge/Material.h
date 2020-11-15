#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material {
	public:
		Color m_color;
		float m_ambient;
		float m_specular;
		float m_diffuse;
		float m_shininess;

		Material();
		Material(const Color& color, float ambient, float specular, float diffuse, float shininess);
		~Material();

};

#endif

