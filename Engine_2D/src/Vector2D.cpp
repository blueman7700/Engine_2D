#include "Vector2D.h"

/// <summary>
/// 
/// </summary>
Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

/// <summary>
/// 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

/// <summary>
/// 
/// </summary>
Vector2D::~Vector2D()
{

}

// basic arithmetic operator overloads

Vector2D& Vector2D::add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D operator+(Vector2D lhs, const Vector2D& rhs)
{
	return lhs.add(rhs);
}

Vector2D operator-(Vector2D lhs, const Vector2D& rhs)
{
	return lhs.subtract(rhs);
}

Vector2D operator*(Vector2D lhs, const Vector2D& rhs)
{
	return lhs.multiply(rhs);
}

Vector2D operator/(Vector2D lhs, const Vector2D& rhs)
{
	return lhs.divide(rhs);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->divide(vec);
}

Vector2D& Vector2D::operator*(const int i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
	os << vec.x << ", " << vec.y;
	return os;
}

std::string Vector2D::toString()
{
	std::string out = "";
	out += std::to_string(this->x);
	out += ", ";
	out += std::to_string(this->y);
	return out;

}