#include <stdio.h>
#include <windows.h>

void main()
{
	char password[50];
	int i=0;
	memset(password,0,sizeof(password));
	while(strcmp(password,"kong19920213")!=0)
	{
		i++;
		printf("��%d�������룺",i);
		gets(password);
		
		if(i>=3)
			break;
	}
	if(i==3)
	{
		printf("�����������!\n");
		exit(1);
	}
}