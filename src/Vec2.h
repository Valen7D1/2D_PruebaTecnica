#pragma once

class vec2
{
public:
	vec2();
	vec2(float _x, float _y);
	~vec2();

	vec2 operator*(const float& value);

	bool operator!=(const vec2& otherVector);
	bool operator==(const vec2& otherVector);

	vec2 operator+=(const vec2& value);
	
	vec2 operator+(const vec2& otherVector);
	vec2 operator-(const vec2& otherVector);
	vec2 operator*(const vec2& otherVector);
	vec2 operator/(const vec2& otherVector);

	vec2 AbsoluteValue() const;
	float Magnitude() const;
	void Normalize();
	float DotProduct(const vec2& other) const;

	float Angle(const vec2& other) const;
	float Distance(const vec2& other) const;
	float length()const;


	float x;
	float y;
};

