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
		printf("第%d输入密码：",i);
		gets(password);
		
		if(i>=3)
			break;
	}
	if(i==3)
	{
		printf("输入次数超限!\n");
		exit(1);
	}
}