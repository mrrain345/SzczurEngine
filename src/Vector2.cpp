#include <Szczur/System/Vector2.h>

namespace Szczur {
	const Vector2 Vector2::Down	( 0,  1);
	const Vector2 Vector2::Left	(-1,  0);
	const Vector2 Vector2::Right( 1,  0);
	const Vector2 Vector2::Up	( 0, -1);
	const Vector2 Vector2::Zero	( 0,  0);
	const Vector2 Vector2::One	( 1,  1);

	Vector2::Vector2() {
		this->x = 0;
		this->y = 0;
	}
	
	Vector2::Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
	Vector2::Vector2(sf::Vector2f vector) {
		this->x = vector.x;
		this->y = vector.y;
	}
	
	Vector2::Vector2(sf::Vector2i vector) {
		this->x = vector.x;
		this->y = vector.y;
	}
	
	Vector2::Vector2(sf::Vector2u vector) {
		this->x = vector.x;
		this->y = vector.y;
	}
	
	void Vector2::Set(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
	float Vector2::Magnitude() {
		return sqrt(x*x + y*y);
	}
	
	float Vector2::SqrMagnitude() {
		return x*x + y*y;
	}
	
	float Vector2::Angle() {
		return acos(x / Magnitude()) * (180/M_PI);
	}
	
	
	
	Vector2 Vector2::Normalized() {
		float magnitude = Magnitude();
		return Vector2(x/magnitude, y/magnitude);
	}
	
	Vector2 Vector2::Scaled(Vector2 scale) {
		return Vector2(x * scale.x, y * scale.y);
	}
	
	Vector2 Vector2::ClampedMagnitude(float maxLength) {
		if (SqrMagnitude() <= maxLength * maxLength) return Vector2(x, y);
		Vector2 vector = Normalized();
		return vector * maxLength;
	}
	
	Vector2 Vector2::Rounded() {
		float vx = (x >= 0) ? (int)(x + 0.5f) : (int)(x - 0.5f);
		float vy = (y >= 0) ? (int)(y + 0.5f) : (int)(y - 0.5f);
		return Vector2(vx, vy);
	}
	
	Vector2 Vector2::Rotated(float angle) {
		float x = this->x * cos(angle) - this->y * sin(angle);
		float y = this->x * sin(angle) + this->y * cos(angle);
		return Vector2(x, y);
	}
	
	
	
	void Vector2::Normalize() {
		float magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
	}
	
	void Vector2::Scale(Vector2 scale) {
		x *= scale.x;
		y *= scale.y;
	}
	
	void Vector2::Round() {
		x = (x >= 0) ? (int)(x + 0.5f) : (int)(x - 0.5f);
		y = (y >= 0) ? (int)(y + 0.5f) : (int)(y - 0.5f);
	}
	
	void Vector2::ClampMagnitude(float maxLength) {
		if (SqrMagnitude() <= maxLength * maxLength) return;
		Normalize();
		(*this) *= maxLength;
	}
	
	void Vector2::Rotate(float angle) {
		float x = this->x * cos(angle) - this->y * sin(angle);
		float y = this->x * sin(angle) + this->y * cos(angle);
		Set(x, y);
	}
	
	
	
	Vector2 Vector2::Max(Vector2 vec1, Vector2 vec2) {
		if (vec1 >= vec2) return vec1;
		else return vec2;
	}
	
	Vector2 Vector2::Min(Vector2 vec1, Vector2 vec2) {
		if (vec1 <= vec2) return vec1;
		else return vec2;
	}
	
	float Vector2::Distance(Vector2 vec1, Vector2 vec2) {
		return (vec1 - vec2).Magnitude();
	}
	
	float Vector2::Dot(Vector2 vec1, Vector2 vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}
	
	float Vector2::Angle(Vector2 vec1, Vector2 vec2) {
		float mag = sqrt(vec1.SqrMagnitude() * vec2.SqrMagnitude());
		return acos(Dot(vec1, vec2) / mag) * (180/M_PI);
	}
	
	
	Vector2 Vector2::operator!	()						{ return Vector2(-x, y); }
	Vector2 Vector2::operator+	(const Vector2& vec)	{ return Vector2(x + vec.x,	y + vec.y); }
	Vector2 Vector2::operator-	(const Vector2& vec)	{ return Vector2(x - vec.x,	y - vec.y); }
	Vector2 Vector2::operator*	(float val)				{ return Vector2(x * val,	y * val); }
	Vector2 Vector2::operator/	(float val)				{ return Vector2(x / val,	y / val); }
	
	Vector2& Vector2::operator+=(const Vector2& vec)	{ x += vec.x; y += vec.y;	return *this; }
	Vector2& Vector2::operator-=(const Vector2& vec)	{ x -= vec.x; y -= vec.y;	return *this; }
	Vector2& Vector2::operator*=(float val)				{ x *= val;   y *= val;		return *this; }
	Vector2& Vector2::operator/=(float val)				{ x /= val;   y /= val;		return *this; }
	
	bool Vector2::operator==	(const Vector2& vec)	{ return (x - vec.x <   1e-5 && y - vec.y <   1e-5); }
	bool Vector2::operator!=	(const Vector2& vec)	{ return (x - vec.x <   1e-5 && y - vec.y <   1e-5); }
	bool Vector2::operator>		(const Vector2& vec)	{ return (x - vec.x >   1e-5 && y - vec.y >   1e-5); }
	bool Vector2::operator<		(const Vector2& vec)	{ return (x - vec.x <  -1e-5 && y - vec.y <  -1e-5); }
	bool Vector2::operator>=	(const Vector2& vec)	{ return (x - vec.x >= -1e-5 && y - vec.y >= -1e-5); }
	bool Vector2::operator<=	(const Vector2& vec)	{ return (x - vec.x <=  1e-5 && y - vec.y <=  1e-5); }
	
	Vector2::operator sf::Vector2f() { return sf::Vector2f(x, y); }
	Vector2::operator sf::Vector2i() { return sf::Vector2i(x, y); }
	
	Vector2 operator*	(float val, const Vector2& vec) { return Vector2(vec.x * val, vec.y * val); }
	Vector2 operator/	(float val, const Vector2& vec) { return Vector2(vec.x / val, vec.y / val); }
}
