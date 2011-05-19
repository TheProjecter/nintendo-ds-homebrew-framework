#ifndef IBACKGROUND_H
#define IBACKGROUND_H

#include <nds.h>
#include <string>

/*

Background Base Class
Wraps up libnds backgrounds
Shaun Mitchell 2011

---Allowed Background Sizes---

R = Rotation, ER = Extended Rotation, T = Text, B8 = 8bit Bmp, B16 = 16Bit Bmp

BgSize_R_128x128 	
BgSize_R_256x256 	
BgSize_R_512x512 	
BgSize_R_1024x1024 	
BgSize_T_256x256 	
BgSize_T_512x256 	
BgSize_T_256x512 	
BgSize_T_512x512 	
BgSize_ER_128x128 	
BgSize_ER_256x256 	
BgSize_ER_512x512 	
BgSize_ER_1024x1024 	
BgSize_B8_128x128 	
BgSize_B8_256x256 	
BgSize_B8_512x256 	
BgSize_B8_512x512 	
BgSize_B8_1024x512 	
BgSize_B8_512x1024 	
BgSize_B16_128x128 	
BgSize_B16_256x256 	
BgSize_B16_512x256 	
BgSize_B16_512x512 	

---Allowed Background Types---

BgType_Text8bpp 	
8bpp Tiled background with 16 bit tile indexes and no allowed rotation or scaling

BgType_Text4bpp 	
4bpp Tiled background with 16 bit tile indexes and no allowed rotation or scaling

BgType_Rotation 	
Tiled background with 8 bit tile indexes Can be scaled and rotated.

BgType_ExRotation 	
Tiled background with 16 bit tile indexes Can be scaled and rotated.

BgType_Bmp8 	
Bitmap background with 8 bit color values which index into a 256 color palette.

BgType_Bmp16 	
Bitmap background with 16 bit color values of the form aBBBBBGGGGGRRRRR 
(if 'a' is set the pixel will be rendered...if not the pixel will be transparent)
*/

class IBackground
{
public:

	virtual ~IBackground() 
	{
		free(m_imageData);
		free(m_mapData);
		free(m_paletteData);
	}

	// create a background to be drawn on later
	virtual void CreateBlank(std::string screen, BgSize bgSize, int layer = 3, int mapBase = 0, int tileBase = 0) = 0;

	// create a background and load an image file
	virtual void CreateFromImageFile(std::string screen, BgSize bgSize, const char* imageFile = NULL, const char* paletteFile = NULL, 
		const char* mapFile = NULL, int layer = 3, int mapBase = 0, int tileBase = 0) = 0;

	// create a background and draw a colour onto it
	virtual void DrawColour(std::string screen, BgSize size, int r, int g, int b, int layer = 3, int mapBase = 0, int tileBase = 0) = 0;

	// draw the background // draw to a blank background if data passed in
	virtual void Draw(void* data = NULL) = 0;

	// get
	void* GetImageData() { if(m_imageData != NULL) return m_imageData; else return NULL; }
	void* GetPaletteData() { if(m_paletteData != NULL) return m_paletteData; else return NULL; }
	void* GetMapData() { if(m_mapData != NULL) return m_mapData; else return NULL; }

	int Get() { return m_bg; }

protected:

	IBackground() : m_bg(0),
					m_imageSize(0),
					m_paletteSize(0),
					m_imageData(NULL),
					m_paletteData(NULL),
					m_mapData(NULL)
	{

	}

	// the background id
	int m_bg;

	// file sizes
	long m_imageSize;
	long m_paletteSize;

	// data 
	void* m_imageData;
	void* m_paletteData;
	void* m_mapData;
};



#endif