#include "Game.h"
#include "GameState.h"
#include "DSGraphicsRenderer.h"
#include "GameObjectFactory.h"
#include <iostream>
#include <fat.h>
#include <vector>

Game::Game() : m_nextGameObjectID(0),
			   m_bStateLoaded(false),
			   m_p1Score(0),
			   m_p2Score(0)
{

}

void Game::AddGameObject(GameObject* pGO)
{
	m_gameObjects.insert(std::pair<int, GameObject*>(m_nextGameObjectID, pGO));
}

void Game::LoadGameObjects(const char* gameObjectfile)
{
	File fr;
	fr.Open(gameObjectfile);

	while(!fr.EndOfFile())
	{
		char type[50];
		fr.GetString(type);

		GameObject* newObject = TheGameObjectFactory::Instance()->Create(type);
		newObject->Load(&fr);

		TheGame::Instance()->AddGameObject(newObject);

		TheGame::Instance()->IncrementGameObjectID();
	}
}

void Game::Reset()
{
	m_p1Score = 0;
	m_p2Score = 0;
	m_gameObjects.clear();
}

bool Game::Init()
{
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	mmInitDefault("assets/soundbank.bin");

	std::cout << "Game Init success\n";
	return true;
}

void Game::Clean()
{
	while(!states.empty())
	{
		states.back()->Clean();
		states.pop_back();
	}
}

void Game::ChangeState(GameState* state)
{
	if(!states.empty())
	{
		states.back()->Clean();
		states.pop_back();
		m_bStateLoaded = false;
	}

	states.push_back(state);

	// load the state 
	m_bStateLoaded = states.back()->Init();
}

void Game::PushState(GameState* state)
{
	if(!states.empty())
	{
		states.back()->Pause();
	}

	states.push_back(state);
	m_bStateLoaded = false;

	// load the state 
	m_bStateLoaded = states.back()->Init();
}

void Game::PopState()
{
	if(!states.empty())
	{
		states.back()->Clean();
		states.pop_back();
	}

	if(!states.empty())
	{
		states.back()->Resume();
	}
}

void Game::Update(float gameSpeed)
{
	if(CheckLoadState())
	{
		states.back()->Update(gameSpeed);
		EventHandler::Update();
	}
}

void Game::Draw(IGraphicsRenderer* renderer)
{
	if(CheckLoadState())
	{
		states.back()->Draw(renderer);
	}
}