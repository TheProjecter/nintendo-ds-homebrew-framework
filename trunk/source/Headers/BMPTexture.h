#ifndef BMP_TEXTURE_H
#define BMP_TEXTURE_H

/*
	BMP Texture Type
*/

#include "ITexture.h"

class BMPTexture : public ITexture
{
public:

	virtual const char* GetType() { return "bmp"; }
	virtual bool Load(int width, int height, const char* filename);

private:

	char* m_pixels;
	int m_width;
	int m_height;
};
#endif
