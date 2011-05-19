#ifndef START_MENU_STATE_H
#define START_MENU_STATE_H

#include "GameState.h"
#include "BackgroundTypes.h"

class StartMenuState : public GameState
{
public:

	bool Init();
	void Clean();

	void Pause();
	void Resume();

	void Update(float gameSpeed);
	void Draw(IGraphicsRenderer* renderer);

	static StartMenuState* Instance() {
		return &m_StartMenuState;
	}

private:

	StartMenuState();

	static StartMenuState m_StartMenuState;


	// Backgrounds for state
	IBackground* m_mainBack;
	IBackground* m_subBack;
};

#endif