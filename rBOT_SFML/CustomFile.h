#pragma once
#include "PCH.h"
#include <fstream>

class CustomFile {
public:
	CustomFile(string filename);

	void write(string text);

	string readLine(int line);

	string getFileName();

	void clear();

private:
	fstream m_file;
	string m_filename;
};
