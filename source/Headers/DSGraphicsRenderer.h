#ifndef _DS_GRAPHICS_RENDERER_H
#define _DS_GRAPHICS_RENDERER_H

#include "GraphicsRenderer.h"

#include <nds.h> // Needed for DS graphics rendering
#include <nds/arm9/image.h>
#include <nds/arm9/trig_lut.h>

class DSGraphicsRenderer : public IGraphicsRenderer
{
public:

	DSGraphicsRenderer() {}

	virtual const char* GetTypeName() const { return "DSGraphicsRenderer"; }

	virtual bool Init();
	virtual void StartRenderScene();
	virtual void EndRenderScene();

};

#endif