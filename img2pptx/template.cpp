#include "StdAfx.h"
#include "template.h"
#include "helper.h"
#include "archiver.h"
#include "resource.h"

string CTemplate::Extract()
{
  // Get temporary path
	char s[MAX_PATH];
	GetTempPath(MAX_PATH,s);
	string path = s;
	path = path + "\\"+"img2pptx";

	// Check whether \img2pptx  directory exists and create if not
	CreateDirectory(path.c_str(), NULL);

	// Clear the temp directory
	ClearDirectory(path);

	// Read template into buffer
	Read();

	// Unzip template
	CArchiver arc;
	arc.Unzip((unsigned char *)m_buffer.data(), m_buffer.size(), path);

	// Save path
	m_path = path;
	return m_path;
}

extern HMODULE g_Module;

void CTemplate::Read()
{
	HRSRC resource = FindResource(g_Module,MAKEINTRESOURCE(IDR_PPTX1),"PPTX");
	if (resource)
	{
		HGLOBAL loaded = LoadResource(g_Module, resource);
		if (loaded)
		{
			void *p = LockResource(loaded);
			if (p)
			{
				DWORD size = SizeofResource(g_Module, resource);
				m_buffer.append((char *)p,size);
			}
		}
	}
}

void CTemplate::CompressAndCopy(string dstfile)
{
	// Zip it
	CArchiver arc;
	arc.Zip(m_path);

	// Copy to target path
	CopyFile((m_path + "\\template.pptx").c_str(),dstfile.c_str(), false);
}