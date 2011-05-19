#ifndef I_TEXTURE_H
#define I_TEXTURE_H

/*
	Texture base class
*/

class ITexture
{
public:

	virtual ~ITexture() {}
	virtual const char* GetType() = 0;

	virtual bool Load(int width, int height, const char* filename) = 0;

	int Get() { return m_texture; }

protected:

	ITexture() {}

	int m_texture;
};

#endif