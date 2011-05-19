#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Singleton.h"
#include "IMesh.h"
#include "ITexture.h"
#include <string>
#include <map>
#include <memory>

class ResourceManager
{
public:

	typedef std::map<std::string, ITexture*> Textures;
	typedef std::map<std::string, IMesh*> Meshes;

	~ResourceManager();

	bool LoadResources(std::string resourceFile);
	void ClearResources();

	void AddMesh(std::string meshFile, std::string name);
	void AddTexture(std::string textureFile, std::string name, int width, int height);

	IMesh* GetMesh(std::string name) { return m_meshes[name]; }
	int GetTexture(std::string name) { return m_textures[name]->Get(); }

private:

	ResourceManager();
	friend class Singleton<ResourceManager>;

	Textures m_textures;
	Meshes m_meshes;
};

typedef Singleton<ResourceManager> TheResourceManager;

#endif