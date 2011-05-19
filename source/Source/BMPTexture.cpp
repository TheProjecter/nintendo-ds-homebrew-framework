#include "BMPTexture.h"
#include <nds.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

bool BMPTexture::Load(int width, int height, const char* filename)
{
	FILE* pFile;
	pFile = fopen(filename, "rb");
	void* data;
	data = malloc(256 * 256 * sizeof(u16));
	fread(data, 256 * 256 * sizeof(u16), 1, pFile);
	fclose(pFile);

	// allocate a texture name
	glGenTextures( 1, &m_texture );
	// select texture
	glBindTexture( GL_TEXTURE_2D, m_texture );

	// TODO, support different texture sizes
	glTexImage2D(0, 0, GL_RGB16, m_width , m_height, 0, TEXGEN_TEXCOORD , data);

	return true;
}