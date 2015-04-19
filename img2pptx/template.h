#pragma once
#include <string>
using namespace std;

class CTemplate
{
private:
	string m_path;
	string m_buffer;

	void Read();
public:
	string Extract();
    void CompressAndCopy(string dstfile);
};

