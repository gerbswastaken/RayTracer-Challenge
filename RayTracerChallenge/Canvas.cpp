#include "Canvas.h"

Canvas::Canvas(int width, int height) {
	m_width = width;
	m_height = height;

	m_canvas.reserve(width * height);
}

Canvas::Canvas(int width, int height, const std::vector<Color>& colorArray) {
	m_width = width;
	m_height = height;
	m_canvas = colorArray;
}



Canvas::~Canvas() {
	//Nothing in here for now
}

void Canvas::setColor(int x, int y, const Color& color) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
		m_canvas[x + (y * m_width)] = color;
	}
	else {
		std::cout << "Accessing a Pixel out of the Canvas! | X: " << x << " | Y: " << y << '\n';
	}
}

Color& Canvas::getColor(int x, int y) {
	if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
		return m_canvas[x + (y * m_width)];
	}
	std::cout << "Accessing a Pixel out of the Canvas! | X: " << x << " | Y: " << y << '\n';
	std::cout << "Returning Pixel (0,0) \n";
	return m_canvas[0];
	
}

int Canvas::getWidth() const {
	return m_width;
}

int Canvas::getHeight() const {
	return m_height;
}

void Canvas::clear(const Color& color) {
	for (int i = 0; i < (m_width * m_height); ++i) {
		m_canvas.push_back(Color(0.0f,0.0f,0.0f));
	}
}