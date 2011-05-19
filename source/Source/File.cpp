#include "File.h"

bool File::Open(const char* filename)
{
	m_pFile = fopen(filename, "r");

	if(m_pFile == NULL)
	{
		return false;
	}

	return true;
}

bool File::GetInt(int *pInt)
{
	if(fscanf(m_pFile, "%d", pInt) == 1)
	{
		return true;
	}

	return false;
}

bool File::GetFloat (float *pFloat)
{
	if(fscanf(m_pFile, "%f", pFloat) == 1)
	{
		return true;
	}

	return false;
}

bool File::GetString(char *pString)
{
	if(fscanf(m_pFile, "%s", pString) == 1)
	{
		return true;
	}

	return false;
}

bool File::EndOfFile()
{
	return feof(m_pFile);
}