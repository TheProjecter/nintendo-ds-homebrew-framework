#include "Ball.h"
#include "GameObjectFactory.h"
#include "ResourceManager.h"
#include "Game.h"
#include <nds.h>
#include "soundbank.h"
#include <maxmod9.h>

float maxVel = 20.0f;

static bool ballCreator = TheGameObjectFactory::Instance()->AddType("Ball", Ball::CreateBall);

GameObject* Ball::CreateBall()
{
	return new Ball;
}

Ball::Ball()
{

}

bool Ball::Load(File* pFile)
{
	MeshObject::Load(pFile);

	m_boundingBox = new BoundingRectangle(m_position.m_x, m_position.m_y, 1.0f, 1.0f);

	m_velocity.m_y = -10.0;

	return true;
}

void Ball::Update(float gameSpeed)
{
	// save the current position
	Vec2f oldPos = m_position;

	switch (m_currentState)
	{
	case tennis::states_inplay :

		if(m_velocity.m_x >= maxVel)
		{
			m_velocity.m_x = maxVel;
		}

		// Check for collision before moving in y
		if(m_boundingBox->Colliding(TheGame::Instance()->GetGameObject(0)->GetBoundingBox()))
		{
			m_velocity.m_y = m_velocity.m_y * -1.0f;
			m_velocity.m_x += TheGame::Instance()->GetGameObject(0)->GetVelocity().m_x * 0.5f;
		}

		if(m_boundingBox->Colliding(TheGame::Instance()->GetGameObject(1)->GetBoundingBox()))
		{
			m_velocity.m_y = m_velocity.m_y * -1.0f;
			m_velocity.m_x += TheGame::Instance()->GetGameObject(1)->GetVelocity().m_x * 0.5f;
		}

		m_position.m_y += m_velocity.m_y * gameSpeed;

		// Check for collision before moving in x
		if(m_boundingBox->Colliding(TheGame::Instance()->GetGameObject(0)->GetBoundingBox()))
		{
			m_velocity.m_x += TheGame::Instance()->GetGameObject(0)->GetVelocity().m_x * 0.5f;
		}

		if(m_boundingBox->Colliding(TheGame::Instance()->GetGameObject(1)->GetBoundingBox()))
		{
			m_velocity.m_x += TheGame::Instance()->GetGameObject(1)->GetVelocity().m_x * 0.5f;
		}

		m_position.m_x += m_velocity.m_x * gameSpeed;

		// check for out of bounds
		if(m_position.m_x > 14.0 || m_position.m_x < -14.0)
		{
			m_position = oldPos;
			m_velocity.m_x *= -1.0f;
		}
		// update bounding box
		m_boundingBox->SetPos(Vec2f(m_position.m_x, m_position.m_y));

		break;

	case tennis::states_p1serve:

		m_velocity.m_x = 0;
		m_velocity.m_y = 0;
		m_position.m_x = TheGame::Instance()->GetGameObject(0)->GetPosition().m_x;
		m_position.m_y = TheGame::Instance()->GetGameObject(0)->GetPosition().m_y + 1.5f;

		// update bounding box
		m_boundingBox->SetPos(Vec2f(m_position.m_x, m_position.m_y));

		break;

	case tennis::states_p2serve:

		m_velocity.m_x = 0;
		m_velocity.m_y = 0;
		m_position.m_x = TheGame::Instance()->GetGameObject(1)->GetPosition().m_x;
		m_position.m_y = TheGame::Instance()->GetGameObject(1)->GetPosition().m_y - 1.5f;

		// update bounding box
	    m_boundingBox->SetPos(Vec2f(m_position.m_x, m_position.m_y));

		break;

	case tennis::states_beforeplay:

		break;

	}
}

void Ball::Draw()
{
	MeshObject::Draw();	
}