#ifndef ANIMATE_SPRITE_H
#define ANIMATE_SPRITE_H

#include "Sprite.h"
#include <vector>

class AnimatedSprite : public Sprite
{
public:

	AnimatedSprite();
	AnimatedSprite(int numFrames, int id, std::string screen, const char* imagefile, SpriteSize spriteSize, SpriteColorFormat spriteColourFormat, const char* palFile = NULL);

	void Load();
	void Draw(float x, float y);

	void SetCurrentFrame(int frame) { m_currentFrame = frame; }
	void Animate() {}


private:

	int m_numFrames;
	int m_currentFrame;
	std::vector<u16*> m_frames;

	const char* m_palFile;
};

#endif