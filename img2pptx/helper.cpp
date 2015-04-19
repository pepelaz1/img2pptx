#include <windows.h>
#include "helper.h"

void ClearDirectory(string directory)
{
	string dir = directory + "\\*";
	WIN32_FIND_DATA ffdata;
	HANDLE find = FindFirstFile(dir.c_str(), &ffdata);
	do
	{
		if (strcmp(ffdata.cFileName,".") !=0 && 
			strcmp(ffdata.cFileName,"..") != 0)
		{
			if ( ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				string cdir = directory + "\\" + ffdata.cFileName;
				ClearDirectory(cdir);
				RemoveDirectory(cdir.c_str());
			}
			else
			{
				string dfile = directory + "\\" + ffdata.cFileName;
				DeleteFile(dfile.c_str());
			}
		}
	}
	while(FindNextFileA(find, &ffdata));
	FindClose(find);

	// Also remove directory itself
	//RemoveDirectory(directory.c_str());
}

char easytolower(char in)
{
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;

} 

string GetFileExtension(string FileName)
{
    if(FileName.find_last_of(".") != std::string::npos)
	{
       string s =  FileName.substr(FileName.find_last_of(".")+1);
	   transform(s.begin(), s.end(), s.begin(), easytolower);
	   return s;
	}
    return "";
}

