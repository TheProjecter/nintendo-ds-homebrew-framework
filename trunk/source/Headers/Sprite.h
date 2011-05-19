#ifndef SPRITE_H
#define SPRITE_H

#include <nds.h>
#include <string>

class Sprite
{
public:

	Sprite();
	Sprite(int id, std::string screen, const char* imagefile, SpriteSize spriteSize, SpriteColorFormat spriteColourFormat);

	~Sprite();

	virtual void Load();
	void Draw(float x, float y);
	void Update();

protected:

	int m_id;
	void* m_graphicsData;
	u16* m_gfx;
	long m_spriteGraphicsSize;
	std::string m_screen;
	SpriteSize m_spriteSize;
	SpriteColorFormat m_colourFormat;
	const char* m_imageFile;
};


#endif