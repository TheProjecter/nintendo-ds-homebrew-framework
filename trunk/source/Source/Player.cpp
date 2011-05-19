#include "Player.h"
#include "Game.h"
#include "ResourceManager.h"
#include "GameObjectFactory.h"
#include <iostream>

static bool playerCreator = TheGameObjectFactory::Instance()->AddType("Player", Player::CreatePlayer);

GameObject* Player::CreatePlayer()
{
	return new Player;
}

Player::Player() :	m_stylusLastX(0),
	m_stylusLastY(0)
{

}

bool Player::Load(File* pFile)
{
	MeshObject::Load(pFile);

	m_boundingBox = new BoundingRectangle(m_position.m_x, m_position.m_y, 4.0f, 2.0f);
	//m_boundingBox = new BoundingRectangle(m_position, Fixed(5), Fixed(2));
	return true;
}

void Player::Update(float gameSpeed)
{
	Vec2f oldPos = m_position;

	switch (m_currentState)
	{
	case tennis::states_inplay :

		// get input to move the player
		HandleInput();

		MeshObject::Update(gameSpeed);

		if(m_position.m_x >= Fixed(14) || m_position.m_x <= Fixed(-14))
		{
			m_position.m_x = oldPos.m_x;
		}
		else
		{
			m_position.m_x = m_position.m_x;
		}

		if(m_position.m_y > Fixed(-2) || m_position.m_y < Fixed(-8))
		{
			m_position.m_y = oldPos.m_y;
		}
		else
		{
			m_position.m_y = m_position.m_y;
		}

		m_boundingBox->SetPos(Vec2f(m_position.m_x - 2.0f, m_position.m_y));

		break;

	case tennis::states_p1serve :

		// get input to move the player
		HandleInput();

		m_position.m_y = Fixed(-8);

		m_position.m_x += m_velocity.m_x * gameSpeed;

		if(m_position.m_x >= Fixed(14) || m_position.m_x <= Fixed(-14))
		{
			m_position.m_x = oldPos.m_x;
		}
		else
		{
			m_position.m_x = m_position.m_x;
		}

		if(m_position.m_y > Fixed(-2)|| m_position.m_y < Fixed(-8))
		{
			m_position.m_y = oldPos.m_y;
		}
		else
		{
			m_position.m_y = m_position.m_y;
		}

		if(TheGame::Instance()->KeyPressed(KEY_B))
		{
			TheGame::Instance()->GetGameObject(2)->SetVelocity(Vec2f(Fixed(0), Fixed(-10)));
			TheGame::Instance()->GetGameObject(2)->SetState(tennis::states_inplay);
			TheGame::Instance()->GetGameObject(1)->SetState(tennis::states_inplay);
			m_currentState = tennis::states_inplay;
		}

		m_boundingBox->SetPos(Vec2f(m_position.m_x - 2.0f, m_position.m_y));

		break;

	case tennis::states_p2serve :

		HandleInput();

		m_position.m_y = Fixed(-8); 

		m_position.m_x += m_velocity.m_x * gameSpeed;

		if(m_position.m_x >= Fixed(14) || m_position.m_x <= Fixed(-14)) // 14
		{
			m_position.m_x = oldPos.m_x;
		}
		else
		{
			m_position.m_x = m_position.m_x;
		}

		if(m_position.m_y > Fixed(-2) || m_position.m_y < Fixed(-8))
		{
			m_position.m_y = oldPos.m_y;
		}
		else
		{
			m_position.m_y = m_position.m_y;
		}

		m_boundingBox->SetPos(Vec2f(m_position.m_x - 2.0f, m_position.m_y));

		break;

	case tennis::states_beforeplay:

		break;
	}
}

void Player::Draw()
{
	MeshObject::Draw();
}

void Player::HandleInput()
{
	if(TheGame::Instance()->KeyHeld(KEY_UP))
	{
		m_bMoving = true;
		m_velocity.m_y = Fixed(16); // 16
	}
	else if(TheGame::Instance()->KeyHeld(KEY_DOWN))
	{
		m_bMoving = true;
		m_velocity.m_y = Fixed(-16); // -16
	}
	else if(!TheGame::Instance()->KeyHeld(KEY_UP) || !TheGame::Instance()->KeyHeld(KEY_DOWN))
	{
		m_bMoving = false;
		m_velocity.m_y = Fixed(0);
	}

	if(TheGame::Instance()->KeyHeld(KEY_RIGHT))
	{
		m_bMoving = true;
		m_velocity.m_x = Fixed(-16);
	}
	else if(TheGame::Instance()->KeyHeld(KEY_LEFT))
	{
		m_bMoving = true;
		m_velocity.m_x = Fixed(16);
	}
	else if(!TheGame::Instance()->KeyHeld(KEY_RIGHT) || !TheGame::Instance()->KeyHeld(KEY_LEFT))
	{
		m_bMoving = false;
		m_velocity.m_x = Fixed(0);
	}
}