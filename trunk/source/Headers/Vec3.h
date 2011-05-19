#ifndef VEC3_H
#define VEC3_H

/*
	DS Homebrew

	3D Vector 

	DS does not have an FPU so floating point operations are expensive
	Change the typedef to change precision

	Shaun Mitchell
	April 2011
*/

#include <nds.h>
#include <math.h>

template <class T>
class Vec3
{
public:

	// default constructor
	Vec3<T>() : m_x(0), m_y(0), m_z(0) {}
	Vec3<T>(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}

	~Vec3<T>() {}

	void SetX(T x) { m_x = x; }
	void SetY(T y) { m_y = y; }
	void SetZ(T z) { m_z = z; }

	T GetX() { return m_x; }
	T GetY() { return m_y; }
	T GetZ() { return m_z; }

	Vec3<T> Cross(const Vec3<T>& vec) const;

	T Dot(const Vec3<T>& vec) const;
	T Length() const;
	T LengthSquared() const;

	bool operator==(const Vec3<T>& vec) const;
	bool operator!=(const Vec3<T>& vec) const;

	Vec3<T> &operator+=(const Vec3<T>& vec);
	Vec3<T> &operator-=(const Vec3<T>& vec);
	Vec3<T> &operator*=(T scalar);
	Vec3<T> &operator/=(T scalar);

	Vec3<T> operator+(const Vec3<T>& vec) const;
	Vec3<T> operator-(const Vec3<T>& vec) const;
	Vec3<T> operator*(T scalar) const;
	Vec3<T> operator/(T scalar) const;

	void Clear();

	void Normalise();

	T m_x;
	T m_y;
	T m_z;
};

template<class T>
inline Vec3<T> operator*(T scalar, const Vec3<T>& vec)
{
	return Vec3<T>(scalar * vec.m_x, scalar * vec.m_y, scalar * vec.m_z);
}

template<class T>
inline Vec3<T> operator-(const Vec3<T>& vec)
{
	return Vec3<T>(-vec.m_x, -vec.m_y, -vec.m_z);
}

template<class T>
inline Vec3<T> Vec3<T>::Cross(const Vec3<T>& vec) const
{
	return Vec3<T>((m_y * vec.m_z) - (m_z * vec.m_y),
				(m_z * vec.m_x) - (m_x * vec.m_z),
				(m_x * vec.m_y) - (m_y * vec.m_x));
}

template<class T>
inline T Vec3<T>::Dot(const Vec3<T>& vec) const
{
	return	(m_x * vec.m_x) + 
			(m_y * vec.m_y) + 
			(m_z * vec.m_z);
}

template<class T>
inline Vec3<T> &Vec3<T>::operator+=(const Vec3<T>& vec)
{
	m_x += vec.m_x, m_y += vec.m_y, m_z += vec.m_z;
	return *this;
}

template<class T>
inline bool Vec3<T>::operator==(const Vec3<T>& vec) const
{
	return	m_x == vec.m_x && 
			m_y == vec.m_y && 
			m_z == vec.m_z;
}

template<class T>
inline bool Vec3<T>::operator!=(const Vec3<T>& vec) const
{
	return !(*this == vec);
}

template<class T>
inline Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &vec)
{
	m_x -= vec.m_x, m_y -= vec.m_y, m_z -= vec.m_z;
	return *this;
}

template<class T>
inline Vec3<T> &Vec3<T>::operator*=(T scalar)
{
	m_x *= scalar, m_y *= scalar, m_z *= scalar;
	return *this;
}

template<class T>
inline Vec3<T> &Vec3<T>::operator/=(T scalar)
{
	m_x /= scalar, m_y /= scalar, m_z /= scalar;
	return *this;
}

template<class T>
inline Vec3<T> Vec3<T>::operator+(const Vec3<T>& vec) const
{
	Vec3<T> tmp(*this);
	tmp += vec;
	return tmp;
}

template<class T>
inline Vec3<T> Vec3<T>::operator-(const Vec3<T>& vec) const
{
	Vec3<T> tmp(*this);
	tmp -= vec;
	return tmp;
}

template<class T>
inline Vec3<T> Vec3<T>::operator*(T scalar) const
{
	return Vec3<T>(m_x * scalar, m_y * scalar, m_z * scalar);    
}

template<class T>
inline Vec3<T> Vec3<T>::operator/(T scalar) const
{
	return Vec3<T>(m_x / scalar, m_y / scalar, m_z / scalar);
}

template<class T>
inline T Vec3<T>::Length() const
{
	return sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
}

template<class T>
inline T Vec3<T>::LengthSquared() const
{
	return (m_x * m_x) + (m_y * m_y) + (m_z * m_z);
}

template<class T>
inline void Vec3<T>::Normalise()
{
	T invMag = 1.0 / Length();
	m_x *= invMag, m_y *= invMag, m_z *= invMag;
}

typedef Vec3<float32> Vec3f;
typedef Vec3<v16> Vec3v16;

#endif