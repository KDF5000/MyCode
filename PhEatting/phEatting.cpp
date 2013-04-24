#include <stdio.h>
#include <windows.h>

//五个哲学家 5只筷子
int Chopsticks[6];   //值为1可用
int philosopher[6];
int mutex =1;
HANDLE hwnd[6];
bool Try(int i)
{
	if(philosopher[i]==0)
		return false;
	return true;
}
void Take(int i)
{
	philosopher[i] = 0; //拿走编号为i的筷子
}
void release(int i)
{
	philosopher[i] = 1; //放下编号为i的筷子
}
bool mutexP()
{
	if(mutex==0)
		return false;
	mutex =0;
	return true;
}
void mutexV()
{
	mutex =1;
}
DWORD WINAPI philosopherET(LPVOID number)
{
	int *i = (int *)number;
	while(true)
	{
		if(!mutexP())
			continue;
		printf("哲学家%d,思考中...\n",*i);
		//尝试拿走右手边筷子
		if(!Try(*i))
			continue;
		if(!Try((*i+1)%5))
			continue;
		//拿走筷子
		Take(*i);
		Take((*i+1)%5);
		printf("哲学家%d，吃饭中\n",*i);
		Sleep(1000);
		//放下筷子
		release(*i);    //放下右手边筷子
		release(*i);    //放下左手边筷子
		mutexV();
	}
	return 0;
}

void main()
{
	int i;
	//初始化
	for(i=1;i<6;i++)
	{
		Chopsticks[i]  = 1;//值为1可用
		philosopher[i] = i;
	
		hwnd[i] = CreateThread(NULL,0,philosopherET,&i,0,0);
	}
	WaitForSingleObject(hwnd[1],INFINITE);
	//WaitForMultipleObjects(6,hwnd,false,INFINITE);
}