#include "DSGraphicsRenderer.h"
#include "Game.h"
#include "StartMenuState.h"
#include "ChooseCourtState.h"
#include "PlayState.h"
#include <iostream>
#include <time.h>

/*
easily changeable game speed for animation and movement, 
DS does not need delta time between frames it just ticks along
*/
const float g_gameSpeed = 0.1f;

// nice macro :)
#define SAFE_DELETE(p) { if (p) { delete p; p = NULL; } }

// global systems
IGraphicsRenderer* g_graphicsRenderer = NULL;

int main(int argc, char **argv)
{
	srand(time(NULL));

	// Initialise the graphics renderer
	g_graphicsRenderer = new DSGraphicsRenderer();

	if(g_graphicsRenderer == NULL || !g_graphicsRenderer->Init())
	{
		// problem initialising graphics renderer
		return 1;
	}

	if(!TheGame::Instance()->Init())
	{
		// problem initialising game
		std::cout << "problem initialising game\n";
		return 1;
	}

	TheGame::Instance()->ChangeState(StartMenuState::Instance());

	bool Running = true;

	while(Running)
	{
		TheGame::Instance()->Draw(g_graphicsRenderer);
		TheGame::Instance()->Update(g_gameSpeed);
	}

	SAFE_DELETE(g_graphicsRenderer);

	return 0;
}