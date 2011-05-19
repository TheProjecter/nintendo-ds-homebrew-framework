#include "Sprite.h"
#include <fstream>

Sprite::Sprite() :	
	m_id(0), // careful here
	m_graphicsData(NULL),
	m_gfx(NULL),
	m_spriteGraphicsSize(0),
	m_screen(""),
	m_spriteSize(SpriteSize_16x16),
	m_colourFormat(SpriteColorFormat_16Color),
	m_imageFile("")

{

}

Sprite::Sprite(int id, std::string screen, const char* imagefile, SpriteSize spriteSize, SpriteColorFormat spriteColourFormat)	:	
	m_id(id),
	m_graphicsData(NULL),
	m_gfx(NULL),
	m_spriteGraphicsSize(0),
	m_screen(screen),
	m_spriteSize(spriteSize),
	m_colourFormat(spriteColourFormat),
	m_imageFile(imagefile)
{

}


Sprite::~Sprite()
{
	free(m_graphicsData);
	free(m_gfx);
}

void Sprite::Load()
{
	FILE* pFile = fopen(m_imageFile, "rb");

	// get file size
	fseek(pFile, 0, SEEK_END);
	m_spriteGraphicsSize = ftell(pFile);
	rewind(pFile);

	m_graphicsData = malloc(m_spriteGraphicsSize);

	// read the data then close the file
	fread(m_graphicsData, m_spriteGraphicsSize, 1, pFile);
	fclose(pFile);

	// allocate some memory for the sprites
	if(m_screen == "top")
	{
		m_gfx = oamAllocateGfx(&oamMain, m_spriteSize, m_colourFormat);
	}
	else if(m_screen == "bottom")
	{
		m_gfx = oamAllocateGfx(&oamSub, m_spriteSize, m_colourFormat);
	}

	dmaCopy(m_graphicsData, m_gfx, m_spriteGraphicsSize);
}

void Sprite::Draw(float x, float y)
{
	if(m_screen == "top")
	{
		oamSet(&oamMain, m_id, x, y, 0, 15, m_spriteSize, m_colourFormat, 
			m_gfx, 0, false, false, false, false, false);
	}
	else if(m_screen == "bottom")
	{
		oamSet(&oamSub, m_id, x, y, 0, 15, m_spriteSize, m_colourFormat, 
			m_gfx, 0, false, false, false, false, false);
	}

	//swiWaitForVBlank();

	if(m_screen == "top")
	{
		oamUpdate(&oamMain);
	}
	else if(m_screen == "bottom")
	{
		oamUpdate(&oamSub);
	}
}

void Sprite::Update()
{

}