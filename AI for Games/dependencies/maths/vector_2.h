// @brief vector_2.h
// Class represents a pair f cartesian coordinates
// for use in two dimentional game systems

#pragma once

#ifndef _VECTOR_2_
#define _VECTOR_2_

class vector_2
{
public:
	/*	@brief Critical math data for vector_2
	*/
	union
	{
		struct
		{
			float x;
			float y;
		};
		float data[2];
	};

	vector_2(const float a_x = 0.0f, const float a_y = 0.0f);

	/*	@brief Subscript operator overloading to allow direct data access
		@param Index of the data member
		@return Reference to indexed data member
	*/
	float& operator[](const int a_index);

	/*	@brief Casting operator oveloading 
	*/
	operator float*();

	/*	@brief Casting read only float* operator oveloading
	*/
	operator const float*() const;

	vector_2 operator+(const vector_2& a_rhs) const;
	vector_2 operator-(const vector_2& a_rhs) const;
	vector_2 operator*(const float a_rhs) const;
	vector_2 operator/(const float a_rhs) const;

	vector_2& operator+=(const vector_2& a_rhs);
	vector_2& operator-=(const vector_2& a_rhs);
	vector_2& operator*=(const float a_rhs);
	vector_2& operator/=(const float a_rhs);

	float square_magnitude() const;
	float magnitude() const;

	void normalise();
	vector_2 normalised() const;

	float dot(const vector_2& a_vector_2) const;

	vector_2 right() const;

	float dot(const vector_2& a_vector_2_A, const vector_2& a_vector_2_B);

	bool operator==(const vector_2& a_rhs) const;
};

vector_2 operator*(const float a_lhs, const vector_2& a_rhs);

#endif // !_VECTOR_2_
