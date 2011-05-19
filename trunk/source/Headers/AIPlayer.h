#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "MeshObject.h"

class AIPlayer : public MeshObject
{

public:

	AIPlayer();

	static GameObject* CreateAIPlayer();

	virtual const char* GetType() { return "AIPlayer"; }

	virtual bool Load(File* pFile);
	virtual void Update(float gameSpeed);
	virtual void Draw();

private:

	void DoAI();
};

#endif