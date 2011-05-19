#ifndef DSMD2_H
#define DSMD2_H

#include <nds.h>
#include <vector>
#include <string>
#include "Vec3.h"
#include "IMesh.h"

struct DSMD2Vertex
{
	Vec3f pos;
	Vec3f normal;
};

struct DSMD2Frame
{
	char name[16];
	DSMD2Vertex* vertices;
};

struct DSMD2TexCoord
{
	float texCoordX;
	float texCoordY;
};

struct DSMD2Triangle
{
	v16 vertices[3];
	int texCoords[3];
};

class DSMD2 : public IMesh
{
public:

	DSMD2();
	~DSMD2();

	virtual const char* GetType() { return "md2"; }

	virtual void SetAnimation(const char* name);

	virtual void Draw(float time, std::string textureName);

	virtual bool Load(const char* filename);

private:

	DSMD2Frame* m_frames;
	uint16 m_numFrames;

	DSMD2TexCoord* m_texCoords;
	DSMD2Triangle* m_triangles;
	uint16 m_numTriangles;

	uint16 m_startFrame;
	uint16 m_endFrame;
};

#endif