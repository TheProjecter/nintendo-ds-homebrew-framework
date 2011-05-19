#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "AnimateSprite.h"
#include "DisplayList.h"

class PlayState : public GameState
{
public:

	bool Init();
	void Clean();

	void Pause();
	void Resume();

	void Update(float gameSpeed);
	void Draw(IGraphicsRenderer* renderer);

	static PlayState* Instance() {
		return &m_PlayState;
	}

protected:
	PlayState();

private:
	static PlayState m_PlayState;

	// the game sub state
	tennis::game_states m_currentState;

	// bottom screen backgrounds and sprites
	AnimatedSprite* m_pScoreSprite1;
	AnimatedSprite* m_pScoreSprite2;
	IBackground* m_pSubScores;
	IBackground* m_pGameOver;
	AnimatedSprite* m_pPauseSprite;

	float m_camStartZ;
	float m_camEndZ;

	DisplayList m_courtList;
};

#endif