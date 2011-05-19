#ifndef SKYBOX_H
#define SKYBOX_H

#include "GameObject.h"
#include "DisplayList.h"

class SkyBox : public GameObject
{
public:

	SkyBox();
	~SkyBox() {}

	static GameObject* CreateSkyBox();
	virtual const char* GetTypeName() const { return "SkyBox"; }

	virtual bool Load(File* pFile);
	void Update(float gameSpeed);
	void Draw();
};

#endif