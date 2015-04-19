extern "C"
{
	__declspec( dllexport ) void __cdecl AddImage(int slideno, char *srcfile);
	__declspec( dllexport ) void __cdecl AddPptxText(int slideno, char* text, int col, int row, char *fntname, int fntsize, int b_r, int b_g, int b_b,int f_r, int f_g, int f_b, bool bold, bool italic, bool underline);
	__declspec( dllexport ) void __cdecl CreatePptx(char *dstfile);
	__declspec( dllexport ) void __cdecl Reset(void);
	__declspec( dllexport ) void __cdecl ImportFromText(int slideno, char* srcfile, char* fntname,int fntsize, int b_r, int b_g,int b_b,int f_r, int f_g,int f_b, bool bold, bool italic, bool underline);
	__declspec( dllexport ) void __cdecl PptxProperties(char *title, char* author, char* subject, char* keyword, char* category, char* status, char* remark);
	__declspec( dllexport ) void __cdecl ExtractImages( char *srcfile, char *dstfolder);
	__declspec( dllexport ) void __cdecl SetChangeSlideMethod(int slideno, bool click,long wait_time = 0);
};