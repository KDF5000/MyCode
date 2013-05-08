//Download by http://www.NewXing.com
#include <iostream>
#include "PE.h"
using namespace std;

void main()
{
	CPE peObj;
	if(!peObj.ModifyPE("G:\\git\\KDF5000\\WinMain\\Debug\\WinMain.exe"))
	{
		cout<<"Write Faild!"<<endl;
	}
	else
	{
		cout<<"Write OK"<<endl;
	}
}