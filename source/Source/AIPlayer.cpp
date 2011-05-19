#include "AIPlayer.h"
#include "GameObjectFactory.h"
#include "Game.h"

static bool AIPlayerCreator = TheGameObjectFactory::Instance()->AddType("AIPlayer", AIPlayer::CreateAIPlayer);

bool chosen = false;
Fixed chosenPos = 0;
Fixed choiceTimer = 0;

GameObject* AIPlayer::CreateAIPlayer()
{
	return new AIPlayer;
}

AIPlayer::AIPlayer() : MeshObject()
{

}

bool AIPlayer::Load(File* pFile)
{
	MeshObject::Load(pFile);

	m_boundingBox = new BoundingRectangle(m_position.m_x, m_position.m_y, 5.0f, 2.0f);

	return true;
}

void AIPlayer::Update(float gameSpeed)
{
	// save the current position
	Vec2f oldPos = m_position;

	switch (m_currentState)
	{
	case tennis::states_inplay :

		DoAI();

		if(m_velocity.m_x > Fixed(20))
		{
			m_velocity.m_x = Fixed(20);
		}
		else if(m_velocity.m_x < Fixed(-20))
		{
			m_velocity.m_x = Fixed(-20);
		}

		MeshObject::Update(gameSpeed);

		if(m_position.m_x >= Fixed(15) || m_position.m_x <= Fixed(-15))
		{
			m_position.m_x = oldPos.m_x;
		}
		else
		{
			m_position.m_x = m_position.m_x;
		}

		m_boundingBox->SetPos(Vec2f(m_position.m_x - 2.0f, m_position.m_y));

		break;

	case tennis::states_p1serve :

		m_position.m_y = Fixed(8);

		DoAI();

		if(m_velocity.m_x > Fixed(10))
		{
			m_velocity.m_x = Fixed(10);
		}
		else if(m_velocity.m_x < Fixed(-10))
		{
			m_velocity.m_x = Fixed(-10);
		}

		m_position.m_x += m_velocity.m_x * gameSpeed;

		if(m_position.m_x >= Fixed(14) || m_position.m_x <= Fixed(-14))
		{
			m_position.m_x = oldPos.m_x;
		}
		else
		{
			m_position.m_x = m_position.m_x;
		}

		m_boundingBox->SetPos(Vec2f(m_position.m_x - 2.0f, m_position.m_y));

		break;

	case tennis::states_p2serve :

		m_position.m_y = Fixed(8);

		DoAI();

		if(m_velocity.m_x > Fixed(10))
		{
			m_velocity.m_x = Fixed(10);
		}
		else if(m_velocity.m_x < Fixed(-10))
		{
			m_velocity.m_x = Fixed(-10);
		}

		m_position.m_x += m_velocity.m_x * gameSpeed;

		if(m_position.m_x >= Fixed(14) || m_position.m_x <= Fixed(-14))
		{
			m_position.m_x = oldPos.m_x;
		}
		else
		{
			m_position.m_x = m_position.m_x;
		}

		m_boundingBox->SetPos(Vec2f(m_position.m_x - 2.0f, m_position.m_y));

		break;

	case tennis::states_beforeplay:

		break;
	}
}

void AIPlayer::Draw()
{
	MeshObject::Draw();
}

void AIPlayer::DoAI()
{
	switch (m_currentState)
	{
	case tennis::states_inplay :

		if(TheGame::Instance()->GetGameObject(2)->GetPosition().m_x > m_position.m_x)
		{
			m_velocity.m_x = Fixed(15);
		}
		else if(TheGame::Instance()->GetGameObject(2)->GetPosition().m_x < m_position.m_x)
		{
			m_velocity.m_x = Fixed(-15);
		}

		break;

	case tennis::states_p1serve:

		m_velocity.m_x = -(m_position.m_x - TheGame::Instance()->GetGameObject(2)->GetPosition().m_x);

		break;

	case tennis::states_p2serve:

		// AI player makes a random choice of where to serve the ball from
		choiceTimer += Fixed(1);

		if(!chosen)
		{
			chosenPos = rand() & (14 - 1); // faster than modulo
			chosen = true;
		}

		if(m_position.m_x < chosenPos || m_position.m_x > chosenPos )
		{
			m_velocity.m_x = -(m_position.m_x - (float)chosenPos); 
		}

		if(choiceTimer >= Fixed(50))
		{
			TheGame::Instance()->GetGameObject(2)->SetVelocity(Vec2f(Fixed(0), Fixed(10)));
			TheGame::Instance()->GetGameObject(2)->SetState(tennis::states_inplay);
			TheGame::Instance()->GetGameObject(0)->SetState(tennis::states_inplay);
			m_currentState = tennis::states_inplay;
			chosen = false;
			choiceTimer = Fixed(0);
		}
		break;

	case tennis::states_beforeplay:

		break;
	}
}