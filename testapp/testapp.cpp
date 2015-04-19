
#include "stdafx.h"
#include "../img2pptx/img2pptx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	AddImage(0, "c:\\1.jpg");
	CreatePptx("text.pptx");
	return 0;
}

