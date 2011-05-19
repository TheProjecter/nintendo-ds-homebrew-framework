#include "BackgroundTypes.h"
#include <fstream>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////
/*
	16bit BMP background
*/
///////////////////////////////////////////////////////////////////////////////////////////
void Background16B::CreateBlank(std::string screen, BgSize bgSize, int layer, int mapBase, int tileBase)
{
	if(screen == "top")
	{
		// initialise the background
		m_bg = bgInit(layer, BgType_Bmp16, bgSize, mapBase, tileBase);
	}
	else if(screen == "bottom")
	{
		// initialise the background
		m_bg = bgInitSub(layer, BgType_Bmp16, bgSize, mapBase, tileBase);
	}
}

void Background16B::CreateFromImageFile(std::string screen, BgSize bgSize, const char* imageFile, 
				const char* paletteFile, const char* mapFile, int layer, int mapBase, int tileBase)
{
	if(imageFile != NULL)
	{
		// get the data from file
		FILE* pFile = fopen(imageFile, "rb");

		// get file size
		fseek(pFile, 0, SEEK_END);
		m_imageSize = ftell(pFile);
		rewind(pFile);

		// allocate some memory to the data pointer
		m_imageData = malloc(m_imageSize);

		// read the data then close the file
		fread(m_imageData, m_imageSize, 1, pFile);
		fclose(pFile);
	}

	if(screen == "top")
	{
		// initialise the background
		m_bg = bgInit(layer, BgType_Bmp16, bgSize, mapBase, tileBase);
	}
	else if(screen == "bottom")
	{
		// initialise the background
		m_bg = bgInitSub(layer, BgType_Bmp16, bgSize, mapBase, tileBase);
	}
}

void Background16B::DrawColour(std::string screen, BgSize bgSize, int r, int g, int b, 
					int layer, int mapBase, int tileBase)
{
	if(screen == "top")
	{
		m_bg = bgInit(layer, BgType_Bmp16, bgSize, mapBase, tileBase);

		// write the colour into the background
		for(int i = 0; i < 256 * 256; i++)
		{
			BG_GFX[i]=RGB15(r, g, b) | BIT(15);
		}

	}
	else if(screen == "bottom")
	{
		m_bg = bgInitSub(layer, BgType_Bmp16, bgSize, mapBase, tileBase);

		//write the colour into the background
		for(int i = 0; i < 256 * 256; i++)
		{
			BG_GFX_SUB[i]=RGB15(r, g, b) | BIT(15);
		}
	}
}

void Background16B::Draw(void* data)
{
	if(data != NULL)
	{
		dmaCopy(data, bgGetGfxPtr(m_bg), m_imageSize);
	}
	else
	{
		dmaCopy(m_imageData, bgGetGfxPtr(m_bg), m_imageSize);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////
/*
	8bit BMP background
*/
///////////////////////////////////////////////////////////////////////////////////////////
void Background8B::CreateBlank(std::string screen, BgSize bgSize, int layer, int mapBase, int tileBase)
{
	if(screen == "top")
	{
		// initialise the background
		m_bg = bgInit(layer, BgType_Bmp8, bgSize, mapBase, tileBase);
	}
	else if(screen == "bottom")
	{
		// initialise the background
		m_bg = bgInitSub(layer, BgType_Bmp8, bgSize, mapBase, tileBase);
	}
}

void Background8B::CreateFromImageFile(std::string screen, BgSize bgSize, const char* imageFile, const char* paletteFile, 
							const char* mapFile, int layer, int mapBase, int tileBase)
{
	if(imageFile != NULL)
	{
		// get the data from file
		FILE* pFile = fopen(imageFile, "rb");

		// get file size
		fseek(pFile, 0, SEEK_END);
		m_imageSize = ftell(pFile);
		rewind(pFile);

		// allocate some memory to the data pointer
		m_imageData = malloc(m_imageSize);

		// read the data then close the file
		fread(m_imageData, m_imageSize, 1, pFile);
		fclose(pFile);
	}

	if(paletteFile != NULL)
	{
		// get the data from file
		FILE* pFile = fopen(paletteFile, "rb");
		// get file size
		fseek(pFile, 0, SEEK_END);
		m_paletteSize = ftell(pFile);
		rewind(pFile);

		// allocate some memory to the data pointer
		m_paletteData = malloc(m_imageSize);

		// read the data then close the file
		fread(m_paletteData, m_paletteSize, 1, pFile);
		fclose(pFile);
	}


	if(screen == "top")
	{
		// initialise the background
		m_bg = bgInit(layer, BgType_Bmp8, bgSize, mapBase, tileBase);
	}
	else if(screen == "bottom")
	{
		// initialise the background
		m_bg = bgInitSub(layer, BgType_Bmp8, bgSize, mapBase, tileBase);
	}
}

void Background8B::DrawColour(std::string screen, BgSize bgSize, int r, int g, int b, int layer, int mapBase, int tileBase)
{
	if(screen == "top")
	{
		m_bg = bgInit(layer, BgType_Bmp8, bgSize, mapBase, tileBase);

		// write the palette
		//for(int i = 0; i < 256; i++)
		//{
			BG_PALETTE[0] = RGB15(r, g, b) | BIT(15);
		//}

		//write the colour into the background
		for(int i = 0; i < 256; i++)
		{
			BG_GFX[i]=RGB15(r, g, b) | BIT(15);
		}

	}
	else if(screen == "bottom")
	{
		m_bg = bgInitSub(layer, BgType_Bmp8, bgSize, mapBase, tileBase);

		// write the palette
		//for(int i = 0; i < 256; i++)
		//{
			BG_PALETTE_SUB[0] = RGB15(r, g, b) | BIT(15);
		//}

		//write the color into the background
		for(int i = 0; i < 256; i++)
		{
			BG_GFX_SUB[i]=RGB15(r, g, b) | BIT(15);
		}
	}
}

void Background8B::Draw(void* data)
{
	if(data != NULL)
	{
		// copy the palette then the image data to VRAM
		dmaCopy(m_paletteData, BG_PALETTE, m_paletteSize);
		dmaCopy(data, bgGetGfxPtr(m_bg), m_imageSize);
	}
	else
	{
		dmaCopy(m_paletteData, BG_PALETTE, m_paletteSize);
		dmaCopy(m_imageData, bgGetGfxPtr(m_bg), m_imageSize);
	}
}