#ifndef GAME_H
#define GAME_H

#include "Singleton.h"
#include "EventHandler.h"
#include "GameObject.h"
#include "BackgroundTypes.h"

// sound header
#include <maxmod9.h>

#include <map>
#include <vector>


class IGraphicsRenderer;
class GameState;

class Game : public EventHandler
{
public:

	typedef std::map<int, GameObject*> GameObjects;

	~Game() {}

	bool Init();

	void Clean();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void Reset();
	void ResetScores() { m_p1Score = 0; m_p2Score = 0; }

	bool CheckLoadState() { return m_bStateLoaded;}

	void Update(float gameSpeed);
	void Draw(IGraphicsRenderer* renderer);

	const GameObjects& GetGameObjects() { return m_gameObjects; }

	int GetNextGameObjectID() { return m_nextGameObjectID; }
	void IncrementGameObjectID() { m_nextGameObjectID++; }
	void AddGameObject(GameObject* pGO);

	GameObject* GetGameObject(int id) { return m_gameObjects[id]; }

	void LoadGameObjects(const char* gameObjectfile);

	void SetPlayStateObjectFile(const char* stateFile) { m_playStateObjectFile = stateFile; }
	void SetPlayStateResourceFile(const char* stateFile) { m_playStateResourcesFile = stateFile; }
	const char* GetPlayStateObjectFile() { return m_playStateObjectFile; }
	const char* GetPlaystateResourceFile() { return m_playStateResourcesFile; }

	void IncrementP1Score() { m_p1Score++; }
	void IncrementP2Score() { m_p2Score++; }
	int GetP1Score() { return m_p1Score; }
	int GetP2Score() { return m_p2Score; }

private:

	Game();
	friend class Singleton<Game>;

	std::vector<GameState*> states;

	int m_nextGameObjectID;
	GameObjects m_gameObjects;

	const char* m_playStateObjectFile;
	const char* m_playStateResourcesFile;

	bool m_bStateLoaded;

	int m_p1Score;
	int m_p2Score;
};

typedef Singleton<Game> TheGame;

#endif