#include "../Headers/DisplayList.h"

DisplayList::DisplayList() //: m_listSize(size)
{
	//m_list = new u32[m_listSize];
	// Increment list count, leaving [0] for the final count
	m_list.push_back(0);
	m_listCount = 1;
}

void DisplayList::AddBeginTriangles()
{
	m_tempValues.push_back(GL_TRIANGLES);
	m_tempDataTypes.push_back(FIFO_BEGIN);
	m_tempListCount++;
}

void DisplayList::AddBeginTriangleStrip()
{
	m_tempValues.push_back(GL_TRIANGLE_STRIP);
	m_tempDataTypes.push_back(FIFO_BEGIN);
	m_tempListCount++;
}

void DisplayList::AddBeginQuads()
{
	m_tempValues.push_back(GL_QUADS);
	m_tempDataTypes.push_back(FIFO_BEGIN);
	m_tempListCount++;
}

void DisplayList::AddVertex(float x, float y, float z)
{
	m_tempValues.push_back(VERTEX_PACK(floattov16(x), floattov16(y)));
	m_tempValues.push_back(VERTEX_PACK(floattov16(z), floattov16(z)));
	m_tempDataTypes.push_back(FIFO_VERTEX16);
	m_tempListCount++;

	if(m_tempListCount == 4)
	{
		AddPack();
	}
}

void DisplayList::AddVertexColour(int r, int g, int b)
{
	m_tempValues.push_back(RGB15(r,g,b));
	m_tempDataTypes.push_back(FIFO_COLOR);
	m_tempListCount++;

	if(m_tempListCount == 4)
	{
		AddPack();
	}
}

void DisplayList::AddTexCoords(int x, int y)
{
	if(x <= 0 && y <= 0)
	{
		m_tempValues.push_back(TEXTURE_PACK(inttot16(0), inttot16(0)));
	}
	else if(x > 0 && y > 0)
	{
		m_tempValues.push_back(TEXTURE_PACK(inttot16(128), inttot16(128)));
	}
	else if(x <= 0 && y > 0)
	{
		m_tempValues.push_back(TEXTURE_PACK(inttot16(0), inttot16(128)));
	}
	else if(x > 0 && y <= 0)
	{
		m_tempValues.push_back(TEXTURE_PACK(inttot16(128), inttot16(0)));
	}
	//m_tempValues.push_back(TEXTURE_PACK(inttot16(x), inttot16(y)));
	m_tempDataTypes.push_back(FIFO_TEX_COORD);
	m_tempListCount++;

	if(m_tempListCount == 4)
	{
		AddPack();
	}
}

void DisplayList::AddNormals(float x, float y, float z)
{
	m_tempValues.push_back(NORMAL_PACK(floattov10(x), floattov10(y), floattov10(z)));
	m_tempDataTypes.push_back(FIFO_NORMAL);
	m_tempListCount++;

	if(m_tempListCount == 4)
	{
		AddPack();
	}
}

void DisplayList::AddPack()
{
	for (int i = m_tempDataTypes.size(); i < 4; i++)
	{
		m_tempDataTypes.push_back(FIFO_END);
	}

	m_list.push_back(FIFO_COMMAND_PACK(m_tempDataTypes[0], m_tempDataTypes[1], m_tempDataTypes[2], m_tempDataTypes[3]));
	m_tempDataTypes.clear();

	m_listCount++;

	for (unsigned int i = 0; i < m_tempValues.size(); i++)
	{
		m_list.push_back(m_tempValues[i]);
		m_listCount++;
	}
	m_tempValues.clear();

    m_tempListCount = 0;
}

void DisplayList::End()
{
    AddPack();
	m_list[0] = m_listCount;
}

void DisplayList::ClearTempValues()
{
	m_tempValues.clear();
}