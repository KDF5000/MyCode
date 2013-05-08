#include "pop3.h"
#include "stdafx.h"
#include "BaseDecode.h"

#include <winsock2.h>
#define MAXBUF 4096
//用于保存从服务器返回的数据
char recvbuf[MAXBUF];
//用来控制进度条的进度
int statues;
char *monthT[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char *weekdayT[7]={"Sun","Mon","Tue","Web","Thu","Fri","Sat"};
//初始化sock
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
   statues++;
   return true;
}
//连接服务器
bool ConnectServer(SOCKET *socket,const char *domain,const int port)
{
	
	struct hostent *phost = gethostbyname(domain); 
	//创建一根电线 
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
	//MessageBox(hwnd,ret,TEXT("name"),MB_OK);
	if(!IsOK(ret))
	{
		return false;
	}
	//MessageBox(hwnd,recvbuf,TEXT("name"),MB_OK);
	memset(recvbuf , 0 ,MAXBUF);  
    
	send( socket , passStr , strlen(passStr) , 0 ) ; //----------------------------PASSWORD  
	recv(socket, recvbuf , MAXBUF , 0);  
	sprintf(ret,"%s",recvbuf);
	if(!IsOK(ret))
	{
		return false;
	}
	//MessageBox(hwnd,recvbuf,TEXT("pass"),MB_OK);
	memset(recvbuf , 0 ,MAXBUF);
    return true;	
}


//获取邮件的数目(未完成)
int GetMailNumber(SOCKET socket)
{
	
	char number[5];
	int i=0;
	send( socket , "STAT\t\n" , strlen("STAT\r\n") , 0 ) ;  
	recv(socket,recvbuf , MAXBUF , 0);  
	char *p= strstr(recvbuf,"+OK ");
	if ( p == NULL )
		return 0;
	p=p+4;
	for(i=0;i<5;i++)
	{
		if( p[i] == '\r' || p[i] == '\n' || p[i] ==' ')
		{
			number[i]='\0';
			break;
		}
		number[i]=p[i];	
	}
	//循环总是会死 不知道什么原因
    /*while(p[i] != '\r' || p[i] != '\n' || p[i] !=' ')
	{
		number[i]=p[i];	
		i++;
	}*/
	number[i]='\0';
	//MessageBox(hwnd,number,TEXT("number"),MB_OK);
	memset(recvbuf , 0 ,MAXBUF);  
	return atoi(number);
}

//获取指定邮件的文本,返回保存到文件名
char * Getmail(int index,SOCKET socket,char *path)
{
	char ret[MAXBUF];
	char *p;
	char retr[30];
	int i,j;
	char filepath[30];
	wsprintf(filepath,"%s\\%d.txt",path,index);
	memset(recvbuf , 0 ,MAXBUF); 
	wsprintf(retr,"RETR %d\t\n",index);
	send( socket ,retr , strlen(retr) , 0 ) ; 
	recv(socket , recvbuf , MAXBUF , 0);  
	memset(recvbuf , 0 ,MAXBUF); 
	
	while(strstr((ret+strlen(ret)-3),".")==	NULL)
	{
		recv(socket , recvbuf , MAXBUF , 0); 
		sprintf(ret,"%s",recvbuf);

		if(!saveTofile(ret,filepath))
			return NULL;
        memset(recvbuf , 0 ,MAXBUF);
	}
	memset(recvbuf , 0 ,MAXBUF); 
	return filepath;
}
//获取所有邮件并进行保存
bool GetAllmail(HWND hwnd,SOCKET socket , char *filePath , int numbers)
{
    int index;
	char path[30];
	char retr[30];

    for (index=1;index<=numbers;index++)
	{
		statues++;
		if(!Getmail(index,socket,filePath))
			return false;
		SendDlgItemMessage(hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
	}
	return true;

}
//退出，断开与服务器的连接

void Quit(SOCKET socket)
{
	char quit[MAXBUF] ="QUIT\t\n";
	memset(recvbuf , 0 ,MAXBUF); 
    send( socket ,quit, strlen(quit) , 0 ) ; 
	recv(socket , recvbuf , MAXBUF , 0);  
	return ;
}
//判断返回信息是否有OK
bool IsOK(char * message)
{
    if (tolower(message[1])=='o'&&tolower(message[2])=='k' )
        return 1;
    else
        return 0;
}

//保存文件
bool saveTofile(char *str,char *filename)
{
	FILE *fp = fopen(filename,"a+");
	if(fp!=NULL)
	{
		fwrite(str,strlen(str),1,fp);
 	    fclose(fp);
		return true;
	}
	return false;
}

//用creatthread创建线程
DWORD WINAPI receiveThread2(LPVOID data)
{	
	bool ret ;
	statues=0;
	UserData *user=(UserData*)data;
	if(InitSock())
	{
		SOCKET httpsock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
		if (INVALID_SOCKET == httpsock)  
		{  
			WSACleanup( );
			return 0;
		 } 
		if(!ConnectServer(&httpsock,"pop.163.com",110))
		{
			MessageBox(user->hwnd,TEXT("服务器连接失败！"),TEXT(""),MB_OK || MB_ICONWARNING);
			return 0;
		}
		ret = connectUserMail(httpsock,user->name,user->pass);
		if(ret)
		{
			int i;
			char tempPath[] = "TEMP";
			char mailPath[] ="reveiveMail";
			//int numbers = GetMailNumber(httpsock);
			int numbers = 2;
			
			SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETRANGE,0,MAKELPARAM(0,2*numbers+5));
			statues =5;
			SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
			int allMailFlag = 0;  //判断所有邮件都保存的信号
			int mailIDsFlag = 0; //判断是匹配特定主题或者时间的信号
			char info[MAXBUF];
			int mailID=0;
			char *p;
			char sub[200];

			char dateL[15];
			char dateR[15];
			int year=0;
			int month=0;
			int day =0;
			int *mailIDs=NULL;
			dateTime *dateLP = (dateTime *)malloc(sizeof(dateTime));
			dateTime *dateRP = (dateTime *)malloc(sizeof(dateTime));
			memset(dateL,0,sizeof(dateL));
			memset(dateR,0,sizeof(dateR));
			
			char boxName[30];
			memset(boxName,0,sizeof(boxName));
			//根据选项保存接收收邮件
			switch(user->randRadio)
			{
			  case IDC_ALLMAIL:
					//获取所有邮件保存在temp里
				  //保存玩这个邮件，速度可能比较慢
				  saveAllMail(httpsock,tempPath,user->hwnd,numbers);
				  //知识保存邮件的信息头部
				  //saveAllMailHeadInfo(httpsock,makeDir(tempPath),user->hwnd,numbers);
				  allMailFlag = 1;
				  break;
			  case IDC_DATERANGE:
				    //获取指定日期范围内的邮件
				  GetDlgItemText(user->hwnd,IDC_DATETIMEPICKERL,dateL,sizeof(dateL));
				  GetDlgItemText(user->hwnd,IDC_DATETIMEPICKERR,dateR,sizeof(dateR));

				  sscanf(dateL,"%d/%d/%d",&year,&month,&day);
				  dateLP->year = year;
				  dateLP->month = month;
				  dateLP->day = day;

				  sscanf(dateR,"%d/%d/%d",&year,&month,&day);
				  dateRP->year = year;
				  dateRP->month = month;
				  dateRP->day = day;

				  mailIDs = saveByDate(dateLP,dateRP,httpsock,makeDir(tempPath) ,numbers);
				  mailIDsFlag = 1;
				  break;
			  case IDC_MAILSUBJECT:
				    //获取指定邮件主题的邮件
				  GetDlgItemText(user->hwnd,IDC_SUB,sub,sizeof(sub));
				 // MessageBox(user->hwnd,sub,TEXT(""),MB_OK);
				  mailID = saveMailBySub(sub,httpsock,makeDir(tempPath));
				  if(mailID==-1)
					  MessageBox(user->hwnd,TEXT("对不起没有找到该主题的邮件!"),TEXT(""),MB_OK);
				  break;
			  case IDC_SENDBOX:
				    //获取指定邮箱的邮件
					//保存指定邮箱的所有邮件
				  GetDlgItemText(user->hwnd,IDC_MAILBOX,boxName,sizeof(boxName));
                  mailIDs = saveBymailBox(boxName,httpsock,makeDir(tempPath),numbers);
				  mailIDsFlag = 1;
				  break;
			  default :
				  break;
			}
			//按照指定方式将接收到的邮件进行处理
			switch(user->methodRadio)
			{
				case IDC_BOXNAME:
				    //按照邮箱名和日期保存
					if(allMailFlag==1)
					  moveAllMailBD(tempPath,mailPath,numbers,user->hwnd );

				    if(mailID!=-1 && mailID !=0)
					{
						moveMailBD(tempPath,mailPath,mailID,user->hwnd );
						statues = numbers +5;
						SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
					}

					if(mailIDsFlag !=0)
					{
						if(mailIDs==NULL)
						{
							break;  
						}
						for(i=1;i<=numbers;i++)
						{
							if(mailIDs[i]==1)
								moveMailBD(tempPath,mailPath,i,user->hwnd);
							statues++;
							SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
						}
					}
					break;	
				case IDC_SUBJECT:
					 //按照主题和日期保存
					if(allMailFlag==1)
					  ExtractMailSD(tempPath,mailPath,numbers,user->hwnd );
					if(mailID!=-1 && mailID !=0)
					{
						moveMailSD(tempPath,mailPath,mailID,user->hwnd );
						statues = numbers +5;
						SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
					}
					if(mailIDsFlag !=0)
					{
						if(mailIDs==NULL)
							break;
						for(i=1;i<=numbers;i++)
						{
							if(mailIDs[i]==1)
								moveMailSD(tempPath,mailPath,i,user->hwnd);
							statues++;
							SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
						}
					}
					break;
				case IDC_ATTACHNAME:
					//按照第一个附件名和日期保存
					if(allMailFlag==1)
					  moveAllMailAD(tempPath,mailPath,numbers,user->hwnd );
					if(mailID!=-1 && mailID !=0)
					{
						moveMailAD(tempPath,mailPath,mailID,user->hwnd);
						statues = numbers +5;
						SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
					}
					if(mailIDsFlag !=0)
					{
						if(mailIDs==NULL)
							break;
						for(i=1;i<=numbers;i++)
						{
							if(mailIDs[i]==1)
								moveMailAD(tempPath,mailPath,i,user->hwnd);
							statues++;
							SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
						}
					}
					break;
				default:
					break;
			}
			statues = 2*numbers+5;
			SendDlgItemMessage(user->hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
			Sleep(2000);
			MessageBox(user->hwnd,TEXT("操作成功"),TEXT(""),MB_OK );
			Quit(httpsock);
			return 1;

		}
		else
		{
			MessageBox(user->hwnd,TEXT("用户登录失败"),TEXT(""),MB_OK || MB_ICONWARNING);
			Quit(httpsock);
			return 0;
		}
	}
	MessageBox(user->hwnd,TEXT("对不起，初始化失败，稍后重试"),TEXT(""),MB_OK || MB_ICONWARNING);
	return 0;
}

//获取主题从保存的邮件中
char * extractSubject(char *filename)
{
	FILE *fp;
	char temp[100];
	char sub[100];
	char Nsub[] = "unkown_subjext";
	char *p,*pB,*pQ;
	int i;
	fp = fopen(filename,"r");
	if(fp!=NULL)
	{
		while(fgets(temp,sizeof(temp),fp))
		{
			
			if(strstr(temp,"Subject: "))
			{
				pB = strstr(temp,"?B?");
				pQ = strstr(temp,"?Q?");
				if(pB!=NULL)
				    p = pB;
				if(pQ!=NULL)
					p = pQ;
				if(pB!=NULL||pQ!=NULL)
				{
					p = p+3;
					i=0;
					while(*(p+i)!='?')
					{
						sub[i]=*(p+i);
						i++;
					}
					sub[i]='\0';
				}
				else
				{
					fclose(fp);
					i=9;
					while(temp[i]!='\0')
					{
						if(temp[i]==' '||temp[i]==','||temp[i]=='\n')
							temp[i]='_';
						i++;
					}
					return (temp+9);
				}
				fclose(fp);
				if(pB!=NULL)
				   return (base64_decode(sub,strlen(sub)));
				return sub;
			}
			memset(temp,0,sizeof(temp));
		}
		fclose(fp);
	}
	return ("unkown_subjext");
}

//从邮件信息头中获取主题
char * getsubjectFromHeader(int number ,SOCKET httpsock)
{
	
	char info[MAXBUF];
	char sub[100]; //用于保存主题
	char temp[200];
	char *p,*pQ,*pB;
	int i;
	memset(sub,0,sizeof(sub));
	memset(info,0,sizeof(info));
    memset(temp,0,sizeof(temp));
	sprintf(info,"%s",getMailInfo(number,httpsock));
    p = strstr(info,"Subject: ");
	if(p!=NULL)
	{
		//MessageBox(NULL,TEXT("找到Subject: "),TEXT(""),MB_OK);
		p=p+9;;
		while(*p=='\n'||*p=='\r')
		{
			p++;
		}
	    i=0;
		while(*(p+i)!='\n'&& *(p+i)!='\r')
		{
		  temp[i]=*(p+i);
		  i++;
		}
		temp[i]='\0';
		p=pB=pQ=NULL;
		pB = strstr(temp,"?B?");
		pQ = strstr(temp,"?Q?");
		if(pB!=NULL)
			p = pB;
		if(pQ!=NULL)
			p = pQ;
		if(p!=NULL)
		{
			p = p+3;
			while(*p=='\n'||*p=='\r')
			{
		    	p++;
			}
			i=0;
			while(*(p+i)!='?')
			{
				sub[i]=*(p+i);
				i++;
			}
			sub[i]='\0';
			/*if(pB!=NULL)
			   MessageBox(NULL,base64_decode(sub,strlen(sub)),TEXT(""),MB_OK);
			else
				MessageBox(NULL,sub,TEXT(""),MB_OK);*/
			//MessageBox(NULL,sub,TEXT(""),MB_OK);
			if(pB!=NULL)
			  return (base64_decode(sub,strlen(sub)));
			return sub;
		}
		else
		{		
			p = strstr(info,"Subject: ");
			p=p+9;
			while(*p=='\n'||*p=='\r')
			{
		    	p++;
			}
			i=0;
			while(*(p+i)!='\n'&& *(p+i)!='\r')
			{
			  sub[i]=*(p+i);
			  i++;
			}
			sub[i]='\0';
			//MessageBox(NULL,sub,TEXT(""),MB_OK);
			return sub;
		}	
	}
	char noSub[] = "NO_SUB";
	return noSub;

}
//获取邮件日期从保存的邮件中
//处理Mon, 8 Apr 2013 08:27:39 +0800格式
char * getMailData(char *filename)
{
	FILE *fp = fopen(filename , "r");
	char temp[100];
	char dateStr[100];
	char noDate[] = "NO_DATE";
	if(fp!=NULL)
	{
		while(fgets(temp,sizeof(temp),fp))
		{
			
			if(strstr(temp,"Date: "))
			{
				strcpy(dateStr,temp+6);
			    /*int i=0;
				//去除空格，：等
				while(dateStr[i]!='\0')
				{
					if(dateStr[i]==' '||dateStr[i]==','||dateStr[i]==':'||dateStr[i]=='+')
						dateStr[i]='_';
					i++;
				}*/

				fclose(fp);
				return dateStr;
			}
			memset(temp,0,sizeof(temp));
		}
		fclose(fp);
	}
	return noDate;
}

//从邮件头信息中获取日期
char * getDateFromHeader(int number ,SOCKET httpsocket)
{
	char info[MAXBUF];
	char sub[50]; //用于保存主题
	char noDate[] = "NO_DATE";
	char *p;
	int i;
	sprintf(info,"%s",getMailInfo(number,httpsocket));
    p = strstr(info,"Date: ");
	if(p!=NULL)
	{
		//MessageBox(NULL,TEXT("找到date: "),TEXT(""),MB_OK);
		i=0;
		p = p+6;
		while(*p=='\n'||*p=='\r')
		{
			p++;
		}
		while(*(p+i)!='\n'&& *(p+i)!='\r')
		{
		  sub[i]=*(p+i);
		  i++;
		}
		sub[i]='\0';
		//MessageBox(NULL,sub,TEXT(""),MB_OK);
		return sub;
	}
	return noDate;
}
//从信息头部获取发件人信息
char * getSenderFromHeader(int number ,SOCKET httpsock)
{
	char info[MAXBUF];
	char sub[50]; //用于保存发件人名字
	char mailName[30];//用于保存发件邮箱
	char temp[100];
	memset(temp,0,sizeof(temp));
	memset(info,0,sizeof(info));
	memset(sub,0,sizeof(sub));
	memset(mailName,0,sizeof(mailName));
	char *p,*pQ,*pB;
	int i;
	sprintf(info,"%s",getMailInfo(number,httpsock));
    p = strstr(info,"From: ");
	if(p!=NULL)
	{
		//MessageBox(NULL,TEXT("找到From: "),TEXT(""),MB_OK);
		i=0;
		p = p+6;
		while(*p=='\n'||*p=='\r')
		{
			p++;
		}
		//存放from一行的内容
		while(*(p+i)!='>')
		{
		  temp[i]=*(p+i);
		  i++;
		}
		temp[i]=*(p+i);
		i++;
		temp[i]='\0';
		
		//匹配用base64加密过的发件人姓名
		p=NULL;
		pB = strstr(temp,"?B?");
		pQ = strstr(temp,"?Q?");
		if(pB!=NULL)
			p = pB;
		if(pQ!=NULL)
			p = pQ;
		if(p!=NULL)
		{
			p = p+3;
			while(*p=='\n'||*p=='\r')
			{
			  p++;
			}
			i=0;
			while(*(p+i)!='?')
			{
				sub[i]=*(p+i);
				i++;
			}
			sub[i]='\0';

			//匹配发件邮箱名
			p = NULL;
			p = strstr(temp,"<");
			if(p!=NULL)
			{
				i=0;
				while(*(p+i)!='\0')
				{
					mailName[i] = *(p+i);
					i++;
				}
				mailName[i] = '\0';
			}

			//先清楚temp缓冲区的内容，然后将发件人名字与发件箱名字合并
			memset(temp,0,sizeof(temp));
			//将解码后的发件人姓名复制到temp缓冲区
			if(pB!=NULL)
			    strcpy(temp,base64_decode(sub,strlen(sub)));
			else
				strcpy(temp,sub);  //用Q...解码
			//将发件人姓名与发件邮箱连接
			strcat(temp,mailName);
		   // MessageBox(NULL,temp,TEXT(""),MB_OK);
			return temp;
		}
		else
		{
			i=0;
			p = strstr(info,"From: ");
			p = p+9;
			while(*(p+i)!='\n'&& *(p+i)!='\r')
			{
			  sub[i]=*(p+i);
			  i++;
			}
			sub[i]='\0';
			//MessageBox(NULL,sub,TEXT(""),MB_OK);
			return sub;
		}	
	}
	char noSender[] = "无发件人信息";
	return noSender;

}
//获取发件箱名字，从文件中
char *getsendmailBox(char *filename)
{
	FILE *fp = fopen(filename , "r");
	char temp[200];
	char box[200];
	char *p,*pQ,*pB;
	p = pB = pQ=NULL;
	int i;
	memset(temp,0,sizeof(temp));
	memset(box,0,sizeof(box));

	if(fp!=NULL)
	{
		while(fgets(temp,sizeof(temp),fp))
		{
			if(strstr(temp,"From: "))
			{
				p = strstr(temp,"<");
				if(p!=NULL)
				{
					i=0;
					p++;
					while(*(p+i) !='>' && *(p+i) != '\0')
					{
						box[i]=*(p+i);
						i++;
					}
					box[i]= '\0';
					fclose(fp);
					return 	disSpace(box);
				}
				else
				{
					return ("no_box_info");
				}
			}
			memset(temp,0,sizeof(temp));
		}
		fclose(fp);
	}
	char noBox[] = "NO_BOX";
	return noBox;
}
//获取第一个附件名字
char * getAttachName(char *filename)
{
	
	FILE *fp = fopen(filename , "r");
	char temp[200];
	char att[200];
	char noAtt[] = "无附件";
	char *p,*pQ,*pB;
	p = pB = pQ=NULL;
	int i;
	memset(temp,0,sizeof(temp));
	memset(att,0,sizeof(att));
	if(fp!=NULL)
	{
		while(fgets(temp,sizeof(temp),fp))
		{
			if(strstr(temp,"attachment"))
			{
				pB = strstr(temp,"?B?");
				pQ = strstr(temp,"?Q?");
				if(pB!=NULL)
				{
					p=pB;
				}
				if(pQ!=NULL)
				{
					p=pQ;
				}
				if(p!=NULL)
				{
					p= p +3;
					i=0;
					while(*(p+i) !='?')
					{
						att[i]=*(p+i);
						i++;
					}
					att[i]= '\0';
					fclose(fp);
					return (base64_decode(att,strlen(att)));
				}
				else
				{
					p = strstr(temp,"filename");
					if(p!=NULL)	
					{
						p= p +10;
						i=0;
						while(*(p+i)!='\"')
						{
							att[i]=*(p+i);
							i++;
						}
						att[i]='\0';
						fclose(fp);
						return att;
					}
				}
			}
			memset(temp,0,sizeof(temp));
		}
		fclose(fp);
	}
	return noAtt;
}

/*************************************
*dirName:要创建的目录名字，不能有空格
*功能：创建一个指定名字的目录
***************************************/
char * makeDir(char *dirName)
{
	char cmd[200];
	if(access(dirName,0))//判断目录是否存在
    {
        sprintf(cmd,"cmd.exe /C md %s",dirName);
        ///system(cmd);
		WinExec(cmd,SW_HIDE);
		return dirName;
    }
    else
    {
        return dirName;
    }
}
/*****************************************
*去除空格用_代替
*disSpace(char string[])
******************************************/
char * disSpace(char string[])
{
	int i=0;
	while(string[i]!='\0')
	{
		if(string[i]==' '||string[i]==','||string[i]==':'||string[i]=='+' ||string[i]=='\r'||string[i]=='\n')
			string[i]='_';
		i++;
	}
	return string;
}

/**************************************************************
*功能：按照指定方式保存邮件
*时间：2013.4.8
***************************************************************/

void saveAllMail(SOCKET httpsock,char *filepath,HWND hwnd , int numbers)
{
	if(numbers<=0)
	{
		MessageBox(hwnd,TEXT("您的邮箱中没有邮件"),TEXT("警告"),MB_OK || MB_ICONWARNING);
		return ;
	}
	if(!GetAllmail(hwnd,httpsock,makeDir(filepath),numbers))
		MessageBox(hwnd,TEXT("保存邮件失败!"),TEXT("SAVEFAIL"),MB_OK || MB_ICONWARNING);
	return;
}


//保存所有邮件的信息头
void saveAllMailHeadInfo(SOCKET httpsock,char *savepath,HWND hwnd , int numbers)
{	
	if(numbers<=0)
	{
		MessageBox(hwnd,TEXT("您的邮箱中没有邮件"),TEXT("警告"),MB_OK || MB_ICONWARNING);
		return ;
	}
	int i;
	char filepath[100];
	char temp[MAXBUF];
	char test[]="test";
	for(i=1;i<=numbers;i++)
	{
		sprintf(temp,"%s",getMailInfo(i,httpsock));
		wsprintf(filepath,"%s\\%d.txt",savepath,i);
		if(!saveTofile(temp,filepath))
		{
			MessageBox(hwnd,TEXT("保存文件失败"),TEXT(""),MB_OK);
			return ;
		}
	}
	return;
}

//获取邮件信息头(未用)
char * getMailInfo(int mailID,SOCKET socket)
{
	  char order[30];
	  char temp[MAXBUF];
	  sprintf(order,"TOP %d %d\t\n",mailID,0);
	  send(socket,order,strlen(order),0);
	  recv(socket,temp,strlen(temp),0);
	  memset(temp,0,sizeof(temp));
	  recv(socket , temp , MAXBUF , 0);  
	  return temp;
}


//从临时文件中提取相关内容并保存
void ExtractMailSD(char *tempPath,char *mailPath,int numbers,HWND hwnd )
{
		int i;
		char maildir[100];
		char filepath[100];
		char subject[200];

		char date[50];
		for(i=1;i<=numbers;i++)
		{
			sprintf(filepath,"%s\\%d.txt",tempPath,i);
			
			strcpy(subject,extractSubject(filepath));
			strcpy(date , getMailData(filepath));
			if(subject!=NULL)
			{
				//strcpy(subject,disSpace(subject));
				disSpace(subject);
			}
			if(date!=NULL)
			{
				//strcpy(date,disSpace(date));
				disSpace(date);
			}
			sprintf(maildir,"%s\\%s_%s",mailPath,subject,date);
			makeDir(maildir);
			
			cutFile(filepath,maildir);
	
			memset(maildir,0,sizeof(maildir));
			sprintf(maildir,"%s_%s",subject,date);
			//总是失败
			//decodeMail(filepath,mailPath,maildir,i);
		//	remove(filepath);
			statues ++;
			SendDlgItemMessage(hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
		}
		return ;
}

//剪切一个文件到指定目录
bool cutFile(char *sourcePath ,char *aimPath)
{
	char cmd[200];
	if(access(sourcePath,0)!=-1)//判断目录是否存在
    {
        wsprintf(cmd,"copy  %s %s",sourcePath,aimPath);
        system(cmd);
		//WinExec(cmd,SW_HIDE);
		remove(sourcePath);
		return true;
    }
    else
    {
        return false;
    }
}

/*****************************************************
*功能：保存指定主题的邮件
******************************************************/
int saveMailBySub(char *subject,SOCKET httpsock,char *path)
{
	int numbers = GetMailNumber(httpsock);
	int i;
	char sub[200];
	strcpy(sub,subject);
	char temp[200]; //用于存放信息头接收到的邮件主题
	for(i=1;i<=numbers;i++)
	{
		memset(temp,0,sizeof(temp));
		strcpy(temp,getsubjectFromHeader(i,httpsock));
		if(strcmp(temp,sub)==0)
		{
			Getmail(i,httpsock,path);
			statues = numbers+5;
		    SendDlgItemMessage(NULL,IDC_PROGRESS1,PBM_SETPOS,statues,0);
			return i;
		}
		statues++;
		SendDlgItemMessage(NULL,IDC_PROGRESS1,PBM_SETPOS,statues,0);
	}
	return -1;
}

/***********************************************************
*功能：moveMailSD()移动邮件到指定文件夹
************************************************************/
void moveMailSD(char *tempPath,char *mailPath,int mailID,HWND hwnd )
{
	int i;
	char maildir[100];
	char filepath[100];

	wsprintf(filepath,"%s\\%d.txt",tempPath,mailID);
	char *subject = extractSubject(filepath);
	char *date =  getMailData(filepath);
	char aimFile[50];
    //创建一个目录
	disSpace(subject);
	disSpace(date);
	wsprintf(maildir,"%s\\%s_%s",mailPath,subject,date);
	makeDir(maildir);
	//剪切文件至目标文件夹
	cutFile(filepath,maildir);
	memset(maildir,0,sizeof(maildir));
    sprintf(maildir,"%s_%s",subject,date);
	//总是失败
	//decodeMail(filepath,mailPath,maildir,mailID);
//	remove(filepath);
	return ;
}

//将临时邮件按照附件名和日期名转移
void moveMailAD(char *tempPath,char *mailPath,int mailID , HWND hwnd)
{
	int i;
	char maildir[200];
	char filepath[100];
	char attachment[200];
	char date[50];
	char aimFile[50];

	memset(attachment,0,sizeof(attachment));
	memset(date,0,sizeof(date));
	memset(maildir,0,sizeof(maildir));
	memset(filepath,0,sizeof(filepath));
	memset(aimFile,0,sizeof(aimFile));

	wsprintf(filepath,"%s\\%d.txt",tempPath,mailID);
	//strcpy(attachment, getAttachName(filepath) );
	sprintf(attachment,"%s",getAttachName(filepath));
	sprintf(date,"%s",getMailData(filepath));
	//strcpy(date, getMailData(filepath) );

	if(date!=NULL)
	{
		disSpace(date);
	}
	
	if(attachment!=NULL)
	{
		disSpace(attachment);
	}

    //创建一个目录
	wsprintf(maildir,"%s\\%s_%s",mailPath,attachment,date);
	makeDir(maildir);
	//剪切文件至目标文件夹
	cutFile(filepath,maildir);
	memset(maildir,0,sizeof(maildir));
    sprintf(maildir,"%s_%s",attachment,date);
	//总是失败
	//decodeMail(filepath,mailPath,maildir,mailID);
	//remove(filepath);
	return ;
}
//将所有邮件移动到指定文件夹按照附件名和日期名转移
void moveAllMailAD(char *tempPath,char *mailPath,int numbers,HWND hwnd )
{
    int i;
	for(i=1;i<=numbers;i++)
	{
		moveMailAD(tempPath,mailPath,i,hwnd);
		statues++;
		SendDlgItemMessage(hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
	}
	return ;
}

//将所有邮件移动到指定文件夹按照发件箱和日期名转移hwnd测试时使用
void moveMailBD(char *tempPath,char *mailPath,int mailID,HWND hwnd )
{
	char maildir[100];
	char filepath[100];
	char mailbox[50];
	char date[50];

	
	memset(maildir,0,sizeof(maildir));
	memset(filepath,0,sizeof(filepath));
	memset(mailbox,0,sizeof(mailbox));
	memset(date,0,sizeof(date));

	wsprintf(filepath,"%s\\%d.txt",tempPath,mailID);
	//strcpy(mailbox,getsendmailBox(filepath));
	sprintf(mailbox,"%s",getsendmailBox(filepath));
	sprintf(date,"%s",getMailData(filepath));
	//strcpy(date,getMailData(filepath));

	if(date!=NULL)
	{
		//strcpy(date,disSpace(date));
		disSpace(date);
	}
	
	if(mailbox!=NULL)
	{
		//strcpy(mailbox,disSpace(mailbox));
		disSpace(mailbox);
	}


    //创建一个目录
	wsprintf(maildir,"%s\\%s_%s",mailPath,mailbox,date);
	makeDir(maildir);
	//剪切文件至目标文件夹
	//cutFile(filepath,maildir);
	memset(maildir,0,sizeof(maildir));
	sprintf(maildir,"%s_%s",mailbox,date);
	//总是失败*
	decodeMail(filepath,mailPath,maildir,mailID);
	//remove(filepath);
	return ;
}

//将所有邮件移动到指定文件夹按照发件箱和日期名转移hwnd测试时使用
void moveAllMailBD(char *tempPath,char *mailPath,int numbers,HWND hwnd )
{
    int i;
	for(i=1;i<=numbers;i++)
	{
		moveMailBD(tempPath,mailPath,i,hwnd);
		statues++;
		SendDlgItemMessage(hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
	}
	return ;
}

//比较两个dateTime结构体日期的大小
int comparDate(dateTime *date1, dateTime *date2)
{
	if(date1->year >= date2->year && date1->month >= date2->month && date1->day >= date2->day)
	{
		if(date1->year == date1->year && date1->month == date2->month && date1->day== date2->day)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return -1;
	}
}
//比较日期保存邮件
int * saveByDate(dateTime *dateL,dateTime *dateR,SOCKET httpsock,char *path ,int numbers)
{
	int i,j;
	char weekday[10]= {0};
	int year=0;
	char month[3]={0};
	int day=0;
	int hour=0;
	int minute=0;
	int second=0;
    int mon=0;
	char time[50];
    int *mailIDs = (int *)malloc(sizeof(int)*(numbers+1));
	for(i=0;i<=numbers;i++)
	{
		mailIDs[i] = 0;
	}
	dateTime *maildate = (dateTime *)malloc(sizeof(dateTime));
	for(i=1;i<=numbers;i++)
	{
		memset(time,0,sizeof(time));
		strcpy(time,getDateFromHeader(i,httpsock));
		//MessageBox(NULL,time,TEXT(""),MB_OK);
		sscanf(time,"%s%d%s%d%d:%d:%d",
		        weekday,&day,month,&year,&hour,&minute,&second);
	    //查表找到月份
		for(j=0;j<12;j++)
		{
			if(strstr(month,monthT[j]))
			{
				mon = j+1;
				break;
			}
		}
		
		maildate->year = year;
		maildate->month = mon;
		maildate->day = day;

		
		if(comparDate(maildate,dateL)>=0 && comparDate(maildate,dateR)<=0)
		{
			Getmail(i,httpsock,path);
			mailIDs[i] = 1;
		}
		statues++;
		SendDlgItemMessage(NULL,IDC_PROGRESS1,PBM_SETPOS,statues,0);
	}
	return mailIDs;
}

//保存指定邮箱的所有邮件
int * saveBymailBox(char *boxName,SOCKET httpsock,char *path ,int numbers)
{
	int i;
	int getAmount=0;
	int *mailIDs = (int *)malloc(sizeof(int)*(numbers+1));
	for(i=0;i<=numbers;i++)
	{
		mailIDs[i] = 0;
	}
	char mailBox[30];
	strcpy(mailBox,boxName);
	char temp[200]; //用于存放信息头接收到的邮件主题
	for(i=1;i<=numbers;i++)
	{
		memset(temp,0,sizeof(temp));
		strcpy(temp,getSenderFromHeader(i,httpsock));
		if(strstr(temp,mailBox))
		{
			Getmail(i,httpsock,path);
			mailIDs[i]=1;
			getAmount++;
		}
		statues++;
		SendDlgItemMessage(NULL,IDC_PROGRESS1,PBM_SETPOS,statues,0);
	}
	if(getAmount==0)
	  return NULL;
	return mailIDs;
}

//MIME内容提取
//将指定未解码的文件解码并保存到指定文件夹

bool decodeMail(char *filePath, char *mailPath,char *maildir,int mailID)
{
	char filename[100];
	char sub[200];
	char subtemp[200]; //用主题下信息于将从文件中提取的
	char sender[50];
	char senderTemp[50];
	char date[50];
	char dateTemp[50];
	char temp[100];

	memset(filename,0,sizeof(filename));
	memset(sub,0,sizeof(sub));
	memset(subtemp,0,sizeof(subtemp));
	memset(sender,0,sizeof(sender));
	memset(date,0,sizeof(date));
	memset(dateTemp,0,sizeof(dateTemp));
	memset(temp,0,sizeof(temp));

	
	FILE *fpR = NULL;
	FILE *fpW = NULL;

	int i=0;
	while(maildir[i]!='\0')
	{
		if(maildir[i]=='\r'||maildir[i]=='\n')
		{
			maildir[i]='\0';
		}
		i++;
	}
	sprintf(filename,"%s\\%s\\%d.txt\0",mailPath,maildir,mailID);

//	MessageBox(NULL,filePath,TEXT(""),MB_OK);
//	MessageBox(NULL,filename,TEXT(""),MB_OK);

	fpR = fopen(filePath,"r");
	fpW = fopen(filename,"a+");
	
	if(fpW!=NULL && fpR!=NULL)
	{
		/*strcpy(subtemp,extractSubject(filePath));
		//strcpy(dateTemp,getMailData(filePath));
		//strcpy(senderTemp,getsendmailBox(filePath));

        wsprintf(sub,"主题：%s\n",subtemp);
		wsprintf(date,"日期：%s",getMailData(filePath));
		wsprintf(sender,"发件人:%s\n",getsendmailBox(filePath));

		fputs(sub,fpW);
		fputs(date,fpW);
		fputs(sender,fpW);
		fputs("内容:\n",fpW);

		int contentFlag=0;
		int decodeBaseS=0;
		int firstEnter = 0;
		int secEnter = 0;
		int startR=0;

		//下面是获取邮件正文信息并保存
		while(fgets(temp,sizeof(temp),fpR))
		{
			if(strcmp(temp,"\r\n")==0)
				contentFlag=1;
			if(contentFlag == 1 && strstr(temp,"Content-Transfer-Encoding: base64"))
			{
				decodeBaseS = 1;
				startR =1;
				continue;
			}
			if(decodeBaseS==1)
			{
				if(strcmp(temp,"\r\n")!=0)
				{
					fputs(base64_decode(temp,strlen(temp)),fpW);
					memset(temp,0,sizeof(temp));
					startR++;
				}
				else
				{
					if(startR!=1)
					{
					  secEnter =1;
					}
				}
			}
			if(secEnter==1)
			{
				decodeBaseS=0;
				firstEnter=0;
				secEnter = 0;
				startR=0;
			}	
		}*/
		MessageBox(NULL,TEXT("打开成功"),TEXT(""),MB_OK);
		fputs("内容:\n",fpW);
		fclose(fpW);
		fclose(fpR);
		fpW=NULL;
		fpR=NULL;
		return true;
	}
	if(fpW!=NULL )
	{
		fclose(fpW);
	}
	if(fpR!=NULL )
	{
		fclose(fpR);
	}
	return false;
}