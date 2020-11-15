#include "Material.h"

Material::Material() {
	m_color = Color(0.0f, 0.0f, 0.0f);
	m_ambient = 0.0f;
	m_specular = 0.0f;
	m_diffuse = 0.0f;
	m_shininess = 0.0f;
}

Material::Material(const Color& color, float ambient, float specular, float diffuse, float shininess) {
	m_color = color;
	m_ambient = ambient;
	m_specular = specular;
	m_diffuse = diffuse;
	m_shininess = shininess;
}

Material::~Material() {
	//Nothing in here for now
}