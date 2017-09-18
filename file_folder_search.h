#ifndef FILE_SEARCH
#define FILE_SEARCH

#include"common.h"

class cFileFoldSearch
{
public:
	cFileFoldSearch();
	~cFileFoldSearch();

	BOOL CALLBACK cFileFoldSearch::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static cFileFoldSearch* ptr;
	
	HWND hDisc, hPath, hFrase;
	HWND hFind, hStop;
	HWND hSubdir;

	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void addDiscToCmboBox();
	void getPathforSearch();
};


#endif FILE_SEARCH

