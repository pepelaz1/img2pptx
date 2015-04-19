#include <windows.h>
#include "archiver.h"

CArchiver::CArchiver()
{
}


CArchiver::~CArchiver()
{
}


void CArchiver::Unzip(unsigned char *buffer, int size, string path)
{
	char oldcurdir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, oldcurdir);
	SetCurrentDirectory(path.c_str());

	HZIP hz = OpenZip(buffer,size,0);
    ZIPENTRY ze;
	GetZipItem(hz,-1,&ze); 
	int numitems=ze.index;
	for (int zi=0; zi<numitems; zi++)
	{ 
		ZIPENTRY ze; 
		GetZipItem(hz, zi, &ze);
		UnzipItem(hz, zi, ze.name);       
	}
	CloseZip(hz);
	
	SetCurrentDirectory(oldcurdir);
}

void CArchiver::Unzip(string arcfile, string path)
{
	char oldcurdir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, oldcurdir);
	SetCurrentDirectory(path.c_str());

	HZIP hz = OpenZip(arcfile.c_str(), NULL);
    ZIPENTRY ze;
	GetZipItem(hz,-1,&ze); 
	int numitems=ze.index;
	for (int zi=0; zi<numitems; zi++)
	{ 
		ZIPENTRY ze; 
		GetZipItem(hz, zi, &ze);
		UnzipItem(hz, zi, ze.name);       
	}
	CloseZip(hz);
	SetCurrentDirectory(oldcurdir);
}

void CArchiver::ZipRecursively(string root, string path, HZIP hz)
{
	string dir = path + "\\*";
	WIN32_FIND_DATA ffdata;
	HANDLE find = FindFirstFile(dir.c_str(), &ffdata);
	do
	{
		if (strcmp(ffdata.cFileName,".") !=0 && 
			strcmp(ffdata.cFileName,"..") != 0 &&
			strcmp(ffdata.cFileName,"template.docx") != 0)
		{
			if ( ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				string cdir = path + "\\" + ffdata.cFileName;
				ZipRecursively(root, cdir,hz);
			}
			else
			{
				string dfile = path + "\\" + ffdata.cFileName;
				dfile.erase(0, root.length()+1);
				ZipAdd(hz,(const TCHAR *)dfile.c_str(),(const TCHAR *)dfile.c_str());
			}
		}
	}
	while(FindNextFileA(find, &ffdata));
	FindClose(find);
}

void CArchiver::Zip(string path)
{
	char oldcurdir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, oldcurdir);
	SetCurrentDirectory(path.c_str());

	HZIP hz = CreateZip("template.pptx",0);
	ZipRecursively(path, path, hz);
	CloseZip(hz);

	SetCurrentDirectory(oldcurdir);
}