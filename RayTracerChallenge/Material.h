#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Pattern.h"

class Material {
	public:
		Pattern* m_pattern;
		Color m_color;
		float m_ambient;
		float m_specular;
		float m_diffuse;
		float m_shininess;

		bool m_hasPattern; //if true, then the material has a pattern
						   //if false, then the material has a color

		Material();
		Material(const Color& color, float ambient, float specular, float diffuse, float shininess);
		Material(Pattern* pattern, float ambient, float specular, float diffuse, float shininess);
		~Material();

};

#endif

