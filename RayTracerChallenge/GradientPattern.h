#include "Pattern.h"
#include "Color.h"

class GradientPattern : public Pattern {
	private: 
		Color m_color1;
		Color m_color2;
	public:
		GradientPattern(const Color& color1, const Color& color2);
		GradientPattern(const Matrix& transformationMatrix, const Color& color1, const Color& color2);

		Color getLocalColor(const Point& localPoint) override;
};

