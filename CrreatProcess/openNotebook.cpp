#include <stdio.h>
#include <windows.h>

int main()
{

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);//��ʼ��si
	si.lpReserved = NULL; 
	si.lpDesktop = NULL; 
	si.lpTitle = NULL; 
	si.dwFlags = 0; 
	si.cbReserved2 = 0; 
	si.lpReserved2 = NULL; 
	

	if(!CreateProcess("c:\\windows\\system32\\notepad.exe",NULL,NULL,NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		printf("��ʧ��");
	}
	return 0;
}