#ifndef BALL_H
#define BALL_H

#include "MeshObject.h"

class Ball : public MeshObject
{
public:

	Ball();

	virtual const char* GetTypeName() const { return "Ball"; }

	static GameObject* CreateBall();
	virtual bool Load(File* pFile);
	virtual void Update(float gameSpeed);
	virtual void Draw();
};

#endif