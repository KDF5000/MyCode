#include "SMTP.h"
#define MAXBUF 1024
char recvbuf[MAXBUF];
bool InitSock()  
{  
   WORD wVersionRequested;
   WSADATA wsaData;  
   int err;  
   wVersionRequested = MAKEWORD( 2, 2 );  
   
   err = WSAStartup( wVersionRequested, &wsaData );  
   if ( err != 0 ) 
   {        
      return false;  
   }     

   if ( LOBYTE( wsaData.wVersion ) != 2 ||   HIBYTE( wsaData.wVersion ) != 2 )
   {  
        WSACleanup();  
        return false;  
   }    
   return true;
}
//连接服务器
bool ConnectServer(SOCKET *socket,const char *domain,const int port)
{
	
	struct hostent *phost = gethostbyname(domain); 
	SOCKADDR_IN sock_addr = { 0 } ;  
	sock_addr.sin_family  = AF_INET ;  
	sock_addr.sin_port    = htons(port) ; 
	memcpy(&sock_addr.sin_addr.S_un.S_addr , phost->h_addr_list[0] , phost->h_length );  

	int res = connect(*socket , (sockaddr *)&sock_addr , sizeof(sockaddr));  
	if (res == SOCKET_ERROR)  
	{  
		 ShowError();
    	 return false; 
	} 
	recv(*socket, recvbuf , MAXBUF , 0);  
	//MessageBox(hwnd,recvbuf,TEXT("contect"),MB_OK);
	return true;
}

//显示连接错误
void ShowError()
{
	TCHAR* lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER| //自动分配消息缓冲区
	FORMAT_MESSAGE_FROM_SYSTEM, //从系统获取信息
	NULL,GetLastError(), //获取错误信息标识
	MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//使用系统缺省语言
	(LPTSTR)&lpMsgBuf, //消息缓冲区
	0, NULL);
	MessageBox(NULL,lpMsgBuf,"",MB_ICONERROR);
}
//连接到指定的邮箱
bool connectUserMail(SOCKET socket,char *username,char *password )
{
	char nameStr[30] ={0};       //用户名  
    char passStr[30] = {0};      //密码
	char ret[MAXBUF];
	wsprintf(nameStr,"USER %s\t\n",username);
	wsprintf(passStr,"PASS %s\t\n",password);

	 //连接指定邮箱
	send( socket, nameStr , strlen(nameStr) , 0 ) ;  //--------------------------NAME  
	recv(socket, recvbuf , MAXBUF , 0);  
    sprintf(ret,"%s",recvbuf);
	if(!IsOK(ret))
	{
		return false;
	}
	memset(recvbuf , 0 ,MAXBUF);  
    
	send( socket , passStr , strlen(passStr) , 0 ) ; //----------------------------PASSWORD  
	recv(socket, recvbuf , MAXBUF , 0);  
	sprintf(ret,"%s",recvbuf);
	if(!IsOK(ret))
	{
		return false;
	}
	memset(recvbuf , 0 ,MAXBUF);
    return true;	
}
//判断返回信息是否有OK
bool IsOK(char * message)
{
    if (tolower(message[1])=='o' && tolower(message[2])=='k' )
        return 1;
    else
        return 0;
}
