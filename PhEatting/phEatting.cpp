#include <stdio.h>
#include <windows.h>

//�����ѧ�� 5ֻ����
int Chopsticks[6];   //ֵΪ1����
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
	philosopher[i] = 0; //���߱��Ϊi�Ŀ���
}
void release(int i)
{
	philosopher[i] = 1; //���±��Ϊi�Ŀ���
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
		printf("��ѧ��%d,˼����...\n",*i);
		//�����������ֱ߿���
		if(!Try(*i))
			continue;
		if(!Try((*i+1)%5))
			continue;
		//���߿���
		Take(*i);
		Take((*i+1)%5);
		printf("��ѧ��%d���Է���\n",*i);
		Sleep(1000);
		//���¿���
		release(*i);    //�������ֱ߿���
		release(*i);    //�������ֱ߿���
		mutexV();
	}
	return 0;
}

void main()
{
	int i;
	//��ʼ��
	for(i=1;i<6;i++)
	{
		Chopsticks[i]  = 1;//ֵΪ1����
		philosopher[i] = i;
	
		hwnd[i] = CreateThread(NULL,0,philosopherET,&i,0,0);
	}
	WaitForSingleObject(hwnd[1],INFINITE);
	//WaitForMultipleObjects(6,hwnd,false,INFINITE);
}