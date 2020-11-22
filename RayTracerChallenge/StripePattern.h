#ifndef STRIPEPATTERN_H
#define STRIPEPATTERN_H

#include "Pattern.h"
#include "Color.h"

class StripePattern : public Pattern {
	private:
		Color m_color1;
		Color m_color2;
	public:
		StripePattern(const Color& color1, const Color& color2);

		Color getColor(const Point& localPoint) override;
};

#endif