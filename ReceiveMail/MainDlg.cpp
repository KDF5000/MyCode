#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"
#include <winsock2.h>
#include "pop3.h"


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
	CheckRadioButton(hwnd,IDC_ALLMAIL,IDC_SENDBOX,IDC_ALLMAIL);
	CheckRadioButton(hwnd,IDC_BOXNAME,IDC_ATTACHNAME,IDC_BOXNAME);
    return TRUE;
}
DWORD WINAPI test(LPVOID data)
{
	UserData *user = (UserData *)data;
	MessageBox(NULL,user->name,TEXT("1"),MB_OK);
	Sleep(5000);
	MessageBox(NULL,user->pass,TEXT("2"),MB_OK);
	return 0;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        case IDC_OK:
		{
			//存储进程ID
			unsigned int threadID;

			//返回进程句柄
			HANDLE hThread;

			//存放用户名的缓冲区 
			char username[30]; 

			//存放用户密码的缓冲区
			char password[30]; 

		    //存放用户信息的结构体
			UserData *user = (UserData*)malloc(sizeof(UserData));
            
			//获取用户的输入
	    	GetDlgItemText(hwnd,IDC_USERNAME,username,sizeof(username)/sizeof(char));
            GetDlgItemText(hwnd,IDC_PASSWORD,password,sizeof(password)/sizeof(char));
			
			//将结构体指向缓冲区数据
			int randRadio = GetCheckRadioButton(hwnd,IDC_ALLMAIL,IDC_SENDBOX);
			int methodRadio = GetCheckRadioButton(hwnd,IDC_BOXNAME,IDC_ATTACHNAME);

			lstrcpy(user->name,username);
			lstrcpy(user->pass,password);
			user->methodRadio = methodRadio;
			user->randRadio = randRadio;
            user->hwnd = hwnd;
		    //开辟一个新的进程
			hThread = CreateThread(NULL,0,receiveThread2,(LPVOID)user,0,0);
			//WaitForSingleObject(hThread,INFINITE);
			//CloseHandle(hThread);
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
//检查选中按钮
int GetCheckRadioButton(HWND hwnd,int firstradioID, int lastradioID)
{
	int i=0;
	for(i=firstradioID;i<=lastradioID;i++)
    {
          UINT uCheck=IsDlgButtonChecked(hwnd,i);
          if(BST_CHECKED==uCheck)
          {
            return i;
          }
     }
     return -1;
}