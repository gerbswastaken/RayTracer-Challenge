#ifndef CANVAS_H
#define CANVAS_H

#include "Tuple.h"
#include "Color.h"

#include <vector>

class Canvas {
	private:
		int m_width{};
		int m_height{};

		std::vector<Color> m_canvas;
		//Color* m_canvas;

	public:
		Canvas() = delete;
		Canvas(int width, int height);
		Canvas(int width, int height, const std::vector<Color>& colorArray);

		~Canvas();

		Color& getColor(int x, int y);
		void setColor(int x, int y, const Color& color);

		void clear(const Color& color);

		int getWidth() const;
		int getHeight() const;

};

#endif

