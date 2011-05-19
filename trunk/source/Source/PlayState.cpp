#include <stdio.h>
#include <assert.h>
#include <iostream>

#include "Game.h"
#include "PlayState.h"
#include "DSGraphicsRenderer.h"
#include "GameObjectFactory.h"
#include "File.h"
#include "ResourceManager.h"
#include "BackgroundTypes.h"

// sound effects and music header
#include "soundbank.h"

PlayState PlayState::m_PlayState;

PlayState::PlayState() :	m_pScoreSprite1(NULL),
							m_pScoreSprite2(NULL),
							m_pSubScores(NULL),
							m_pPauseSprite(NULL)
{

}

bool PlayState::Init()
{
	/*
		The top screen is dedicated to 3D rendering so is set to mode 5 3D
		The bottom screen is 2D only so is set to mode 5 2D
	*/
	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);

	/*
		The A VRAM bank is mapped to enable 3D textures.
		C VRAM bank is used to hold the 128kb 16bit bitmap for the bottom screen scores
		D VRAM is used to enable rendering sprites to the bottom screen for scores
		E VRAM is used to hold the pause sprite on the top screen
	*/
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankE(VRAM_E_MAIN_SPRITE);

	// in order to draw sprites the oam surfaces must be initialised
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);

	// create the sprites
	m_pScoreSprite1 = new AnimatedSprite(11, 0, "bottom", "assets/score_Sprite.bin", SpriteSize_64x64, SpriteColorFormat_256Color, "assets/score_Pal.bin");
	m_pScoreSprite1->Load();

	m_pScoreSprite2 = new AnimatedSprite(11, 1, "bottom", "assets/score_Sprite.bin", SpriteSize_64x64, SpriteColorFormat_256Color, "assets/score_Pal.bin");
	m_pScoreSprite2->Load();

	m_pPauseSprite = new AnimatedSprite(11, 0, "top", "assets/pause_Sprite.bin", SpriteSize_64x64, SpriteColorFormat_Bmp);
	m_pPauseSprite->Load();

	// load the music and play it on a loop
	mmLoad(MOD_BEACH);
	mmStart( MOD_BEACH, MM_PLAY_LOOP );

	// create the background and dma copy it to the bottom screen
	m_pSubScores = new Background16B();
	m_pSubScores->CreateFromImageFile("bottom", BgSize_B16_256x256, "assets/scoreboard_16.bin", NULL, NULL, 3, 0, 0);
	m_pSubScores->Draw();

	// load the resources needed for this state
	if(!TheResourceManager::Instance()->LoadResources(TheGame::Instance()->GetPlaystateResourceFile()))
	{
		return false;
	}

	// load game objects
	TheGame::Instance()->LoadGameObjects(TheGame::Instance()->GetPlayStateObjectFile());

	// Display List for the court
	m_courtList.AddBeginQuads();
	m_courtList.AddVertexColour(31,31,31);
	m_courtList.AddTexCoords(0,0);
	m_courtList.AddVertex(-1.5f, 0.0f, -1.0f);
	m_courtList.AddTexCoords(128,0);
	m_courtList.AddVertex(1.5f, 0.0f, -1.0f);
	m_courtList.AddTexCoords(128,128);
	m_courtList.AddVertex(1.5f, 0.0f, 1.0f);
	m_courtList.AddTexCoords(0,128);
	m_courtList.AddVertex(-1.5f, 0.0f, 1.0f);
	m_courtList.End();

	// start in before state
	m_currentState = tennis::sub_beforeplay;

	// values to animate camera
	m_camStartZ = -20.0f;
	m_camEndZ = -6.0f;

	return true;
}

// Free textures and memory
void PlayState::Clean()
{
	TheResourceManager::Instance()->ClearResources();
	delete m_pScoreSprite1;
	delete m_pScoreSprite2;
	delete m_pSubScores;
	delete m_pPauseSprite;
}

// Pause this state
void PlayState::Pause()
{
}

// Resume this state
void PlayState::Resume()
{
}

void PlayState::Update(float gameSpeed) 
{
	// when someone wins, reset the scores and set to p1serve state - TODO move to another state displaying winner
	if(TheGame::Instance()->GetP1Score() >= 10 || TheGame::Instance()->GetP2Score() >= 10)
	{
		TheGame::Instance()->ResetScores();
		for(Game::GameObjects::const_iterator it = TheGame::Instance()->GetGameObjects().begin(); it != TheGame::Instance()->GetGameObjects().end(); ++it)
		{
			GameObject* p = it->second;
			p->SetState(tennis::states_p1serve);
		}
	}

	// update scores on bottom screen
	m_pScoreSprite1->SetCurrentFrame(TheGame::Instance()->GetP1Score());
	m_pScoreSprite2->SetCurrentFrame(TheGame::Instance()->GetP2Score());

	// only update movement if not in pause or game over
	if(m_currentState != tennis::sub_paused)
	{
		// Update all the objects
		for(Game::GameObjects::const_iterator it = TheGame::Instance()->GetGameObjects().begin(); it != TheGame::Instance()->GetGameObjects().end(); ++it)
		{
			GameObject* p = it->second;
			p->Update(gameSpeed);
		}

		// switch states of all objects when a score is made
		if(TheGame::Instance()->GetGameObject(2)->GetPosition().m_y > 11.0f)
		{
			TheGame::Instance()->IncrementP1Score();
			for(Game::GameObjects::const_iterator it = TheGame::Instance()->GetGameObjects().begin(); it != TheGame::Instance()->GetGameObjects().end(); ++it)
			{
				GameObject* p = it->second;
				p->SetState(tennis::states_p1serve);
			}
		}

		if(TheGame::Instance()->GetGameObject(2)->GetPosition().m_y < -11.0f)
		{
			TheGame::Instance()->IncrementP2Score();
			for(Game::GameObjects::const_iterator it = TheGame::Instance()->GetGameObjects().begin(); it != TheGame::Instance()->GetGameObjects().end(); ++it)
			{
				GameObject* p = it->second;
				p->SetState(tennis::states_p2serve);
			}
		}
	}

	// quick and cheerful pause :) // displays in emulator not on DS!
	if(TheGame::Instance()->KeyPressed(KEY_START) && m_currentState != tennis::sub_beforeplay)
	{
		if(m_currentState != tennis::sub_paused)
		{
			m_currentState = tennis::sub_paused;
		}
		else
		{
			m_currentState = tennis::sub_inplay;
		}
	}
}

void PlayState::Draw(IGraphicsRenderer* renderer) 
{
	// draw scores on bottom screen
	m_pScoreSprite1->Draw(137, 17);
	m_pScoreSprite2->Draw(137, 83);

	// quick and cheerful pause :) // displays in emulator not on DS!
	if(m_currentState == tennis::sub_paused)
	{
		m_pPauseSprite->Draw(100,70);
	}
	else
	{
		m_pPauseSprite->Draw(-100, -100);
	}

	renderer->StartRenderScene();

	/*
	Before play starts
	Animate the camera and then set all objects to the 1st player serve state
	*/
	if(m_currentState == tennis::sub_beforeplay)
	{
		if(m_camStartZ < m_camEndZ)
		{
			m_camStartZ += 0.3f;
		}
		else
		{
			m_currentState = tennis::sub_inplay;
			for(Game::GameObjects::const_iterator it = TheGame::Instance()->GetGameObjects().begin(); it != TheGame::Instance()->GetGameObjects().end(); ++it)
			{
				GameObject* p = it->second;
				p->SetState(tennis::states_p1serve);
			}
		}
	}

	// set the cameras position
	gluLookAt(0.0f, 15.0f, m_camStartZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// draw the game objects
	for(Game::GameObjects::const_iterator it = TheGame::Instance()->GetGameObjects().begin(); it != TheGame::Instance()->GetGameObjects().end(); ++it)
	{
		GameObject* p = it->second;
		p->Draw();
	}

	// draw the court with its loaded texture
	glPushMatrix();

	glScalef(10.0f, 1.0f, 10.0f);
	glTranslatef(0.0f, -4.0f, 0.0f);

	// bind the court texture
	glBindTexture(0, TheResourceManager::Instance()->GetTexture("court"));

	// draw the court
	glCallList(&m_courtList.m_list[0]);

	glPopMatrix(1);

	renderer->EndRenderScene();

}
