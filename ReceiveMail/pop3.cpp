#include "pop3.h"
#include "stdafx.h"
#include "BaseDecode.h"

#include <winsock2.h>
#define MAXBUF 4096
//���ڱ���ӷ��������ص�����
char recvbuf[MAXBUF];
//�������ƽ������Ľ���
int statues;
char *monthT[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
char *weekdayT[7]={"Sun","Mon","Tue","Web","Thu","Fri","Sat"};
//��ʼ��sock
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
//���ӷ�����
bool ConnectServer(SOCKET *socket,const char *domain,const int port)
{
	
	struct hostent *phost = gethostbyname(domain); 
	//����һ������ 
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

//��ʾ���Ӵ���
void ShowError()
{
	TCHAR* lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER| //�Զ�������Ϣ������
	FORMAT_MESSAGE_FROM_SYSTEM, //��ϵͳ��ȡ��Ϣ
	NULL,GetLastError(), //��ȡ������Ϣ��ʶ
	MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),//ʹ��ϵͳȱʡ����
	(LPTSTR)&lpMsgBuf, //��Ϣ������
	0, NULL);
	MessageBox(NULL,lpMsgBuf,"",MB_ICONERROR);
}


//���ӵ�ָ��������
bool connectUserMail(SOCKET socket,char *username,char *password )
{
	char nameStr[30] ={0};       //�û���  
    char passStr[30] = {0};      //����
	char ret[MAXBUF];
	wsprintf(nameStr,"USER %s\t\n",username);
	wsprintf(passStr,"PASS %s\t\n",password);

	 //����ָ������
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


//��ȡ�ʼ�����Ŀ(δ���)
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
	//ѭ�����ǻ��� ��֪��ʲôԭ��
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

//��ȡָ���ʼ����ı�,���ر��浽�ļ���
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
//��ȡ�����ʼ������б���
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
//�˳����Ͽ��������������

void Quit(SOCKET socket)
{
	char quit[MAXBUF] ="QUIT\t\n";
	memset(recvbuf , 0 ,MAXBUF); 
    send( socket ,quit, strlen(quit) , 0 ) ; 
	recv(socket , recvbuf , MAXBUF , 0);  
	return ;
}
//�жϷ�����Ϣ�Ƿ���OK
bool IsOK(char * message)
{
    if (tolower(message[1])=='o'&&tolower(message[2])=='k' )
        return 1;
    else
        return 0;
}

//�����ļ�
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

//��creatthread�����߳�
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
			MessageBox(user->hwnd,TEXT("����������ʧ�ܣ�"),TEXT(""),MB_OK || MB_ICONWARNING);
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
			int allMailFlag = 0;  //�ж������ʼ���������ź�
			int mailIDsFlag = 0; //�ж���ƥ���ض��������ʱ����ź�
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
			//����ѡ���������ʼ�
			switch(user->randRadio)
			{
			  case IDC_ALLMAIL:
					//��ȡ�����ʼ�������temp��
				  //����������ʼ����ٶȿ��ܱȽ���
				  saveAllMail(httpsock,tempPath,user->hwnd,numbers);
				  //֪ʶ�����ʼ�����Ϣͷ��
				  //saveAllMailHeadInfo(httpsock,makeDir(tempPath),user->hwnd,numbers);
				  allMailFlag = 1;
				  break;
			  case IDC_DATERANGE:
				    //��ȡָ�����ڷ�Χ�ڵ��ʼ�
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
				    //��ȡָ���ʼ�������ʼ�
				  GetDlgItemText(user->hwnd,IDC_SUB,sub,sizeof(sub));
				 // MessageBox(user->hwnd,sub,TEXT(""),MB_OK);
				  mailID = saveMailBySub(sub,httpsock,makeDir(tempPath));
				  if(mailID==-1)
					  MessageBox(user->hwnd,TEXT("�Բ���û���ҵ���������ʼ�!"),TEXT(""),MB_OK);
				  break;
			  case IDC_SENDBOX:
				    //��ȡָ��������ʼ�
					//����ָ������������ʼ�
				  GetDlgItemText(user->hwnd,IDC_MAILBOX,boxName,sizeof(boxName));
                  mailIDs = saveBymailBox(boxName,httpsock,makeDir(tempPath),numbers);
				  mailIDsFlag = 1;
				  break;
			  default :
				  break;
			}
			//����ָ����ʽ�����յ����ʼ����д���
			switch(user->methodRadio)
			{
				case IDC_BOXNAME:
				    //���������������ڱ���
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
					 //������������ڱ���
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
					//���յ�һ�������������ڱ���
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
			MessageBox(user->hwnd,TEXT("�����ɹ�"),TEXT(""),MB_OK );
			Quit(httpsock);
			return 1;

		}
		else
		{
			MessageBox(user->hwnd,TEXT("�û���¼ʧ��"),TEXT(""),MB_OK || MB_ICONWARNING);
			Quit(httpsock);
			return 0;
		}
	}
	MessageBox(user->hwnd,TEXT("�Բ��𣬳�ʼ��ʧ�ܣ��Ժ�����"),TEXT(""),MB_OK || MB_ICONWARNING);
	return 0;
}

//��ȡ����ӱ�����ʼ���
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

//���ʼ���Ϣͷ�л�ȡ����
char * getsubjectFromHeader(int number ,SOCKET httpsock)
{
	
	char info[MAXBUF];
	char sub[100]; //���ڱ�������
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
		//MessageBox(NULL,TEXT("�ҵ�Subject: "),TEXT(""),MB_OK);
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
//��ȡ�ʼ����ڴӱ�����ʼ���
//����Mon, 8 Apr 2013 08:27:39 +0800��ʽ
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
				//ȥ���ո񣬣���
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

//���ʼ�ͷ��Ϣ�л�ȡ����
char * getDateFromHeader(int number ,SOCKET httpsocket)
{
	char info[MAXBUF];
	char sub[50]; //���ڱ�������
	char noDate[] = "NO_DATE";
	char *p;
	int i;
	sprintf(info,"%s",getMailInfo(number,httpsocket));
    p = strstr(info,"Date: ");
	if(p!=NULL)
	{
		//MessageBox(NULL,TEXT("�ҵ�date: "),TEXT(""),MB_OK);
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
//����Ϣͷ����ȡ��������Ϣ
char * getSenderFromHeader(int number ,SOCKET httpsock)
{
	char info[MAXBUF];
	char sub[50]; //���ڱ��淢��������
	char mailName[30];//���ڱ��淢������
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
		//MessageBox(NULL,TEXT("�ҵ�From: "),TEXT(""),MB_OK);
		i=0;
		p = p+6;
		while(*p=='\n'||*p=='\r')
		{
			p++;
		}
		//���fromһ�е�����
		while(*(p+i)!='>')
		{
		  temp[i]=*(p+i);
		  i++;
		}
		temp[i]=*(p+i);
		i++;
		temp[i]='\0';
		
		//ƥ����base64���ܹ��ķ���������
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

			//ƥ�䷢��������
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

			//�����temp�����������ݣ�Ȼ�󽫷����������뷢�������ֺϲ�
			memset(temp,0,sizeof(temp));
			//�������ķ������������Ƶ�temp������
			if(pB!=NULL)
			    strcpy(temp,base64_decode(sub,strlen(sub)));
			else
				strcpy(temp,sub);  //��Q...����
			//�������������뷢����������
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
	char noSender[] = "�޷�������Ϣ";
	return noSender;

}
//��ȡ���������֣����ļ���
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
//��ȡ��һ����������
char * getAttachName(char *filename)
{
	
	FILE *fp = fopen(filename , "r");
	char temp[200];
	char att[200];
	char noAtt[] = "�޸���";
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
*dirName:Ҫ������Ŀ¼���֣������пո�
*���ܣ�����һ��ָ�����ֵ�Ŀ¼
***************************************/
char * makeDir(char *dirName)
{
	char cmd[200];
	if(access(dirName,0))//�ж�Ŀ¼�Ƿ����
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
*ȥ���ո���_����
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
*���ܣ�����ָ����ʽ�����ʼ�
*ʱ�䣺2013.4.8
***************************************************************/

void saveAllMail(SOCKET httpsock,char *filepath,HWND hwnd , int numbers)
{
	if(numbers<=0)
	{
		MessageBox(hwnd,TEXT("����������û���ʼ�"),TEXT("����"),MB_OK || MB_ICONWARNING);
		return ;
	}
	if(!GetAllmail(hwnd,httpsock,makeDir(filepath),numbers))
		MessageBox(hwnd,TEXT("�����ʼ�ʧ��!"),TEXT("SAVEFAIL"),MB_OK || MB_ICONWARNING);
	return;
}


//���������ʼ�����Ϣͷ
void saveAllMailHeadInfo(SOCKET httpsock,char *savepath,HWND hwnd , int numbers)
{	
	if(numbers<=0)
	{
		MessageBox(hwnd,TEXT("����������û���ʼ�"),TEXT("����"),MB_OK || MB_ICONWARNING);
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
			MessageBox(hwnd,TEXT("�����ļ�ʧ��"),TEXT(""),MB_OK);
			return ;
		}
	}
	return;
}

//��ȡ�ʼ���Ϣͷ(δ��)
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


//����ʱ�ļ�����ȡ������ݲ�����
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
			//����ʧ��
			//decodeMail(filepath,mailPath,maildir,i);
		//	remove(filepath);
			statues ++;
			SendDlgItemMessage(hwnd,IDC_PROGRESS1,PBM_SETPOS,statues,0);
		}
		return ;
}

//����һ���ļ���ָ��Ŀ¼
bool cutFile(char *sourcePath ,char *aimPath)
{
	char cmd[200];
	if(access(sourcePath,0)!=-1)//�ж�Ŀ¼�Ƿ����
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
*���ܣ�����ָ��������ʼ�
******************************************************/
int saveMailBySub(char *subject,SOCKET httpsock,char *path)
{
	int numbers = GetMailNumber(httpsock);
	int i;
	char sub[200];
	strcpy(sub,subject);
	char temp[200]; //���ڴ����Ϣͷ���յ����ʼ�����
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
*���ܣ�moveMailSD()�ƶ��ʼ���ָ���ļ���
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
    //����һ��Ŀ¼
	disSpace(subject);
	disSpace(date);
	wsprintf(maildir,"%s\\%s_%s",mailPath,subject,date);
	makeDir(maildir);
	//�����ļ���Ŀ���ļ���
	cutFile(filepath,maildir);
	memset(maildir,0,sizeof(maildir));
    sprintf(maildir,"%s_%s",subject,date);
	//����ʧ��
	//decodeMail(filepath,mailPath,maildir,mailID);
//	remove(filepath);
	return ;
}

//����ʱ�ʼ����ո�������������ת��
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

    //����һ��Ŀ¼
	wsprintf(maildir,"%s\\%s_%s",mailPath,attachment,date);
	makeDir(maildir);
	//�����ļ���Ŀ���ļ���
	cutFile(filepath,maildir);
	memset(maildir,0,sizeof(maildir));
    sprintf(maildir,"%s_%s",attachment,date);
	//����ʧ��
	//decodeMail(filepath,mailPath,maildir,mailID);
	//remove(filepath);
	return ;
}
//�������ʼ��ƶ���ָ���ļ��а��ո�������������ת��
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

//�������ʼ��ƶ���ָ���ļ��а��շ������������ת��hwnd����ʱʹ��
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


    //����һ��Ŀ¼
	wsprintf(maildir,"%s\\%s_%s",mailPath,mailbox,date);
	makeDir(maildir);
	//�����ļ���Ŀ���ļ���
	//cutFile(filepath,maildir);
	memset(maildir,0,sizeof(maildir));
	sprintf(maildir,"%s_%s",mailbox,date);
	//����ʧ��*
	decodeMail(filepath,mailPath,maildir,mailID);
	//remove(filepath);
	return ;
}

//�������ʼ��ƶ���ָ���ļ��а��շ������������ת��hwnd����ʱʹ��
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

//�Ƚ�����dateTime�ṹ�����ڵĴ�С
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
//�Ƚ����ڱ����ʼ�
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
	    //����ҵ��·�
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

//����ָ������������ʼ�
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
	char temp[200]; //���ڴ����Ϣͷ���յ����ʼ�����
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

//MIME������ȡ
//��ָ��δ������ļ����벢���浽ָ���ļ���

bool decodeMail(char *filePath, char *mailPath,char *maildir,int mailID)
{
	char filename[100];
	char sub[200];
	char subtemp[200]; //����������Ϣ�ڽ����ļ�����ȡ��
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

        wsprintf(sub,"���⣺%s\n",subtemp);
		wsprintf(date,"���ڣ�%s",getMailData(filePath));
		wsprintf(sender,"������:%s\n",getsendmailBox(filePath));

		fputs(sub,fpW);
		fputs(date,fpW);
		fputs(sender,fpW);
		fputs("����:\n",fpW);

		int contentFlag=0;
		int decodeBaseS=0;
		int firstEnter = 0;
		int secEnter = 0;
		int startR=0;

		//�����ǻ�ȡ�ʼ�������Ϣ������
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
		MessageBox(NULL,TEXT("�򿪳ɹ�"),TEXT(""),MB_OK);
		fputs("����:\n",fpW);
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