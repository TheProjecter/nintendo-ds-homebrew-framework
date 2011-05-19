#include "AnimateSprite.h"
#include <fstream>

AnimatedSprite::AnimatedSprite() : Sprite()
{

}

AnimatedSprite::AnimatedSprite(int numFrames, int id, std::string screen, const char* imagefile, SpriteSize spriteSize, SpriteColorFormat spriteColourFormat, const char* palFile) :
Sprite(id, screen, imagefile, spriteSize, spriteColourFormat),
	m_numFrames(numFrames),
	m_palFile(palFile)
{
	for(int i = 0; i < numFrames; i++)
	{
		u16* temp = NULL;
		m_frames.push_back(temp);
	}
}


void AnimatedSprite::Load()
{
	if(m_palFile != NULL)
	{
		FILE* pFile2 = fopen(m_palFile, "rb");
		void* data = malloc(256*2);
		fread(data, 256*2, 1, pFile2);
		fclose(pFile2);

		if(m_screen == "top")
		{
			dmaCopy(data, SPRITE_PALETTE, 256*2);
		}
		else if(m_screen == "bottom")
		{
			dmaCopy(data, SPRITE_PALETTE_SUB, 256*2);
		}
	}

	FILE* pFile = fopen(m_imageFile, "rb");

	// get file size
	fseek(pFile, 0, SEEK_END);
	m_spriteGraphicsSize = ftell(pFile);
	rewind(pFile);

	m_graphicsData = malloc(m_spriteGraphicsSize);

	// read the data then close the file
	fread(m_graphicsData, m_spriteGraphicsSize, 3, pFile);
	fclose(pFile);

	// allocate some memory for the sprites
	if(m_screen == "top")
	{
		for(int i = 0; i < m_numFrames; i++)
		{
			m_frames[i] = oamAllocateGfx(&oamMain, m_spriteSize, m_colourFormat);
			if(m_colourFormat == SpriteColorFormat_256Color)
			{
				dmaCopy(m_graphicsData, m_frames[i], 64*64);
				m_graphicsData += 64*64;
			}
			else if(m_colourFormat == SpriteColorFormat_Bmp)
			{
				dmaCopy(m_graphicsData, m_frames[i], 64*64*2);
				m_graphicsData += 64*64*2;
			}
		}
	}
	else if(m_screen == "bottom")
	{
		for(int i = 0; i < m_numFrames; i++)
		{
			m_frames[i] = oamAllocateGfx(&oamSub, m_spriteSize, m_colourFormat);
			if(m_colourFormat == SpriteColorFormat_256Color)
			{
				dmaCopy(m_graphicsData, m_frames[i], 64*64);
				m_graphicsData += 64*64;
			}
			else if(m_colourFormat == SpriteColorFormat_Bmp)
			{
				dmaCopy(m_graphicsData, m_frames[i], 64*64*2);
				m_graphicsData += 64*64*2;
			}
		}
	}
}

void AnimatedSprite::Draw(float x, float y)
{
	if(m_screen == "top")
	{
		oamSet(&oamMain, m_id, x, y, 0, 0, m_spriteSize, m_colourFormat, 
			m_frames[m_currentFrame], 0, false, false, false, false, false);
	}
	else if(m_screen == "bottom")
	{
		oamSet(&oamSub, m_id, x, y, 0, 0, m_spriteSize, m_colourFormat, 
			m_frames[m_currentFrame], 0, false, false, false, false, false);
	}

	swiWaitForVBlank();

	if(m_screen == "top")
	{
		oamUpdate(&oamMain);
	}
	else if(m_screen == "bottom")
	{
		oamUpdate(&oamSub);
	}
}





