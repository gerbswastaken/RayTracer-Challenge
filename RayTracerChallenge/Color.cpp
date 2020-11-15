#include "Color.h"

Color::Color() : Vector (0.0f,0.0f,0.0f) {

}

Color::Color(float red, float green, float blue) : Vector(red, green, blue) {

}

Color::Color(const Vector& vector) : Vector(vector) {

}

float Color::getRed() const {
	return getX();
}

float Color::getGreen() const {
	return getY();
}

float Color::getBlue() const {
	return getZ();
}

std::ostream& operator<<(std::ostream& out, const Color& color) {
	out << "Color[RGB]( " << color.getRed() << ", " << color.getGreen() << ", " << color.getBlue() << " )";
	return out;
}

Color Color::halamardProduct(const Color& c1, const Color& c2) {
	return Color( (c1.getRed() * c2.getRed()), (c1.getGreen() * c2.getGreen()), (c1.getBlue() * c2.getBlue()) );
}