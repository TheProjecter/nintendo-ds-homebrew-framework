#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "File.h"
#include "Vec3.h"
#include "CollisionDetection.h"
#include "EGameObjectStates.h"
#include "Vec2.h"

class GameObject
{
public:

	virtual ~GameObject() { delete m_boundingBox; }

	virtual const char* GetTypeName() const = 0;

	virtual bool Load(File* pFile) = 0;
	virtual void Update(float gameSpeed) = 0;
	virtual void Draw() = 0;

	const Vec2f& GetPosition() { return m_position; }
	const Vec2f& GetVelocity() { return m_velocity; }

	void SetPosition(const Vec2f& pos) { m_position = pos; }
	void SetVelocity(const Vec2f& vel) { m_velocity = vel; }

	void SetState(tennis::object_states state) { m_currentState = state; }

	const BoundingRectangle* GetBoundingBox() const { return m_boundingBox; }

protected:

	GameObject() :	m_id(0),
					m_position(Vec2f(0,0)),
					m_velocity(Vec2f(0,0)),
					m_boundingBox(NULL),
					m_currentState(tennis::states_beforeplay)
	{

	}

	int m_id;

	Vec2f m_position;
	Vec2f m_velocity;

	BoundingRectangle* m_boundingBox;

	tennis::object_states m_currentState;
};

#endif