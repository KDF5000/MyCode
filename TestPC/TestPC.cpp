#include <stdio.h>
#include <windows.h>

//��¼��Ʒ��,�������Ʒ��Ϊ20��ģ�⻺������С
int productCount=0;
//�ٽ�������
CRITICAL_SECTION metux;
//���������Full�ź���
HANDLE hFull;
//���������Empty�ź���
HANDLE hEmpty;

DWORD WINAPI productor(LPVOID lpData)
{
	int i=0; //ѭ������
	while(1)
	{
		WaitForSingleObject(hEmpty,INFINITE);
		EnterCriticalSection( &metux);
		productCount++;
		printf("������%d����Ʒ,�ִ��Ʒ%d��\n",i+1,productCount);
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
		printf("����������һ����Ʒ,��ʣ��%d��\n",productCount);
		Sleep(1000); //˯��1����
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
