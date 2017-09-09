#include <Szczur/System/Color.h>

namespace Szczur {
	const Color Color::Black		(0,   0,   0  );
	const Color Color::White		(255, 255, 255);
	const Color Color::Gray			(128, 128, 128);
	const Color Color::Red			(255, 0,   0  );
	const Color Color::Green		(0,   255, 0  );
	const Color Color::Blue			(0,   0,   255);
	const Color Color::Yellow		(255, 255, 0  );
	const Color Color::Magenta		(255, 0,   255);
	const Color Color::Cyan			(0,   255, 255);
	const Color Color::Transparent	(0,  0,  0,  0);
	
	Color::Color() {
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}
	
	Color::Color(unsigned char gray, unsigned char alpha) {
		r = gray;
		g = gray;
		b = gray;
		a = alpha;
	}
	
	Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	
	Color::Color(sf::Color color) {
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	
	void Color::Set(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	
	static unsigned char Max(unsigned char a, unsigned char b) { return (a >= b) ? a : b; }
	static unsigned char Min(unsigned char a, unsigned char b) { return (a <= b) ? a : b; }
	
	int Color::Hue() {
		int max = Max(Max(r, g), b);
		int min = Min(Min(r, g), b);
		int val = (max - min) * 60;
		int hue;
		
		if		(max == r)	hue = ((g-b)*60)       / val;
		else if (max == g)	hue = ((b-r)*60 + 120) / val;
		else				hue = ((r-g)*60 + 240) / val;
		
		if (hue < 0) hue += 360;
		return hue;
	}
	
	unsigned char Color::Saturation() {
		int max = Max(Max(r, g), b);
		int min = Min(Min(r, g), b);
		if (max == 0) return 0;
		return 255 * (max - min) / max;
	}
	
	unsigned char Color::Value() {
		return Max(Max(r, g), b);
	}
	
	unsigned char Color::ToGray() {
		return (((unsigned int) r) + ((unsigned int) g) + ((unsigned int) b)) / 3;
	}
	
	
	Color Color::HSV(int hue, unsigned char sat, unsigned char val, unsigned char alpha) {
		if (sat == 0) return Color(0, 0, 0, alpha);
		
		unsigned char reg = hue / 43;
		unsigned char rem = (hue - (reg * 43)) * 6;
		unsigned char v = val;
		
		unsigned char  p = (val * (255 - sat)) >> 8;
		unsigned char  q = (val * (255 - ((sat * rem) >> 8))) >> 8;
		unsigned char  t = (val * (255 - ((sat * (255 - rem)) >> 8))) >> 8;
		
		if		(reg == 0)	return Color(v, t, p, alpha);
		else if (reg == 1)	return Color(q, v, p, alpha);
		else if (reg == 2)	return Color(p, v, t, alpha);
		else if (reg == 3)	return Color(p, q, v, alpha);
		else if (reg == 4)	return Color(t, p, v, alpha);
		else				return Color(v, p, q, alpha);
	}
	
	Color Color::Blend(Color col1, Color col2) {
		unsigned char r = (col1.r * col1.a / 255) + (col2.r * col2.a * (255 - col1.a) / (255*255));
		unsigned char g = (col1.g * col1.a / 255) + (col2.g * col2.a * (255 - col1.a) / (255*255));
		unsigned char b = (col1.b * col1.a / 255) + (col2.b * col2.a * (255 - col1.a) / (255*255));
		unsigned char a = col1.a + (col2.a * (255 - col1.a) / 255);
		return Color(r, g, b, a);
	}
	
	bool	Color::operator==	(const Color& col) { return (r == col.r && g == col.g && b == col.b && a == col.a); }
	bool	Color::operator!=	(const Color& col) { return (r != col.r || g != col.g || b != col.b || a != col.a); }
	
	Color	Color::operator+	(const Color& col) { return Color(r + col.r, g + col.g, b + col.b, a + col.a); }
	Color	Color::operator-	(const Color& col) { return Color(r - col.r, g - col.g, b - col.b, a - col.a); }
	Color	Color::operator*	(const Color& col) { return Color(r * col.r, g * col.g, b * col.b, a * col.a); }
	Color	Color::operator/	(const Color& col) { return Color(r / col.r, g / col.g, b / col.b, a / col.a); }
	
	Color&	Color::operator+=	(const Color& col) { r += col.r; g += col.g; b += col.b; a += col.a; return *this; }
	Color&	Color::operator-=	(const Color& col) { r -= col.r; g -= col.g; b -= col.b; a -= col.a; return *this; }
	Color&	Color::operator*=	(const Color& col) { r *= col.r; g *= col.g; b *= col.b; a *= col.a; return *this; }
	Color&	Color::operator/=	(const Color& col) { r /= col.r; g /= col.g; b /= col.b; a /= col.a; return *this; }
	
	Color::operator sf::Color() const { return sf::Color(r, g, b, a); }
}
