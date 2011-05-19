#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#include "GameObject.h"
#include <string>

class MeshObject : public GameObject
{
public:

	virtual ~MeshObject() {}

	virtual const char* GetTypeName() const { return "MeshObject"; }

	virtual bool Load(File* pFile);
	virtual void Update(float gameSpeed);
	virtual void Draw();

	void SetMesh(std::string meshName) { m_meshName = meshName; }
	void SetTexture(std::string texName) { m_texName = texName; }

protected:

	// default constructor
	MeshObject();

	std::string m_meshName;
	std::string m_texName;
	std::string m_currentAnim;

	float m_rotation;
	float m_animTimer;

	bool m_bMoving;

	void Animate();
};

#endif