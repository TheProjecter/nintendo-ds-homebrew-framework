#ifndef VEC2_H
#define VEC2_H

#include <nds.h>
#include <math.h>
#include "Fixed.h"

/*
	DS Homebrew

	2D Vector 

	DS does not have an FPU so floating point operations are expensive
	Thanks to http://wiki.yak.net/675 for Fixed arithemtic code

	Shaun Mitchell
	April 2011
*/

template <class T>
class Vec2
{
public:

	// creates a vec2 at default location
	Vec2<T>() : m_x(0), m_y(0) {}
	Vec2<T>(T x, T y) : m_x(x), m_y(y) {}

	~Vec2<T>() {}

	// Set
	void SetX(T x) { m_x = x; }
	void SetY(T y) { m_y = y; }

	// Get
	T GetX() { return m_x; }
	T GetY() { return m_y; }

	T Dot(const Vec2<T>& vec) const;
	T Length() const;
	T LengthSquared() const;

	bool operator==(const Vec2<T>& vec) const;
	bool operator!=(const Vec2<T>& vec) const;

	Vec2<T> &operator+=(const Vec2<T>& vec);
	Vec2<T> &operator-=(const Vec2<T>& vec);
	Vec2<T> &operator*=(T scalar);
	Vec2<T> &operator/=(T scalar);

	Vec2<T> operator+(const Vec2<T>& vec) const;
	Vec2<T> operator-(const Vec2<T>& vec) const;
	Vec2<T> operator*(T scalar) const;
	Vec2<T> operator/(T scalar) const;

	void Clear();

	void Normalise();

	T m_x;
	T m_y;
};

template<class T>
inline Vec2<T> operator*(T scalar, const Vec2<T>& vec)
{
	return Vec2<T>(scalar * vec.m_x, scalar * vec.m_y);
}

template<class T>
inline Vec2<T> operator-(const Vec2<T>& vec)
{
	return Vec2<T>(-vec.m_x, -vec.m_y);
}

template<class T>
inline T Vec2<T>::Dot(const Vec2<T>& vec) const
{
	return	(m_x * vec.m_x) + (m_y * vec.m_y);
}

template<class T>
inline Vec2<T> &Vec2<T>::operator+=(const Vec2<T>& vec)
{
	m_x += vec.m_x, m_y += vec.m_y;
	return *this;
}

template<class T>
inline bool Vec2<T>::operator==(const Vec2<T>& vec) const
{
	return	m_x == vec.m_x && m_y == vec.m_y;
}

template<class T>
inline bool Vec2<T>::operator!=(const Vec2<T>& vec) const
{
	return !(*this == vec);
}

template<class T>
inline Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &vec)
{
	m_x -= vec.m_x, m_y -= vec.m_y;
	return *this;
}

template<class T>
inline Vec2<T> &Vec2<T>::operator*=(T scalar)
{
	m_x *= scalar, m_y *= scalar;
	return *this;
}

template<class T>
inline Vec2<T> &Vec2<T>::operator/=(T scalar)
{
	m_x /= scalar, m_y /= scalar;
	return *this;
}

template<class T>
inline Vec2<T> Vec2<T>::operator+(const Vec2<T>& vec) const
{
	Vec2<T> tmp(*this);
	tmp += vec;
	return tmp;
}

template<class T>
inline Vec2<T> Vec2<T>::operator-(const Vec2<T>& vec) const
{
	Vec2<T> tmp(*this);
	tmp -= vec;
	return tmp;
}

template<class T>
inline Vec2<T> Vec2<T>::operator*(T scalar) const
{
	return Vec2<T>(m_x * scalar, m_y * scalar);    
}

template<class T>
inline Vec2<T> Vec2<T>::operator/(T scalar) const
{
	return Vec2<T>(m_x / scalar, m_y / scalar);
}

template<class T>
inline T Vec2<T>::Length() const
{
	return sqrt((m_x * m_x) + (m_y * m_y));
}

template<class T>
inline T Vec2<T>::LengthSquared() const
{
	return (m_x * m_x) + (m_y * m_y);
}

template<class T>
inline void Vec2<T>::Normalise()
{
	T invMag = 1.0 / Length();
	m_x *= invMag, m_y *= invMag;
}

typedef Vec2<Fixed> Vec2f;

#endif