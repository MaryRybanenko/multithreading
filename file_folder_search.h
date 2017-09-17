#ifndef FILE_SEARCH
#define FILE_SEARCH

#include"common.h"

class cFileFoldSearch
{
public:
	cFileFoldSearch();
	~cFileFoldSearch();

	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static cFileFoldSearch* ptr;

	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);

};


#endif FILE_SEARCH

