#include <stdio.h>
#include <windows.h>

#define  BUFFER_SIZE  20
//全局变量控制生产者消费者行为
int mutex = 1;					//二值信号灯，控制只有一个消费者或者生产者访问资源
int fillCount = 0;				//可用资源个数
int emptyCount = BUFFER_SIZE;   //可用空间个数
int productCount = 0;           //产品个数
HANDLE hwndP;
HANDLE hwndC;

void fillCountP(HANDLE hwnd)
{
	fillCount--;
	if(fillCount<=0)
		SuspendThread(hwnd);
}
void fillcountV(HANDLE hwnd)
{
	fillCount++;
	if(fillCount>0)
		ResumeThread(hwnd);
}

void emptyCountP(HANDLE hwnd)
{
	emptyCount--;
	if(emptyCount<0)
		SuspendThread(hwnd);

}
void emptyCountV(HANDLE hwnd)
{
	emptyCount++;
	if(emptyCount>=0)
		ResumeThread(hwnd);
}
bool MutexP()
{
	if(mutex ==0)
		return false;
	mutex = 0;
	return true;
}

void MutexV()
{
	mutex = 1;
}

DWORD WINAPI producer(LPVOID data)
{
	while(true)
	{
		emptyCountP(hwndP);
		if(!MutexP())
			continue;
		productCount++;
		printf("生产者又生产一个产品，产品数为%d\n",productCount);
		MutexV();
		fillcountV(hwndC);
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI consumer(LPVOID data)
{
	while(true)
	{
		fillCountP(hwndC);
		if(!MutexP())
			continue;
		productCount--;
		printf("消费者又消费一个产品，产品数为:%d\n",productCount);
		MutexV();
		emptyCountV(hwndP);
		Sleep(1000);
	}
	return 0;
}

void main()
{
	hwndP = CreateThread(NULL,0,producer,NULL,0,0);
	hwndC = CreateThread(NULL,0,consumer,NULL,0,0);
	WaitForSingleObject(hwndP,INFINITE);
	WaitForSingleObject(hwndC,INFINITE);
}