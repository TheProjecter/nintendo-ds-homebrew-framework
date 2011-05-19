#include <fstream>
#include <vector>
#include <iostream>

#include "DSMD2.h"
#include "DisplayList.h"
#include "ResourceManager.h"

using namespace std;

namespace
{
	float NORMALS[486] = 
	{-0.525731f,  0.000000f,  0.850651f,
	-0.442863f,  0.238856f,  0.864188f,
	-0.295242f,  0.000000f,  0.955423f,
	-0.309017f,  0.500000f,  0.809017f,
	-0.162460f,  0.262866f,  0.951056f,
	0.000000f,  0.000000f,  1.000000f,
	0.000000f,  0.850651f,  0.525731f,
	-0.147621f,  0.716567f,  0.681718f,
	0.147621f,  0.716567f,  0.681718f,
	0.000000f,  0.525731f,  0.850651f,
	0.309017f,  0.500000f,  0.809017f,
	0.525731f,  0.000000f,  0.850651f,
	0.295242f,  0.000000f,  0.955423f,
	0.442863f,  0.238856f,  0.864188f,
	0.162460f,  0.262866f,  0.951056f,
	-0.681718f,  0.147621f,  0.716567f,
	-0.809017f,  0.309017f,  0.500000f,
	-0.587785f,  0.425325f,  0.688191f,
	-0.850651f,  0.525731f,  0.000000f,
	-0.864188f,  0.442863f,  0.238856f,
	-0.716567f,  0.681718f,  0.147621f,
	-0.688191f,  0.587785f,  0.425325f,
	-0.500000f,  0.809017f,  0.309017f,
	-0.238856f,  0.864188f,  0.442863f,
	-0.425325f,  0.688191f,  0.587785f,
	-0.716567f,  0.681718f, -0.147621f,
	-0.500000f,  0.809017f, -0.309017f,
	-0.525731f,  0.850651f,  0.000000f,
	0.000000f,  0.850651f, -0.525731f,
	-0.238856f,  0.864188f, -0.442863f,
	0.000000f,  0.955423f, -0.295242f,
	-0.262866f,  0.951056f, -0.162460f,
	0.000000f,  1.000000f,  0.000000f,
	0.000000f,  0.955423f,  0.295242f,
	-0.262866f,  0.951056f,  0.162460f,
	0.238856f,  0.864188f,  0.442863f,
	0.262866f,  0.951056f,  0.162460f,
	0.500000f,  0.809017f,  0.309017f,
	0.238856f,  0.864188f, -0.442863f,
	0.262866f,  0.951056f, -0.162460f,
	0.500000f,  0.809017f, -0.309017f,
	0.850651f,  0.525731f,  0.000000f,
	0.716567f,  0.681718f,  0.147621f,
	0.716567f,  0.681718f, -0.147621f,
	0.525731f,  0.850651f,  0.000000f,
	0.425325f,  0.688191f,  0.587785f,
	0.864188f,  0.442863f,  0.238856f,
	0.688191f,  0.587785f,  0.425325f,
	0.809017f,  0.309017f,  0.500000f,
	0.681718f,  0.147621f,  0.716567f,
	0.587785f,  0.425325f,  0.688191f,
	0.955423f,  0.295242f,  0.000000f,
	1.000000f,  0.000000f,  0.000000f,
	0.951056f,  0.162460f,  0.262866f,
	0.850651f, -0.525731f,  0.000000f,
	0.955423f, -0.295242f,  0.000000f,
	0.864188f, -0.442863f,  0.238856f,
	0.951056f, -0.162460f,  0.262866f,
	0.809017f, -0.309017f,  0.500000f,
	0.681718f, -0.147621f,  0.716567f,
	0.850651f,  0.000000f,  0.525731f,
	0.864188f,  0.442863f, -0.238856f,
	0.809017f,  0.309017f, -0.500000f,
	0.951056f,  0.162460f, -0.262866f,
	0.525731f,  0.000000f, -0.850651f,
	0.681718f,  0.147621f, -0.716567f,
	0.681718f, -0.147621f, -0.716567f,
	0.850651f,  0.000000f, -0.525731f,
	0.809017f, -0.309017f, -0.500000f,
	0.864188f, -0.442863f, -0.238856f,
	0.951056f, -0.162460f, -0.262866f,
	0.147621f,  0.716567f, -0.681718f,
	0.309017f,  0.500000f, -0.809017f,
	0.425325f,  0.688191f, -0.587785f,
	0.442863f,  0.238856f, -0.864188f,
	0.587785f,  0.425325f, -0.688191f,
	0.688191f,  0.587785f, -0.425325f,
	-0.147621f,  0.716567f, -0.681718f,
	-0.309017f,  0.500000f, -0.809017f,
	0.000000f,  0.525731f, -0.850651f,
	-0.525731f,  0.000000f, -0.850651f,
	-0.442863f,  0.238856f, -0.864188f,
	-0.295242f,  0.000000f, -0.955423f,
	-0.162460f,  0.262866f, -0.951056f,
	0.000000f,  0.000000f, -1.000000f,
	0.295242f,  0.000000f, -0.955423f,
	0.162460f,  0.262866f, -0.951056f,
	-0.442863f, -0.238856f, -0.864188f,
	-0.309017f, -0.500000f, -0.809017f,
	-0.162460f, -0.262866f, -0.951056f,
	0.000000f, -0.850651f, -0.525731f,
	-0.147621f, -0.716567f, -0.681718f,
	0.147621f, -0.716567f, -0.681718f,
	0.000000f, -0.525731f, -0.850651f,
	0.309017f, -0.500000f, -0.809017f,
	0.442863f, -0.238856f, -0.864188f,
	0.162460f, -0.262866f, -0.951056f,
	0.238856f, -0.864188f, -0.442863f,
	0.500000f, -0.809017f, -0.309017f,
	0.425325f, -0.688191f, -0.587785f,
	0.716567f, -0.681718f, -0.147621f,
	0.688191f, -0.587785f, -0.425325f,
	0.587785f, -0.425325f, -0.688191f,
	0.000000f, -0.955423f, -0.295242f,
	0.000000f, -1.000000f,  0.000000f,
	0.262866f, -0.951056f, -0.162460f,
	0.000000f, -0.850651f,  0.525731f,
	0.000000f, -0.955423f,  0.295242f,
	0.238856f, -0.864188f,  0.442863f,
	0.262866f, -0.951056f,  0.162460f,
	0.500000f, -0.809017f,  0.309017f,
	0.716567f, -0.681718f,  0.147621f,
	0.525731f, -0.850651f,  0.000000f,
	-0.238856f, -0.864188f, -0.442863f,
	-0.500000f, -0.809017f, -0.309017f,
	-0.262866f, -0.951056f, -0.162460f,
	-0.850651f, -0.525731f,  0.000000f,
	-0.716567f, -0.681718f, -0.147621f,
	-0.716567f, -0.681718f,  0.147621f,
	-0.525731f, -0.850651f,  0.000000f,
	-0.500000f, -0.809017f,  0.309017f,
	-0.238856f, -0.864188f,  0.442863f,
	-0.262866f, -0.951056f,  0.162460f,
	-0.864188f, -0.442863f,  0.238856f,
	-0.809017f, -0.309017f,  0.500000f,
	-0.688191f, -0.587785f,  0.425325f,
	-0.681718f, -0.147621f,  0.716567f,
	-0.442863f, -0.238856f,  0.864188f,
	-0.587785f, -0.425325f,  0.688191f,
	-0.309017f, -0.500000f,  0.809017f,
	-0.147621f, -0.716567f,  0.681718f,
	-0.425325f, -0.688191f,  0.587785f,
	-0.162460f, -0.262866f,  0.951056f,
	0.442863f, -0.238856f,  0.864188f,
	0.162460f, -0.262866f,  0.951056f,
	0.309017f, -0.500000f,  0.809017f,
	0.147621f, -0.716567f,  0.681718f,
	0.000000f, -0.525731f,  0.850651f,
	0.425325f, -0.688191f,  0.587785f,
	0.587785f, -0.425325f,  0.688191f,
	0.688191f, -0.587785f,  0.425325f,
	-0.955423f,  0.295242f,  0.000000f,
	-0.951056f,  0.162460f,  0.262866f,
	-1.000000f,  0.000000f,  0.000000f,
	-0.850651f,  0.000000f,  0.525731f,
	-0.955423f, -0.295242f,  0.000000f,
	-0.951056f, -0.162460f,  0.262866f,
	-0.864188f,  0.442863f, -0.238856f,
	-0.951056f,  0.162460f, -0.262866f,
	-0.809017f,  0.309017f, -0.500000f,
	-0.864188f, -0.442863f, -0.238856f,
	-0.951056f, -0.162460f, -0.262866f,
	-0.809017f, -0.309017f, -0.500000f,
	-0.681718f,  0.147621f, -0.716567f,
	-0.681718f, -0.147621f, -0.716567f,
	-0.850651f,  0.000000f, -0.525731f,
	-0.688191f,  0.587785f, -0.425325f,
	-0.587785f,  0.425325f, -0.688191f,
	-0.425325f,  0.688191f, -0.587785f,
	-0.425325f, -0.688191f, -0.587785f,
	-0.587785f, -0.425325f, -0.688191f,
	-0.688191f, -0.587785f, -0.425325f};

	//Returns whether the system is little-endian
	bool littleEndian() {
		//The short value 1 has bytes (1, 0) in little-endian and (0, 1) in
		//big-endian
		short s = 1;
		return (((char*)&s)[0]) == 1;
	}

	//Converts a four-character array to an integer, using little-endian form
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
			((unsigned char)bytes[2] << 16) |
			((unsigned char)bytes[1] << 8) |
			(unsigned char)bytes[0]);
	}

	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
			(unsigned char)bytes[0]);
	}

	//Converts a two-character array to an unsigned short, using little-endian
	//form
	unsigned short toUShort(const char* bytes) {
		return (unsigned short)(((unsigned char)bytes[1] << 8) |
			(unsigned char)bytes[0]);
	}

	//Converts a four-character array to a float, using little-endian form
	float toFloat(const char* bytes) {
		float f;
		if (littleEndian()) {
			((char*)&f)[0] = bytes[0];
			((char*)&f)[1] = bytes[1];
			((char*)&f)[2] = bytes[2];
			((char*)&f)[3] = bytes[3];
		}
		else {
			((char*)&f)[0] = bytes[3];
			((char*)&f)[1] = bytes[2];
			((char*)&f)[2] = bytes[1];
			((char*)&f)[3] = bytes[0];
		}
		return f;
	}

	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}

	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}

	//Reads the next two bytes as an unsigned short, using little-endian form
	unsigned short readUShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toUShort(buffer);
	}

	//Reads the next four bytes as a float, using little-endian form
	float readFloat(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toFloat(buffer);
	}

	//Calls readFloat three times and returns the results as a Vec3f object
	Vec3f readVector(ifstream &input) {
		float x = readFloat(input);
		float y = readFloat(input);
		float z = readFloat(input);
		return Vec3f(x,y,z);
	}
}

DSMD2::~DSMD2()
{
	if (m_frames != NULL) {
		for(int i = 0; i < m_numFrames; i++) {
			delete[] m_frames[i].vertices;
		}
		delete[] m_frames;
	}

	if (m_texCoords != NULL) {
		delete[] m_texCoords;
	}
	if (m_triangles != NULL) {
		delete[] m_triangles;
	}
}

DSMD2::DSMD2()
{
	m_frames = NULL;
	m_texCoords = NULL;
	m_triangles = NULL;
}

bool DSMD2::Load(const char* filename)
{
	ifstream input;
	input.open(filename, istream::binary);

	char buffer[64];
	input.read(buffer, 4); //Should be "IPD2", if this is an MD2 file
	if (buffer[0] != 'I' || buffer[1] != 'D' ||
		buffer[2] != 'P' || buffer[3] != '2') {
			return false;
	}
	if (readInt(input) != 8) { //The version number
		return false;
	}

	uint16 textureWidth = readInt(input);   //The width of the textures
	uint16 textureHeight = readInt(input);  //The height of the textures
	readInt(input);                      //The number of bytes per frame
	uint16 numTextures = readInt(input);    //The number of textures
	if (numTextures != 1) {
		return false;
	}
	uint16 numVertices = readInt(input);    //The number of vertices
	uint16 numTexCoords = readInt(input);   //The number of texture coordinates
	uint16 numTriangles = readInt(input);   //The number of triangles
	readInt(input);                      //The number of OpenGL commands
	uint16 numFrames = readInt(input);      //The number of frames

	//Offsets (number of bytes after the beginning of the file to the beginning
	//of where certain data appear)
	readInt(input);                      //The offset to the textures
	uint16 texCoordOffset = readInt(input); //The offset to the texture coordinates
	uint16 triangleOffset = readInt(input); //The offset to the triangles
	uint16 frameOffset = readInt(input);    //The offset to the frames
	readInt(input);                      //The offset to the OpenGL commands
	readInt(input);                      //The offset to the end of the file

	///Load the texture coordinates
	input.seekg(texCoordOffset, ios_base::beg);
	this->m_texCoords = new DSMD2TexCoord[numTexCoords];
	for(int i = 0; i < numTexCoords; i++) {
		DSMD2TexCoord* texCoord = this->m_texCoords + i;
		texCoord->texCoordX = (float)readShort(input) / textureWidth;
		texCoord->texCoordY = 1 - (float)readShort(input) / textureHeight;
	}

	//Load the triangles
	input.seekg(triangleOffset, ios_base::beg);
	this->m_triangles = new DSMD2Triangle[numTriangles];
	this->m_numTriangles = numTriangles;
	for(int i = 0; i < numTriangles; i++) {
		DSMD2Triangle* triangle = this->m_triangles + i;
		for(int j = 0; j < 3; j++) {
			triangle->vertices[j] = readUShort(input);
		}
		for(int j = 0; j < 3; j++) {
			triangle->texCoords[j] = readUShort(input);
		}
	}

	//Load the frames
	input.seekg(frameOffset, ios_base::beg);
	this->m_frames = new DSMD2Frame[numFrames];
	this->m_numFrames = numFrames;
	for(int i = 0; i < numFrames; i++) {
		DSMD2Frame* frame = this->m_frames + i;
		frame->vertices = new DSMD2Vertex[numVertices];
		Vec3f scale = readVector(input);
		Vec3f translation = readVector(input);
		input.read(frame->name, 16);

		for(int j = 0; j < numVertices; j++) {
			DSMD2Vertex* vertex = frame->vertices + j;
			input.read(buffer, 3);
			Vec3f v((unsigned char)buffer[0], (unsigned char)buffer[1], (unsigned char)buffer[2]);
			vertex->pos = translation + Vec3f(scale.m_x * v.m_x, scale.m_y * v.m_y, scale.m_z * v.m_z);

			input.read(buffer, 1);
			int normalIndex = (int)((unsigned char)buffer[0]);
			vertex->normal = Vec3f(NORMALS[3 * normalIndex],
				NORMALS[3 * normalIndex + 1],
				NORMALS[3 * normalIndex + 2]);
		}
	}

	this->m_startFrame = 0;
	this->m_endFrame = numFrames - 1;
	
	return true;
}

void DSMD2::SetAnimation(const char* name)
{
	bool found = false;

	for(int i = 0; i < m_numFrames; i++) {
		DSMD2Frame* frame = m_frames + i;
		if (strlen(frame->name) > strlen(name) &&
			strncmp(frame->name, name, strlen(name)) == 0 &&
			!isalpha(frame->name[strlen(name)])) {
			if (!found) {
				found = true;
				m_startFrame = i;
			}
			else {
				m_endFrame = i;
			}
		}
		else if (found) {
			break;
		}
	}
}


void DSMD2::Draw(float time, std::string textureName) 
{
	if (time > -100000000 && time < 1000000000) {
		time -= (int)time;
		if (time < 0) {
			time += 1;
		}
	}
	else 
	{
		time = 0;
	}

	glEnable(GL_TEXTURE_2D);
	//Use the appropriate texture
	glBindTexture(GL_TEXTURE_2D, TheResourceManager::Instance()->GetTexture(textureName));

	//Figure out the two frames between which we are interpolating
	int frameIndex1 = (int)(time * (m_endFrame - m_startFrame + 1)) + m_startFrame;
	if (frameIndex1 > m_endFrame) {
		frameIndex1 = m_startFrame;
	}

	int frameIndex2;
	if (frameIndex1 < m_endFrame) {
		frameIndex2 = frameIndex1 + 1;
	}
	else {
		frameIndex2 = m_startFrame;
	}

	DSMD2Frame* frame1 = m_frames + frameIndex1;
	DSMD2Frame* frame2 = m_frames + frameIndex2;

	//Figure out the fraction that we are between the two frames
	float frac =
		(time - (float)(frameIndex1 - m_startFrame) /
		(float)(m_endFrame - m_startFrame + 1)) * (m_endFrame - m_startFrame + 1);

	//Draw the this as an interpolation between the two frames
	glBegin(GL_TRIANGLES);
	
	for(int i = 0; i < m_numTriangles; i++) {
		DSMD2Triangle* triangle = m_triangles + i;
		for(int j = 2; j >= 0; j--) {
			DSMD2Vertex* v1 = frame1->vertices + triangle->vertices[j];
			DSMD2Vertex* v2 = frame2->vertices + triangle->vertices[j];
			Vec3f pos = v1->pos * (1 - frac) + v2->pos * frac;
			Vec3f normal = v1->normal * (1 - frac) + v2->normal * frac;
			if (normal.m_x == 0 && normal.m_y == 0 && normal.m_z == 0) {
				normal = Vec3f(0, 0, 1);
			}
			glNormal3f(normal.m_x, normal.m_y, normal.m_z);

			DSMD2TexCoord* texCoord = m_texCoords + triangle->texCoords[j];
			glTexCoord2f(texCoord->texCoordX, texCoord->texCoordY);
			glVertex3f(pos.m_x, pos.m_y, pos.m_z);
		}
	}
	glEnd();
}
