#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"

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
    switch(id)
    {
        case IDC_OK:
		{
			if(InitSock())
			{
				SOCKET httpsock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
				if (INVALID_SOCKET == httpsock)  
				{  
					WSACleanup();
					return 0;
				 } 
				if(!ConnectServer(&httpsock,"",110))
				{
					MessageBox(user->hwnd,TEXT("服务器连接失败！"),TEXT(""),MB_OK || MB_ICONWARNING);
					return 0;
				}
				ret = connectUserMail(httpsock,user->name,user->pass);
				if(ret)
				{
					
				}
			}
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