#ifndef Vector2D_h
#define Vector2D_h

#include <iostream>

class Vector2D {

public:
	float x, y;

	Vector2D();
	Vector2D(float x, float y);

	// Here we pass a 2nd vector in and we simply read it. It's a const, because we don't want to change
	// the vector being passed in.

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Divide(const Vector2D& vec);

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& v1);
	Vector2D& operator-=(const Vector2D& v1);
	Vector2D& operator*=(const Vector2D& v1);
	Vector2D& operator/=(const Vector2D& v1);

	Vector2D& operator*(const int& i);
	Vector2D& Zero();

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

#endif