#pragma once

#include <iostream>
#include <string>

class Vector2D
{
public:

	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	~Vector2D();

	Vector2D& add(const Vector2D& vec);
	Vector2D& subtract(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);

	friend Vector2D operator+(Vector2D lhs, const Vector2D& rhs);
	friend Vector2D operator-(Vector2D lhs, const Vector2D& rhs);
	friend Vector2D operator*(Vector2D lhs, const Vector2D& rhs);
	friend Vector2D operator/(Vector2D lhs, const Vector2D& rhs);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	Vector2D& operator*(const int i);
	Vector2D& zero();

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
	std::string toString();

private:



};

