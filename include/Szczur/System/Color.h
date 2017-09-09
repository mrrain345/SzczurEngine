#pragma once
#include <SFML/Graphics/Color.hpp>

namespace Szczur {
	class Color {
	public:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
		
		static const Color Black;
		static const Color White;
		static const Color Gray;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
		
		Color();
		Color(unsigned char gray, unsigned char alpha = 255);
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
		Color(sf::Color color);
		
		void Set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);
		
		int Hue();
		unsigned char Saturation();
		unsigned char Value();
		unsigned char ToGray();
		
		static Color HSV(int hue, unsigned char sat, unsigned char val, unsigned char alpha = 255);
		static Color Blend(Color col1, Color col2);
		
		bool	operator==	(const Color& col);
		bool	operator!=	(const Color& col);
		
		Color	operator+	(const Color& col);
		Color	operator-	(const Color& col);
		Color	operator*	(const Color& col);
		Color	operator/	(const Color& col);
		
		Color&	operator+=	(const Color& col);
		Color&	operator-=	(const Color& col);
		Color&	operator*=	(const Color& col);
		Color&	operator/=	(const Color& col);
		
		operator sf::Color() const;
	};
}
