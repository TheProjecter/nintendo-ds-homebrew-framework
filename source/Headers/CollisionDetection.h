#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "Vec3.h"
#include "Vec2.h"

///////////////////////////////////////////////////////////////////////////////////////////
/*
	3D Axis Aligned Bounding Box
*/
///////////////////////////////////////////////////////////////////////////////////////////
class AABB3
{
public:

	AABB3(const Vec3f& pos, float width, float height, float depth) : m_position(pos)
	{
		m_maxextents.m_x = m_position.m_x + width;
		m_minextents.m_x = m_position.m_x - width;

		m_maxextents.m_y = m_position.m_y + height;
		m_minextents.m_y = m_position.m_y - height;

		m_maxextents.m_z = m_position.m_z + depth;
		m_minextents.m_z = m_position.m_z - depth;
	}

	Vec3f m_position;
	Vec3f m_maxextents;
	Vec3f m_minextents;

	float width;
	float height;
	float depth;

	void Update(const Vec3f& pos);
	const bool Overlaps(const AABB3* b) const;

};

inline void AABB3::Update(const Vec3f& pos)
{
	m_position = pos;

	m_maxextents.m_x = m_position.m_x + width;
	m_minextents.m_x = m_position.m_x - width;

	m_maxextents.m_y = m_position.m_y + height;
	m_minextents.m_y = m_position.m_y - height;

	m_maxextents.m_z = m_position.m_z + depth;
	m_minextents.m_z = m_position.m_z - depth;
}

inline const bool AABB3::Overlaps(const AABB3* b) const
{
	if(m_maxextents.m_x < b->m_minextents.m_x)
	{
		return false;
	}

	if(m_minextents.m_x > b->m_maxextents.m_x)
	{
		return false;
	}

	if(m_maxextents.m_y < b->m_minextents.m_y)
	{
		return false;
	}

	if(m_minextents.m_y > b->m_maxextents.m_y)
	{
		return false;
	}

	if(m_maxextents.m_z < b->m_minextents.m_z)
	{
		return false;
	}

	if(m_minextents.m_z > b->m_maxextents.m_z)
	{
		return false;
	}

	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
	2D Axis Aligned Bounding Box
*/
///////////////////////////////////////////////////////////////////////////////////////////
class AABB2
{
public:

	AABB2(const Vec2f& pos, float width, float height) : m_position(pos)
	{
		m_maxextents.m_x = m_position.m_x + width;
		m_minextents.m_x = m_position.m_x - width;

		m_maxextents.m_y = m_position.m_y + height;
		m_minextents.m_y = m_position.m_y - height;
	}

	Vec2f m_position;
	Vec2f m_maxextents;
	Vec2f m_minextents;

	float width;
	float height;

	void Update(const Vec2f& pos);
	const bool Overlaps(const AABB2* b) const;
};

inline void AABB2::Update(const Vec2f& pos)
{
	m_position = pos;

	m_maxextents.m_x = m_position.m_x + width;
	m_minextents.m_x = m_position.m_x - width;

	m_maxextents.m_y = m_position.m_y + height;
	m_minextents.m_y = m_position.m_y - height;
}

inline const bool AABB2::Overlaps(const AABB2* b) const
{
	if(m_maxextents.m_x < b->m_minextents.m_x)
	{
		return false;
	}

	if(m_minextents.m_x > b->m_maxextents.m_x)
	{
		return false;
	}

	if(m_maxextents.m_y < b->m_minextents.m_y)
	{
		return false;
	}

	if(m_minextents.m_y > b->m_maxextents.m_y)
	{
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
/*
	Simple 2D Bounding Rectangle
*/
///////////////////////////////////////////////////////////////////////////////////////////
class BoundingRectangle
{

public:

	BoundingRectangle()
	{
		m_pos = Vec2f(0,0);
		m_height = 0;
		m_width = 0;
	}
	
	BoundingRectangle(Fixed x, Fixed y, float width, float height)
	{
		m_pos = Vec2f(x,y);
		m_height = height;
		m_width = width;
	}
		

	bool Colliding(const BoundingRectangle* other) const;

	void SetPos(const Vec2f& pos) { m_pos = pos; }

	const Vec2f& GetPosition() const { return m_pos; }
	Fixed GetHeight() const { return m_height; }
	Fixed GetWidth() const { return m_width; }

	Vec2f m_pos;
	Fixed m_height;
	Fixed m_width;
};

inline bool BoundingRectangle::Colliding(const BoundingRectangle *other) const
{
	Fixed leftA, leftB;
	Fixed rightA, rightB;
	Fixed topA, topB;
	Fixed bottomA, bottomB;

	leftA = m_pos.m_x;
	rightA = m_pos.m_x + m_width;
	topA = m_pos.m_y;
	bottomA = m_pos.m_y + m_height;

	leftB = other->m_pos.m_x;
	rightB = other->m_pos.m_x + other->m_width;
	topB = other->m_pos.m_y;
	bottomB = other->m_pos.m_y + other->m_height;

	if(bottomA <= topB)
	{
		return false;
	}

	if(topA >= bottomB)
	{
		return false;
	}

	if(rightA <= leftB)
	{
		return false;
	}

	if(leftA >= rightB)
	{
		return false;
	}

	return true;
}

#endif