#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
//���������chopsticks�ź���
HANDLE chopsticks[6];
HANDLE Philosopher[6];
//�ٽ�������
CRITICAL_SECTION metux;
int states[6];

DWORD WINAPI PhilosopherET(LPVOID lpData)
{
	//��ѧ�ұ��
	int i = (int)lpData;
	while(1)
	{
		//Sleep(1000);
		//EnterCriticalSection( &metux);
		//printf("��ѧ��%d����˼����\n",i);
		//LeaveCriticalSection( &metux);
		states[i]=0;
		WaitForSingleObject(chopsticks[i],INFINITE);
		if(WaitForSingleObject(chopsticks[(i+1)%5],INFINITE)!=WAIT_OBJECT_0 )
		{
			ReleaseSemaphore(chopsticks[i],1,NULL);
			continue;
		}
		//EnterCriticalSection( &metux);
		//printf("��ѧ��%d���ڳԷ���\n",i);
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
		printf("��ѧ��:	  1	   2	  3	   4 	 5\n");
		printf("״  ̬:");
		for(j=1;j<6;j++)
		{
			if(states[j]==1)
			    printf("	�Է���");
			else
				printf("	˼����");
		}
		printf("\n**************************************************\n\n");
		Sleep(1000);
	}
	getchar();
	return ;
}