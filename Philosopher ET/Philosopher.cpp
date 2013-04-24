#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
//句柄，保存chopsticks信号量
HANDLE chopsticks[6];
HANDLE Philosopher[6];
//临界区对象
CRITICAL_SECTION metux;
int states[6];

DWORD WINAPI PhilosopherET(LPVOID lpData)
{
	//哲学家编号
	int i = (int)lpData;
	while(1)
	{
		//Sleep(1000);
		//EnterCriticalSection( &metux);
		//printf("哲学家%d正在思考中\n",i);
		//LeaveCriticalSection( &metux);
		states[i]=0;
		WaitForSingleObject(chopsticks[i],INFINITE);
		if(WaitForSingleObject(chopsticks[(i+1)%5],INFINITE)!=WAIT_OBJECT_0 )
		{
			ReleaseSemaphore(chopsticks[i],1,NULL);
			continue;
		}
		//EnterCriticalSection( &metux);
		//printf("哲学家%d正在吃饭中\n",i);
		//LeaveCriticalSection( &metux);
		states[i] = 1;
		Sleep(1000);
		ReleaseSemaphore(chopsticks[i],1,NULL);
		ReleaseSemaphore(chopsticks[(i+1)%5],1,NULL);
	}

}

void main()
{
	int j;
	InitializeCriticalSection( &metux);
	for(j=1;j<6;j++)
	{
		states[j]=0;
	}
	for(j=1;j<6;j++)
	{
		chopsticks[j] = CreateSemaphore(NULL, 1, 1, NULL);
	}
	for(j=1;j<6;j++)
	{
		Philosopher[j] = CreateThread(NULL, 0, PhilosopherET, (LPVOID)j, 0, NULL);
	}
	while(1)
	{
		printf("哲学家:	  1	   2	  3	   4 	 5\n");
		printf("状  态:");
		for(j=1;j<6;j++)
		{
			if(states[j]==1)
			    printf("	吃饭中");
			else
				printf("	思考中");
		}
		printf("\n**************************************************\n\n");
		Sleep(1000);
	}
	getchar();
	return ;
}