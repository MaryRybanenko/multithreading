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
	hList = GetDlgItem(hwnd, IDC_FINDLIST);

	
	addDiscToCmboBox();

	return TRUE;
}

void cFileFoldSearch::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case ID_BFIND:
	{
		GetWindowText(hPath, mask, 255);
		GetWindowText(hFrase, frase, 255);

		if (lstrlen(mask) == 0)
		{
			MessageBox(hwnd, TEXT("Введите маску для поиска"), TEXT("Поиск папок и файлов"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			int index = SendMessage(hDisc, CB_GETCURSEL, 0, 0);
			startSearching(fd, st, driveList[index], mask, subDir);
			EnableWindow(hFind, FALSE);
		}
		break;
	}

	case ID_BSTOP:
	{
		EnableWindow(hStop, FALSE);
		EnableWindow(hFind, TRUE);

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
	
	char drive_letter;
	int mask = GetLogicalDrives();

	int i = 0;
	for (drive_letter = 'a'; mask; mask >>= 1, ++drive_letter)
	{
		if (mask & 1) {
			
			wsprintf(currStr, TEXT("%c:\\"), drive_letter);
			driveList.push_back(currStr);
			SendMessage(hDisc, CB_ADDSTRING, 0, LPARAM(driveList[i]));
			i++;
		}		
	}

	SendMessage(hDisc, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}


TCHAR* cFileFoldSearch::makePath(TCHAR* disc, TCHAR* mask)
{
	TCHAR path[255];
	wsprintf(path, TEXT("%s\\%s"), disc, mask);

	return path;
}

TCHAR* cFileFoldSearch::makeRecPath(TCHAR* disc, TCHAR* currDir)
{
	TCHAR path[255];
	wsprintf(path, TEXT("%s\\%s\\"), disc, currDir);

	return path;
}


void cFileFoldSearch::findFolder(WIN32_FIND_DATA &fd, SYSTEMTIME &st, TCHAR* disc)
{
	TCHAR szBuf[300];
	TCHAR szTime[50];
	TCHAR *szFullPath = makePath(disc, fd.cFileName);

	FileTimeToLocalFileTime(&fd.ftLastWriteTime, &fd.ftLastWriteTime);
	if (FileTimeToSystemTime(&fd.ftLastWriteTime, &st) == TRUE)
	{
		wsprintf(szTime, TEXT("%.2d.%.2d.%d    %.2d:%.2d"), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
	}

	wsprintf(szBuf, TEXT("%-100s%-50s\n"), fd.cFileName, szTime);
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(szBuf));
}

void cFileFoldSearch::findFile(WIN32_FIND_DATA &fd, SYSTEMTIME &st, TCHAR* disc)
{
	TCHAR szBuf[300];
	TCHAR szTime[50];
	TCHAR *szFullPath = makePath(disc, fd.cFileName);

	FileTimeToLocalFileTime(&fd.ftLastWriteTime, &fd.ftLastWriteTime);
	if (FileTimeToSystemTime(&fd.ftLastWriteTime, &st) == TRUE)
	{
		wsprintf(szTime, TEXT("%.2d.%.2d.%d    %.2d:%.2d"), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
	}

	wsprintf(szBuf, TEXT("%-100s%-50s%ld\n"), fd.cFileName, szTime, fd.nFileSizeLow);
	SendMessage(hList, LB_ADDSTRING, 0, LPARAM(szBuf));


}

void cFileFoldSearch::startSearching(WIN32_FIND_DATA &fd, SYSTEMTIME &st, TCHAR* disc, TCHAR* mask, bool flag)
{
	TCHAR path[255];
	wsprintf(path, TEXT("%s\\%s"), disc, mask);

	HANDLE hFind = FindFirstFile(path, &fd);
	do
	{
		if ((0 == lstrcmp(fd.cFileName, L".")) ||
			(0 == lstrcmp(fd.cFileName, L"..")))
		{
			continue;
		}
		if (hFind == INVALID_HANDLE_VALUE)
		{
			break;
		}
		else
		{
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				findFolder(fd, st, disc);
				if (flag)
				{
					wcscpy(newDisc, makeRecPath(disc, fd.cFileName));
					TCHAR newMask[255];
					wcscpy(newMask, mask);

					startSearching(fd, st, newDisc, newMask, flag);
				}
			}
			else
			{
				findFile(fd, st, disc);
				if (flag)
				{
					FindNextFile(hFind, &fd);
					wcscpy(newDisc, makeRecPath(disc, fd.cFileName));
					wcscpy(newMask, mask);

					startSearching(fd, st, newDisc, newMask, flag);

				}
			}
		}

	} while (FindNextFile(hFind, &fd));

	FindClose(hFind);
}

//void cFileFoldSearch::getPathforSearch()
//{
//	//int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
//}

//IDC_COMBDISC - get disc
//IDC_EFILE - get other info