#include "ResourceManager.h"
#include "TextureFactory.h"
#include "MeshFactory.h"
#include "HelperFunctions.h"
#include "File.h"
#include <iostream>
#include <memory>

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	ClearResources();
}

bool ResourceManager::LoadResources(std::string resourceFile)
{
	// load config file for this state
	File f;
	if(!f.Open(resourceFile.c_str()))
	{
		std::cout << "could not open/find " << resourceFile << "\n";
		return false;
	}

	// Load the resources for this state
	std::cout << "Loading resources ";
	while(!f.EndOfFile())
	{
		std::cout << ".";
		char type[50];
		if(f.GetString(type))
		{
			// if it's a texture
			if(strcmp(type, "Texture") == 0)
			{
				// get its filename, resource name, width and height
				char texFile[50], name[50];
				int width, height;
				f.GetString(texFile);
				f.GetString(name);
				f.GetInt(&width);
				f.GetInt(&height);

				// load and add to map
				AddTexture(texFile, name, width, height);
			}
			// if it's a mesh
			else if(strcmp(type, "Mesh") == 0)
			{
				// get its filename and resource name
				char meshFile[50], name[50];
				f.GetString(meshFile);
				f.GetString(name);
				AddMesh(meshFile, name);
			}
		}
		std::cout << ".";
	}
	std::cout << " done\n";

	return true;
}

void ResourceManager::ClearResources()
{
	m_meshes.clear();
	m_textures.clear();
}

// creates an IMesh from file extension
void ResourceManager::AddMesh(std::string meshFile, std::string name)
{
	IMesh* newMesh = TheMeshFactory::Instance()->Create(Helper::GetFileExtension(meshFile));
	newMesh->Load(meshFile.c_str());

	m_meshes.insert(std::pair<std::string, IMesh*>(name, newMesh));
}

// creates textures based on their file extensions
void ResourceManager::AddTexture(std::string textureFile, std::string name, int width, int height)
{
	ITexture* newTexture = TheTextureFactory::Instance()->Create(Helper::GetFileExtension(textureFile));
	newTexture->Load(width, height, textureFile.c_str());

	m_textures.insert(std::pair<std::string, ITexture*>(name, newTexture));
}
