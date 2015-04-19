#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include "xmlwrapper.h"
#include "structures.h"

class CPptxGenerator
{
private:
	CXmlDocWrapper *m_xml;
	map<string,string> m_content_types;
	vector<Slide>m_slides;

	void Reallocate(size_t newsize);
	Slide &GetSlide(int slideno);
	void GetImageSizes(Slide &s);
	void MakeXMLChanges(string path);
	void AddContentTypes(string path);
	void CopyImages(string path);
public:
	CPptxGenerator();
	~CPptxGenerator();

	// Interface methods
	void Write(string file);
	void Reset();
	void AddImage(int slideno, string file);
	void AddText(int slideno, char* text, int col, int row, char *fntname, int fntsize, int b_r, int b_g, int b_b,int f_r, int f_g, int f_b, bool bold, bool italic, bool underline);
	void ImportText(int slideno, char* srcfile, char* fntname,int fntsize, int b_r, int b_g,int b_b,int f_r, int f_g,int f_b, bool bold, bool italic, bool underline);
	void SetProperties(char *title, char* author, char* subject, char* keyword, char* category, char* status, char* remark);
	void SetChangeSlideMethod(int slideno, bool click,long wait_time);
};

