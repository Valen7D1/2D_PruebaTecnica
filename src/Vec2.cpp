#include "Vec2.h"
#include <cmath>

vec2::vec2() :
	x(0),
	y(0)
{
}

vec2::vec2(float _x, float _y) :
	x(_x),
	y(_y)
{
}

vec2::~vec2()
{
}

vec2 vec2::operator+=(const vec2& value)
{
	return vec2(x * value.x, y * value.y);
}

vec2 vec2::operator*(const float& value)
{
	return vec2(x * value, y * value);
}

bool vec2::operator!=(const vec2& otherVector)
{
	return (x != otherVector.x && y != otherVector.y);
}

bool vec2::operator==(const vec2& otherVector)
{
	return (x == otherVector.x && y == otherVector.y);
}


vec2 vec2::operator+(const vec2& otherVector)
{
	return vec2(x + otherVector.x, y + otherVector.y);
}

vec2 vec2::operator-(const vec2& otherVector)
{
	return vec2(x - otherVector.x, y - otherVector.y);
}

vec2 vec2::operator*(const vec2& otherVector)
{
	return vec2(x * otherVector.x, y * otherVector.y);
}

vec2 vec2::operator/(const vec2& otherVector)
{
	return vec2(x / otherVector.x, y / otherVector.y);
}

vec2 vec2::AbsoluteValue() const
{
	return vec2(abs(x), abs(y));
}

float vec2::Magnitude() const
{
	return sqrt(x * x + y * y);
}

void vec2::Normalize()
{
	float mag = Magnitude();
	if (mag != 0)
	{
		x /=  mag;
		y /= mag;
	}
}

float vec2::DotProduct(const vec2& other) const
{
	return (x * other.x) + (y * other.y);
}

float vec2::Angle(const vec2& other) const
{
	float dot = DotProduct(other);
	float mag1 = Magnitude();
	float mag2 = other.Magnitude();

	if (mag1 == 0 || mag2 == 0)
	{
		return 0;
	}

	return acos(dot / (mag1 * mag2));
}

float vec2::Distance(const vec2& other) const
{
	float distX = other.x - x;
	float distY = other.y - y;
	return sqrt(distX * distX + distY * distY);
}

float vec2::length() const
{
	return std::sqrt(x * x + y * y);
}