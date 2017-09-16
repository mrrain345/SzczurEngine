#pragma once
#include <SFML/System/Vector2.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

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
		
		Vector2					();
		Vector2					(float x, float y);
		Vector2					(sf::Vector2f vector);
		Vector2					(sf::Vector2i vector);
		Vector2					(sf::Vector2u vector);
		
		void set				(float x, float y);
		
		float magnitude			();
		float sqrMagnitude		();
		float angle				();
		
		Vector2 normalized		();
		Vector2 scaled			(Vector2 scale);
		Vector2 clampedMagnitude(float maxLength);
		Vector2 rounded			();
		Vector2 rotated			(float angle);
		
		void normalize			();
		void scale				(Vector2 scale);
		void clampMagnitude		(float maxLength);
		void round				();
		void rotate				(float angle);
		
		static Vector2 max		(Vector2 vec1, Vector2 vec2);
		static Vector2 min		(Vector2 vec1, Vector2 vec2);
		static float distance	(Vector2 vec1, Vector2 vec2);
		static float dot		(Vector2 vec1, Vector2 vec2);
		static float angle		(Vector2 vec1, Vector2 vec2);
		
		Vector2 operator!		();
		Vector2 operator+		(const Vector2& vec);
		Vector2 operator-		(const Vector2& vec);
		Vector2 operator*		(float val);
		Vector2 operator/		(float val);
		
		Vector2& operator+=		(const Vector2& vec);
		Vector2& operator-=		(const Vector2& vec);
		Vector2& operator*=		(float val);
		Vector2& operator/=		(float val);
		
		bool operator==			(const Vector2& vec);
		bool operator!=			(const Vector2& vec);
		bool operator>			(const Vector2& vec);
		bool operator<			(const Vector2& vec);
		bool operator>=			(const Vector2& vec);
		bool operator<=			(const Vector2& vec);
		
		Vector2 operator-		();
		
		operator sf::Vector2f	();
		operator sf::Vector2i	();
	};
	
	Vector2 operator*			(float val, const Vector2& vec);
	Vector2 operator/			(float val, const Vector2& vec);
}
