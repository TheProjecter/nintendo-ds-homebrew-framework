#ifndef CHOOSE_COURT_STATE_H
#define CHOOSE_COURT_STATE_H

#include "GameState.h"
#include "BackgroundTypes.h"

class ChooseCourtState : public GameState
{
public:

	bool Init();
	void Clean();

	void Pause();
	void Resume();

	void Update(float gameSpeed);
	void Draw(IGraphicsRenderer* renderer);

	static ChooseCourtState* Instance() {
		return &m_ChooseCourtState;
	}

private:

	ChooseCourtState();

	static ChooseCourtState m_ChooseCourtState;

	// Backgrounds for state
	IBackground* m_mainBack;
	IBackground* m_subBack;
};

#endif