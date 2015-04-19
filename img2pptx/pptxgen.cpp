#include "StdAfx.h"
#include "pptxgen.h"
#include "template.h"
#include "helper.h"
#include "../LibTIFF/tiffio.h"
#include <Winsock2.h>

CPptxGenerator::CPptxGenerator()
{
}


CPptxGenerator::~CPptxGenerator()
{
}

// ---------------------------------------------------
// Interface methods
// ---------------------------------------------------
void CPptxGenerator::Reset()
{
	m_content_types.clear();
	m_slides.clear();
}

void CPptxGenerator::Write(string file)
{

	// Extract template
	CTemplate tmpl;
	string path = tmpl.Extract();
		
	// Copy images
	CopyImages(path);

	// Make XML changes
	MakeXMLChanges(path);

	// Compress template and copy it into output directory
	tmpl.CompressAndCopy(file);

	// Reset
	Reset();
}


void CPptxGenerator::MakeXMLChanges(string path)
{
	m_xml = new CXmlDocWrapper();
	
	AddContentTypes(path);

	
	delete m_xml;
}

void CPptxGenerator::CopyImages(string path)
{
}

void CPptxGenerator::AddContentTypes(string path)
{
//	content_types["jpg"] = "image/jpeg";
//	content_types["jpeg"] = "image/jpeg";
//	content_types["tif"] = "image/tiff";
//	content_types["png"] = "image/png";
//	content_types["bmp"] = "image/png";
//	content_types["rels"] = "application/vnd.openxmlformats-package.relationships+xml";
//	content_types["xml"] = "application/xml";

	m_xml->Load(path+"\\[Content_Types].xml");
	CXmlNodeWrapper root(m_xml->AsNode());
		
	map<string,string>::iterator it = m_content_types.begin();
	int n = 0;
	for(;it != m_content_types.end(); it++)
	{
		CXmlNodeWrapper node(root.InsertChildNode(n,"Default"));
		node.SetAttrValue("Extension",it->first);
		node.SetAttrValue("ContentType",it->second);
		n++;
	}

	/*map<string,bool> unique_exts;
	for ( unsigned int i = 0; i < m_items.size(); i++)
	{
		if ( m_items[i]->type == WordItem::Image)
		{
			WordImage *wi = (WordImage *)m_items[i];
			string ext = GetFileExtension(wi->source);
			if (ext == "bmp")
				ext = "png";
			if (!unique_exts[ext])
			{
				CXmlNodeWrapper node(root.InsertChildBefore(bnode.Interface(),"Default"));
				node.SetAttrValue("Extension",ext);
				node.SetAttrValue("ContentType",m_content_types[ext]);
				unique_exts[ext] = true;
			}
		}
	}*/
	m_xml->Save();

}

void CPptxGenerator::Reallocate(size_t newsize)
{
	if (m_slides.size() < newsize)	m_slides.resize(newsize);
}

Slide &CPptxGenerator::GetSlide(int slideno)
{
	Reallocate(slideno + 1);
	return m_slides[slideno];
}

void CPptxGenerator::GetImageSizes(Slide &s)
{
	string ext = GetFileExtension(s.imgfile);
	s.imgwidth = 300;
	s.imgheight = 376;

	if( ext == "jpg")
	{	
		

		FILE *f=fopen(s.imgfile.c_str(),"rb");
		fseek(f,0,SEEK_END);
		long len=ftell(f);
		fseek(f,0,SEEK_SET);
		if (len<24) {
			fclose(f);
			return;
		}
		unsigned char buf[24]; fread(buf,1,24,f);

		// For JPEGs, we need to read the first 12 bytes of each chunk.
		// We'll read those 12 bytes at buf+2...buf+14, i.e. overwriting the existing buf.
		if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF && buf[3]==0xE0 && buf[6]=='J' && buf[7]=='F' && buf[8]=='I' && buf[9]=='F')
		{ 
			long pos=2;
			while (buf[2]==0xFF)
			{
				if (buf[3]==0xC0 || buf[3]==0xC1 || buf[3]==0xC2 || buf[3]==0xC3 || buf[3]==0xC9 || buf[3]==0xCA || buf[3]==0xCB)
					break;
				pos += 2+(buf[4]<<8)+buf[5];
				if (pos+12>len) break;
				fseek(f,pos,SEEK_SET); fread(buf+2,1,12,f);
			}
		}
		fclose(f);

		 if (buf[0]==0xFF && buf[1]==0xD8 && buf[2]==0xFF)
		 { 
			 s.imgwidth = (buf[7]<<8) + buf[8];
			 s.imgheight = (buf[9]<<8) + buf[10];
		 }
	}
	else if(ext == "tif")
	{
		TIFFErrorHandler oldhandler;
		oldhandler = TIFFSetWarningHandler(NULL);
		TIFF* tif = TIFFOpen(s.imgfile.c_str(), "r");
		TIFFSetWarningHandler(oldhandler);
		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &s.imgwidth);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &s.imgheight);
		TIFFClose(tif);
	}
	else if(ext == "png" || ext == "bmp")
	{
		ifstream in(s.imgfile);
		unsigned int width, height;

		in.seekg(16);
		in.read((char *)&width, 4);
		in.read((char *)&height, 4);

		s.imgwidth  = ntohl(width);
		s.imgheight = ntohl(height);
	}
}


void CPptxGenerator::AddImage(int slideno, string file)
{
	Slide &s = GetSlide(slideno);
	s.imgfile = file;
	GetImageSizes(s);

	int t = 4;
}

void CPptxGenerator::AddText(int slideno, char* text, int col, int row, char *fntname, int fntsize, int b_r, int b_g, int b_b,int f_r, int f_g, int f_b, bool bold, bool italic, bool underline)
{
	Slide &s = GetSlide(slideno);
}

void CPptxGenerator::ImportText(int slideno, char* srcfile, char* fntname,int fntsize, int b_r, int b_g,int b_b,int f_r, int f_g,int f_b, bool bold, bool italic, bool underline)
{
	Slide &s = GetSlide(slideno);
}

void CPptxGenerator::SetProperties(char *title, char* author, char* subject, char* keyword, char* category, char* status, char* remark)
{
}

void CPptxGenerator::SetChangeSlideMethod(int slideno, bool click,long wait_time)
{
}