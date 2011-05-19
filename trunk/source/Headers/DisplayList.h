#ifndef DISPLAY_LIST_H
#define DISPLAY_LIST_H

#include <nds.h>
#include <vector>

class DisplayList
{
public:

	DisplayList();

	void AddBeginTriangles();
	void AddBeginTriangleStrip();
	void AddBeginQuads();
	void AddPack();
	void ClearTempValues();
	void End();

	void AddVertex(float x, float y, float z);
	void AddVertexColour(int r, int g, int b);
	void AddTexCoords(int x, int y);
	void AddNormals(float x, float y, float z);

	std::vector<u32> m_list;

private:

	std::vector<u32> m_tempValues;
	std::vector<u32> m_tempDataTypes;

	int m_listSize;
	int m_listCount;
	int m_tempListCount;
};

#endif