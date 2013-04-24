#include <stdio.h>
#include <windows.h>

#define  BUFFER_SIZE  20
//ȫ�ֱ���������������������Ϊ
int mutex = 1;					//��ֵ�źŵƣ�����ֻ��һ�������߻��������߷�����Դ
int fillCount = 0;				//������Դ����
int emptyCount = BUFFER_SIZE;   //���ÿռ����
int productCount = 0;           //��Ʒ����
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
		printf("������������һ����Ʒ����Ʒ��Ϊ%d\n",productCount);
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
		printf("������������һ����Ʒ����Ʒ��Ϊ:%d\n",productCount);
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