#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WinPoc(
						HWND hwnd,
						UINT msg,
						WPARAM wParam,
						LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPreInstance,
				   LPSTR lcmdline,
				   int ncmdShow)
{
	WNDCLASS wndclass;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra =0;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL,IDC_CROSS);
	wndclass.hIcon = LoadIcon(NULL,IDI_ERROR);
	wndclass.hInstance=hInstance;
	wndclass.lpfnWndProc=WinPoc;
	wndclass.lpszClassName="KDF5000";
	wndclass.lpszMenuName=NULL;
	wndclass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndclass);
	//创建一个窗口，定义一个变量用来保存成功创建窗口后保存的句柄、

	HWND hwnd;
	hwnd = CreateWindow("KDF5000","http://www.kdf5000.com",
						WS_OVERLAPPEDWINDOW,0,0,600,400,
						NULL,NULL,hInstance,NULL);
	//显示及刷新窗口
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//窗口过程函数
LRESULT CALLBACK WinPoc(
						HWND hwnd,
						UINT msg,
						WPARAM wParam,
						LPARAM lParam)
{
	switch(msg)
	{
		case WM_CHAR:
		char szChar[20];
		sprintf(szChar,"char is %d",wParam);
		MessageBox(hwnd,szChar,"weixin",0);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd,"mouse clicked","weixin",0);
		HDC hdc;
		hdc=GetDC(hwnd);
		TextOut(hdc,0,50,"计算机编程语言培训",strlen("计算机编程语言培训"));
		ReleaseDC(hwnd,hdc);
		break;
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC=BeginPaint(hwnd,&ps);
		TextOut(hDC,0,0,"维新培训",strlen("维新培训"));
		EndPaint(hwnd,&ps);
		break;
	case WM_CLOSE:
		if(IDYES==MessageBox(hwnd,"是否真的结束？","weixin",MB_YESNO))
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}