#ifndef FILE_H
#define FILE_H

#include <stdio.h>

class File
{
public:

	bool Open(const char* filename);
	bool GetInt(int *pInt);
	bool GetFloat(float *pFloat);
	bool GetString(char *pString);
	bool EndOfFile();

private:

	FILE* m_pFile;
};

#endif