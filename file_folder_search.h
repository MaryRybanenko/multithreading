#ifndef FILE_SEARCH
#define FILE_SEARCH

#include"common.h"
#include <vector>

class cFileFoldSearch
{
public:
	cFileFoldSearch();
	~cFileFoldSearch();

	static BOOL CALLBACK cFileFoldSearch::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	static cFileFoldSearch* ptr;
	
	HWND hDisc, hPath, hFrase, hList;
	HWND hFind, hStop;
	HWND hSubdir;

	std::vector<TCHAR*> driveList;
	TCHAR path[255];
	TCHAR frase[255];
	TCHAR mask[255];

	TCHAR newDisc[255];
	TCHAR newMask[255];
	TCHAR currStr[5];

	WIN32_FIND_DATA fd;
	SYSTEMTIME st;
	bool subDir = false;

	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);

	void addDiscToCmboBox();
	//void getPathforSearch();

	TCHAR* makePath(TCHAR* disc, TCHAR* mask);
	TCHAR* makeRecPath(TCHAR* disc, TCHAR* currDir);
	void findFolder(WIN32_FIND_DATA &fd, SYSTEMTIME &st, TCHAR* disc);
	void findFile(WIN32_FIND_DATA &fd, SYSTEMTIME &st, TCHAR* disc);
	void startSearching(WIN32_FIND_DATA &fd, SYSTEMTIME &st, TCHAR* disc, TCHAR* mask, bool flag);

};


#endif FILE_SEARCH

