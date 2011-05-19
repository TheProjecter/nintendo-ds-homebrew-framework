#ifndef BACKGROUND_TYPES_H
#define BACKGROUND_TYPES_H

#include "IBackground.h"

///////////////////////////////////////////////////////////////////////////////////////////
/*
	16bit BMP background

	Mode - MODE_5_2D

	Image - YES
	Palette - NO
	Map - NO
*/
///////////////////////////////////////////////////////////////////////////////////////////

class Background16B : public IBackground
{
public:

	Background16B() : IBackground()
	{

	}

	virtual void CreateBlank(std::string screen, BgSize bgSize, int layer = 3, int mapBase = 0, int tileBase = 0);

	virtual void CreateFromImageFile(std::string screen, BgSize bgSize, const char* imageFile = NULL, const char* paletteFile = NULL, 
		const char* mapFile = NULL, int layer = 3, int mapBase = 0, int tileBase = 0);

	virtual void DrawColour(std::string screen, BgSize bgSize, int r, int g, int b, int layer = 3, int mapBase = 0, int tileBase = 0);

	virtual void Draw(void* data = NULL);
};

///////////////////////////////////////////////////////////////////////////////////////////
/*
	8bit BMP background

	Mode - MODE_5_2D

	Image - YES
	Palette - YES
	Map - IF NEEDED
*/
///////////////////////////////////////////////////////////////////////////////////////////

class Background8B : public IBackground
{
public:

	virtual void CreateBlank(std::string screen, BgSize bgSize, int layer = 3, int mapBase = 0, int tileBase = 0);

	virtual void CreateFromImageFile(std::string screen, BgSize bgSize, const char* imageFile = NULL, const char* paletteFile = NULL, 
		const char* mapFile = NULL, int layer = 3, int mapBase = 0, int tileBase = 0);

	virtual void DrawColour(std::string screen, BgSize bgSize, int r, int g, int b, int layer = 3, int mapBase = 0, int tileBase = 0);

	virtual void Draw(void* data = NULL);
};

#endif