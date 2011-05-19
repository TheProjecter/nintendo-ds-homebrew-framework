#ifndef _GL_GRAPHICS_RENDERER_H_
#define _GL_GRAPHICS_RENDERER_H_

#include "GraphicsRenderer.h"

class GLGraphicsRenderer : public IGraphicsRenderer
{
public:

	GLGraphicsRenderer() {}

	virtual const char* GetTypeName() const { return "GLGraphicsRenderer.h"; }

	virtual bool Init();
	virtual bool LoadSceneObjects();
	virtual void StartRenderScene();
	virtual void EndRenderScene();
	virtual void Update();
};

#endif