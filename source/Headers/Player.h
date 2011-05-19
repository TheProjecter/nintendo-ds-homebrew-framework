#ifndef PLAYER_H
#define PLAYER_H

#include "MeshObject.h"

class Player : public MeshObject
{
public:

	Player();

	static GameObject* CreatePlayer();
	virtual const char* GetTypeName() const { return "Player"; }

	virtual bool Load(File* pFile);
	virtual void Update(float gameSpeed);
	virtual void Draw();

private:

	void HandleInput();

	float m_stylusLastX;
	float m_stylusLastY;
};

#endif

