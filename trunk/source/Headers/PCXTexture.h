#ifndef PCX_TEXTURE_H
#define PCX_TEXTURE_H

/*
	PCX Texture type
	Good for DS as they are small
*/
#include "ITexture.h"

class PCXTexture : public ITexture
{
public:

	virtual const char* GetType() { return "pcx"; }
	virtual bool Load(int width, int height, const char* filename);
};

#endif
