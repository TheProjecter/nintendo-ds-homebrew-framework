#include "PCXTexture.h"
#include <nds.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

bool PCXTexture::Load(int width, int height, const char* filename)
{
	sImage pcx;
	void* data;
	FILE* pFile;
	long size;

	pFile = fopen(filename, "rb");
	if(pFile == NULL) 
	{ 
		std::cout << "could not open texture file: " << filename << "\n";
		return false;
	}
	fseek(pFile, 0, SEEK_END);
	size = ftell(pFile);
	rewind(pFile);

	data = malloc(size);

	fread(data, size, 1, pFile);
	fclose(pFile);

	loadPCX((u8*)data, &pcx);
	image8to16(&pcx);

	// allocate a texture name
	glGenTextures( 1, &m_texture );
	// select texture
	glBindTexture( GL_TEXTURE_2D, m_texture );

	// TODO, support different texture sizes
	glTexImage2D(0, 0, GL_RGB, TEXTURE_SIZE_128 , TEXTURE_SIZE_128, 0, TEXGEN_TEXCOORD, pcx.image.data8);

	// free buffer
	imageDestroy(&pcx);

	return true;
}