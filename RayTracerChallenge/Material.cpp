#include "Material.h"

Material::Material() {
	m_hasPattern = false;
	m_color = Color(0.0f, 0.0f, 0.0f);
	m_ambient = 0.0f;
	m_specular = 0.0f;
	m_diffuse = 0.0f;
	m_shininess = 0.0f;
	m_reflectivity = 0.0f;
}

Material::Material(const Color& color, float ambient, float specular, float diffuse, float shininess, float reflectivity) {
	m_hasPattern = false;
	m_color = color;
	m_ambient = ambient;
	m_specular = specular;
	m_diffuse = diffuse;
	m_shininess = shininess;
	m_reflectivity = reflectivity;
}

Material::Material(Pattern* pattern, float ambient, float specular, float diffuse, float shininess, float reflectivity){
	m_hasPattern = true;
	m_pattern = pattern;
	m_ambient = ambient;
	m_specular = specular;
	m_diffuse = diffuse;
	m_shininess = shininess;
	m_reflectivity = reflectivity;
}

Material::~Material() {
	//Nothing in here for now
}