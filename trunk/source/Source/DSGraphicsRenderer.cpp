#include "Headers\DSGraphicsRenderer.h"
#include <iostream>
#include <stdio.h>
#include <fat.h>

bool DSGraphicsRenderer::Init()
{
	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_3D);

	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankB(VRAM_B_TEXTURE);
	vramSetBankC(VRAM_C_TEXTURE);
	vramSetBankD(VRAM_D_TEXTURE);

	fatInitDefault();

	glInit(); // init 3d renderer

	glEnable(GL_ANTIALIAS);
	glEnable(GL_TEXTURE_2D);

	glClearColor(31,31,0,31);
	glClearPolyID(63);
	glClearDepth(0x7FFF);

	glViewport(0,0,255,191);

	//toon-table entry 0 is for completely unlit pixels, going up to entry 31 for completely lit
	//We block-fill it in two halves, we get cartoony 2-tone lighting
	glSetToonTableRange( 0, 15, RGB15(8,8,8) );
	glSetToonTableRange( 16, 31, RGB15(24,24,24) );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 300);

	//NB: When toon-shading, the hw ignores lights 2 and 3
	//Also note that the hw uses the RED component of the lit vertex to index the toon-table
	glLight(0, RGB15(16,16,16) , 0,		floattov10(1.0),		0);
	glLight(1, RGB15(16,16,16),   floattov10(1.0),	0,		0);

	glMaterialf(GL_AMBIENT, RGB15(8,8,8));
	glMaterialf(GL_DIFFUSE, RGB15(24,24,24));
	glMaterialf(GL_SPECULAR, RGB15(0,0,0));
	glMaterialf(GL_EMISSION, RGB15(0,0,0));

	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0 | POLY_FORMAT_LIGHT1); //| POLY_TOON_HIGHLIGHT);

	glMatrixMode(GL_MODELVIEW);

	std::cout << "Init DS Graphics Renderer Success\n";
	return true;
}

void DSGraphicsRenderer::StartRenderScene()
{
	glLoadIdentity();
}

void DSGraphicsRenderer::EndRenderScene()
{
	// flush to screen	
	glFlush(0);
}
