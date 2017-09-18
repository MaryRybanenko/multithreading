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

BOOL cFileFoldSearch::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{ 
	hDisc = GetDlgItem(hwnd, IDC_COMBDISC);
	hPath = GetDlgItem(hwnd, IDC_EFILE);
	hFrase = GetDlgItem(hwnd, IDC_EFRASE);
	hFind = GetDlgItem(hwnd, ID_BFIND);
	hStop = GetDlgItem(hwnd, ID_BSTOP);
	hSubdir = GetDlgItem(hwnd, IDC_CHSUBF);

	return TRUE;
}

void cFileFoldSearch::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_BFIND:
	{

		break;
	}

	case ID_BSTOP:
	{
	
		break;
	}
	}
}

BOOL CALLBACK cFileFoldSearch::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{ 
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose); 
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog); 
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand); 
	}
	return FALSE;
}

void cFileFoldSearch::addDiscToCmboBox()
{
	TCHAR drive_letter;
	int mask = GetLogicalDrives();

	for (drive_letter = 'a'; mask; mask >>= 1, ++drive_letter)
	{
		if (mask & 1) {
			SendMessage(hDisc, CB_ADDSTRING, 0, LPARAM(drive_letter));
		}
	}
}

void cFileFoldSearch::getPathforSearch()
{
	//int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
}

//IDC_COMBDISC - get disc
//IDC_EFILE - get other info