#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <io.h>
#include <errno.h>
#include <stdlib.h>
#include <errno.h>  
#include <commctrl.h>
#pragma comment(lib, "comctl32") 
#pragma  comment(lib,"ws2_32.lib")

bool InitSock() ;
//连接服务器
bool ConnectServer(SOCKET *socket,const char *domain,const int port);
//显示连接错误
void ShowError();
//连接到指定的邮箱
bool connectUserMail(SOCKET socket,char *username,char *password );
//判断返回信息是否有OK
bool IsOK(char * message);