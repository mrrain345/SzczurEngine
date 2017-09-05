#pragma once
#include <SFML/System/Vector2.hpp>

namespace Szczur {
	class Vector2 {	
	public:
		float x;
		float y;
		
		static const Vector2 Down;
		static const Vector2 Left;
		static const Vector2 Right;
		static const Vector2 Up;
		static const Vector2 Zero;
		static const Vector2 One;
		
		Vector2();
		Vector2(float x, float y);
		Vector2(sf::Vector2f vector);
		Vector2(sf::Vector2i vector);
		Vector2(sf::Vector2u vector);
		
		void Set(float x, float y);
		
		float Magnitude();
		float SqrMagnitude();
		float Angle();
		
		Vector2 Normalized();
		Vector2 Scaled(Vector2 scale);
		Vector2 ClampedMagnitude(float maxLength);
		Vector2 Rounded();
		Vector2 Rotated(float angle);
		
		void Normalize();
		void Scale(Vector2 scale);
		void ClampMagnitude(float maxLength);
		void Round();
		void Rotate(float angle);
		
		static Vector2 Max(Vector2 vec1, Vector2 vec2);
		static Vector2 Min(Vector2 vec1, Vector2 vec2);
		static float Distance(Vector2 vec1, Vector2 vec2);
		static float Dot(Vector2 vec1, Vector2 vec2);
		static float Angle(Vector2 vec1, Vector2 vec2);
		
		Vector2 operator!	();
		Vector2 operator+	(const Vector2& vec);
		Vector2 operator-	(const Vector2& vec);
		Vector2 operator*	(float val);
		Vector2 operator/	(float val);
		
		Vector2& operator+=	(const Vector2& vec);
		Vector2& operator-=	(const Vector2& vec);
		Vector2& operator*=	(float val);
		Vector2& operator/=	(float val);
		
		bool operator==		(const Vector2& vec);
		bool operator!=		(const Vector2& vec);
		bool operator>		(const Vector2& vec);
		bool operator<		(const Vector2& vec);
		bool operator>=		(const Vector2& vec);
		bool operator<=		(const Vector2& vec);
		
		operator sf::Vector2f();
		operator sf::Vector2i();
	};
	
	Vector2 operator*	(float val, const Vector2& vec);
	Vector2 operator/	(float val, const Vector2& vec);
}
