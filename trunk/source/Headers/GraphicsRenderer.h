#ifndef _GRAPHICS_RENDERER_H
#define _GRAPHICS_RENDERER_H

class IGraphicsRenderer
{
public:

	virtual ~IGraphicsRenderer() {}
	IGraphicsRenderer() {}

	virtual const char* GetTypeName() const = 0;

	virtual bool Init() = 0;
	virtual void StartRenderScene() = 0;
	virtual void EndRenderScene() = 0;

private:


};

#endif