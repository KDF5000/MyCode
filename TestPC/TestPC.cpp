#include <stdio.h>
#include <windows.h>

//记录产品数,设计最大产品数为20，模拟缓冲区大小
int productCount=0;
//临界区对象
CRITICAL_SECTION metux;
//句柄，保存Full信号量
HANDLE hFull;
//句柄，保存Empty信号量
HANDLE hEmpty;

DWORD WINAPI productor(LPVOID lpData)
{
	int i=0; //循环次数
	while(1)
	{
		WaitForSingleObject(hEmpty,INFINITE);
		EnterCriticalSection( &metux);
		productCount++;
		printf("生产第%d件产品,现存产品%d件\n",i+1,productCount);
		LeaveCriticalSection( &metux);
		ReleaseSemaphore(hFull,1,NULL);
		i++;
	}
	return 0;
}

DWORD WINAPI consumer(LPVOID lpData)
{
	while(1)
	{
		WaitForSingleObject(hFull,INFINITE);
		EnterCriticalSection( &metux);
		productCount--;
		printf("消费者消灭一件产品,还剩余%d件\n",productCount);
		Sleep(1000); //睡眠1秒钟
		LeaveCriticalSection( &metux);
		ReleaseSemaphore(hEmpty,1,NULL);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	 HANDLE hThreadProducer,hThreadConsumer;

	 InitializeCriticalSection( &metux);
	 hFull  = CreateSemaphore(NULL, 0, 100, NULL);
	 hEmpty = CreateSemaphore(NULL,100, 100, NULL);

	 hThreadProducer  = CreateThread(NULL, 0, productor,  NULL, 0, NULL);
	 hThreadConsumer = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

	 getchar();
	 return 0;
}
