#include "PCH.h"
#include "CustomFile.h"

CustomFile::CustomFile(string filename) {
	m_filename = filename;

	m_file.open(filename, ios_base::trunc | ios_base::out);
	m_file << "";
	m_file.close();
}

void CustomFile::write(string text) {
	m_file.open(m_filename, ios_base::app);

	m_file << text;

	m_file.close();
}

string CustomFile::readLine(int line) {
	string buffer;

	m_file.open(m_filename, ios_base::in);

	int counter = 0;
	while (counter < line) {
		counter++;
		getline(m_file, buffer);
	}
	m_file.close();

	return buffer;
}

string CustomFile::getFileName() {
	return m_filename;
}

void CustomFile::clear() {
	m_file.open(m_filename, ios_base::trunc | ios_base::out);
	m_file << "";
	m_file.close();
}
