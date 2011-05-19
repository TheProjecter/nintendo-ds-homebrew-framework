#ifndef IMESH_H
#define IMESH_H

/*
	Mesh base class
	Derive mesh types
*/
#include <string>

class IMesh
{
public:

	virtual ~IMesh() {}

	virtual const char* GetType() = 0;
	virtual bool Load(const char* filename) = 0;

	virtual void Draw(float time, std::string textureName) {}
	virtual void Draw(float time) {}


	virtual void SetAnimation(const char* name) {}
	virtual void SetAnimation(int startFrame, int endFrame) {}

protected:

	IMesh() {}
};

#endif