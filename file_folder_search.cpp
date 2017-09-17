#include"file_folder_search.h"

cFileFoldSearch* cFileFoldSearch::ptr = nullptr;

cFileFoldSearch::cFileFoldSearch()
{
	ptr = this;
}

cFileFoldSearch::~cFileFoldSearch()
{
}


void cFileFoldSearch::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}