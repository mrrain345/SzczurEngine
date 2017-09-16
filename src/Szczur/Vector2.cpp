#include <Szczur/Vector2.h>

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
		this->x = float(vector.x);
		this->y = float(vector.y);
	}
	
	Vector2::Vector2(sf::Vector2u vector) {
		this->x = float(vector.x);
		this->y = float(vector.y);
	}
	
	void Vector2::set(float x, float y) {
		this->x = x;
		this->y = y;
	}
	
	float Vector2::magnitude() {
		return sqrt(x*x + y*y);
	}
	
	float Vector2::sqrMagnitude() {
		return x*x + y*y;
	}
	
	float Vector2::angle() {
		return acos(x / magnitude()) * (180.0f / M_PI);
	}
	
	
	
	Vector2 Vector2::normalized() {
		float mag = magnitude();
		return Vector2(x/mag, y/mag);
	}
	
	Vector2 Vector2::scaled(Vector2 scale) {
		return Vector2(x * scale.x, y * scale.y);
	}
	
	Vector2 Vector2::clampedMagnitude(float maxLength) {
		if (sqrMagnitude() <= maxLength * maxLength) return Vector2(x, y);
		Vector2 vector = normalized();
		return vector * maxLength;
	}
	
	Vector2 Vector2::rounded() {
		float vx = float((x >= 0) ? (int)(x + 0.5f) : (int)(x - 0.5f));
		float vy = float((y >= 0) ? (int)(y + 0.5f) : (int)(y - 0.5f));
		return Vector2(vx, vy);
	}
	
	Vector2 Vector2::rotated(float angle) {
		float x = this->x * cos(angle) - this->y * sin(angle);
		float y = this->x * sin(angle) + this->y * cos(angle);
		return Vector2(x, y);
	}
	
	
	
	void Vector2::normalize() {
		float mag = magnitude();
		x /= mag;
		y /= mag;
	}
	
	void Vector2::scale(Vector2 scale) {
		x *= scale.x;
		y *= scale.y;
	}
	
	void Vector2::round() {
		x = float((x >= 0) ? (int)(x + 0.5f) : (int)(x - 0.5f));
		y = float((y >= 0) ? (int)(y + 0.5f) : (int)(y - 0.5f));
	}
	
	void Vector2::clampMagnitude(float maxLength) {
		if (sqrMagnitude() <= maxLength * maxLength) return;
		normalize();
		(*this) *= maxLength;
	}
	
	void Vector2::rotate(float angle) {
		float x = this->x * cos(angle) - this->y * sin(angle);
		float y = this->x * sin(angle) + this->y * cos(angle);
		set(x, y);
	}
	
	
	
	Vector2 Vector2::max(Vector2 vec1, Vector2 vec2) {
		return (vec1 >= vec2) ? vec1 : vec2;
	}
	
	Vector2 Vector2::min(Vector2 vec1, Vector2 vec2) {
		return (vec1 <= vec2) ? vec1 : vec2;
	}
	
	float Vector2::distance(Vector2 vec1, Vector2 vec2) {
		return (vec1 - vec2).magnitude();
	}
	
	float Vector2::dot(Vector2 vec1, Vector2 vec2) {
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}
	
	float Vector2::angle(Vector2 vec1, Vector2 vec2) {
		float mag = sqrt(vec1.sqrMagnitude() * vec2.sqrMagnitude());
		return acos(dot(vec1, vec2) / mag) * (180.0f / M_PI);
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
	
	Vector2 Vector2::operator-	()	{ return Vector2(-x, -y); }
	
	Vector2::operator sf::Vector2f() { return sf::Vector2f(x, y); }
	Vector2::operator sf::Vector2i() { return sf::Vector2i(x, y); }
	
	Vector2 operator*	(float val, const Vector2& vec) { return Vector2(vec.x * val, vec.y * val); }
	Vector2 operator/	(float val, const Vector2& vec) { return Vector2(vec.x / val, vec.y / val); }
}
