#include <nds.h>
#include "StartMenuState.h"
#include "ChooseCourtState.h"
#include "Game.h"

StartMenuState StartMenuState::m_StartMenuState;

StartMenuState::StartMenuState() :  m_mainBack(NULL),
									m_subBack(NULL)
{

}

bool StartMenuState::Init()
{
	/*
		Set up the video modes.
		MODE_5_2D allows for 4 2D backgrounds.
		Both screens are set up to use this mode.
	*/
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);

	/*
		Map the required banks for the backgrounds.
		This state uses a 16bit BMP for the top screen
		and a 16bit BMP for the bottom screen. A 16bit
		BMP takes up 128kb in memory, Bank A has 128kb
		and Bank C also has 128kb. They both need to be
		activated to use the backgrounds in this state.
	*/
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

	// Set the colour of the bottom screens background
	setBackdropColor(RGB15(31,31,0));
	setBackdropColorSub(RGB15(31,31,0));

	// Create the backgrounds and draw them directly into VRAM (see IBackground.h)
	m_mainBack = new Background16B();
	m_subBack = new Background16B();

	m_mainBack->CreateFromImageFile("top", BgSize_B16_256x256, "assets/toplogo_16.bin");
	m_mainBack->Draw();

	m_subBack->CreateFromImageFile("bottom", BgSize_B16_256x256, "assets/playbutton_16.bin");
	m_subBack->Draw();

	return true;
}

// delete the backgrounds
void StartMenuState::Clean()
{
	delete m_mainBack;
	delete m_subBack;
}

// Pause this state
void StartMenuState::Pause()
{

}

// Resume this state
void StartMenuState::Resume()
{
}

void StartMenuState::Update(float gameSpeed) 
{
	// Check if the stylus touched the Play button
	if(TheGame::Instance()->KeyPressed(KEY_TOUCH))
	{
		if(TheGame::Instance()->GetStylusX() > 34.0f && TheGame::Instance()->GetStylusX() < 230.0f
			&& TheGame::Instance()->GetStylusY() > 54.0f && TheGame::Instance()->GetStylusY() < 96.0f)
		{
			TheGame::Instance()->PushState(ChooseCourtState::Instance());
		}
	}
}

void StartMenuState::Draw(IGraphicsRenderer* renderer) 
{
	swiWaitForVBlank();
}
