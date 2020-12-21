#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Pattern;

class Material {
	public:
		Pattern* m_pattern;
		Color m_color;
		float m_ambient;
		float m_specular;
		float m_diffuse;
		float m_shininess;
		float m_reflectivity;
		float m_refractiveIndex;
		float m_transparency;

		bool m_hasPattern; //if true, then the material has a pattern
						   //if false, then the material has a color

		Material();
		Material(const Color& color, float ambient, float specular, float diffuse, float shininess, float reflectivity, float refractiveIndex, float transparency);
		Material(Pattern* pattern, float ambient, float specular, float diffuse, float shininess, float reflectivity, float refractiveIndex, float transparency);
		~Material();

};

#endif

