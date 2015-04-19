// img2pptx.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "img2pptx.h"
#include "pptxgen.h"
#include "pptxexp.h"

CPptxGenerator g_Gen;
CPptxExporter g_Exp;

void  AddImage(int slideno, char *srcfile)
{
	g_Gen.AddImage(slideno, srcfile);
}

void  AddPptxText(int slideno, char* text, int col, int row, char *fntname, int fntsize, int b_r, int b_g, int b_b,int f_r, int f_g, int f_b, bool bold, bool italic, bool underline)
{
	g_Gen.AddText(slideno, text,col,row,fntname,fntsize, b_r, b_g, b_b, f_r, f_g, f_b, bold, italic, underline);
}

void  CreatePptx(char *dstfile)
{
	g_Gen.Write(dstfile);
}

 void  Reset(void)
 {
	g_Gen.Reset();
 }

void  ImportFromText(int slideno, char* srcfile, char* fntname,int fntsize, int b_r, int b_g,int b_b,int f_r, int f_g,int f_b, bool bold, bool italic, bool underline)
{
	g_Gen.ImportText(slideno, srcfile,fntname,fntsize, b_r, b_g, b_b, f_r, f_g, f_b, bold, italic, underline);
}

 void  PptxProperties(char *title, char* author, char* subject, char* keyword, char* category, char* status, char* remark)
 {
	 g_Gen.SetProperties(title,author,subject,keyword,category, status, remark);
 }

 void  ExtractImages( char *srcfile, char *dstfolder)
 {
	 g_Exp.Extract(srcfile, dstfolder);
 }

void  SetChangeSlideMethod(int slideno, bool click,long wait_time)
{
	g_Gen.SetChangeSlideMethod(slideno, click, wait_time);
}