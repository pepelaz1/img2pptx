#pragma once
#include <string>
using namespace std;
#include "consts.h"
#include "ziputils/zip.h"
#include "ziputils/unzip.h"

class CArchiver
{
private:
	void ZipRecursively(string root, string path, HZIP hz);
public:
	CArchiver();
	~CArchiver();

	void Unzip(unsigned char *buffer, int size, string path);
	void Unzip(string arcfile, string path);
	void Zip(string path);
};

