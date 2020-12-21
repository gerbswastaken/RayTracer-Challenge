#include "Material.h"

Material::Material() {
	m_hasPattern = false;
	m_color = Color(0.0f, 0.0f, 0.0f);
	m_ambient = 0.0f;
	m_specular = 0.0f;
	m_diffuse = 0.0f;
	m_shininess = 0.0f;
	m_reflectivity = 0.0f;
	m_refractiveIndex = 1.0f;
	m_transparency = 0.0f;
}

Material::Material(const Color& color, float ambient, float specular, float diffuse, float shininess, float reflectivity, float refractiveIndex, float transparency) {
	m_hasPattern = false;
	m_color = color;
	m_ambient = ambient;
	m_specular = specular;
	m_diffuse = diffuse;
	m_shininess = shininess;
	m_reflectivity = reflectivity;
	m_refractiveIndex = refractiveIndex;
	m_transparency = transparency;

}

Material::Material(Pattern* pattern, float ambient, float specular, float diffuse, float shininess, float reflectivity, float refractiveIndex, float transparency){
	m_hasPattern = true;
	m_pattern = pattern;
	m_ambient = ambient;
	m_specular = specular;
	m_diffuse = diffuse;
	m_shininess = shininess;
	m_reflectivity = reflectivity;
	m_refractiveIndex = refractiveIndex;
	m_transparency = transparency;
}

Material::~Material() {
	//Nothing in here for now
}