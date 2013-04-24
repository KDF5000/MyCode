#include "StdAfx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"

#include "DrawShape.h"

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }

    return FALSE;
}


BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	HDC hdc;
	DataCir *dataCir = (DataCir *)malloc(sizeof(DataCir));
	DataRec *dataRec = (DataRec *)malloc(sizeof(DataRec));
    switch(id)
    {
        case IDC_OK:
		{
			hdc = GetDC(hwnd);
			dataCir->cdc = hdc;
			dataCir->x = 200;
			dataCir->y = 200;
			dataCir->R = 150;
			dataRec->hdc = hdc;
			dataRec->lx = 380;
			dataRec->ly = 50;
			dataRec->rx = 680;
			dataRec->ry = 350;
			CreateThread(NULL,0,DrawCir,(LPVOID)dataCir,0,0);
			CreateThread(NULL,0,DrawRec,(LPVOID)dataRec,0,0);
		}
        break;
        default:
		break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}