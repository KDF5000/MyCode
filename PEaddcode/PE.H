//Download by http://www.NewXing.com
#pragma once
#ifndef __DEBUG
#define __DEBUG
#include <fstream>
#include <iostream>
using namespace std;
#endif
#include <WINDOWS.H>
#include <IO.H>
#include <fcntl.h>
#include <sys/stat.h>
#include <shellapi.h>

typedef struct _PE_HEADER
{
	DWORD signature;
    IMAGE_FILE_HEADER _head;
    IMAGE_OPTIONAL_HEADER opt_head;
    IMAGE_SECTION_HEADER section_header[6];
}PE_HERDER;

class CPE
{
public:
	CPE(void);
public:
	~CPE(void);
private:
	bool GetPEAddress(const void* Basepoint);					//获取PE地址	
	bool WriteNewEntry(int ret,long offset,DWORD dwAddress);	//写入新入口
	bool WriteCode(int ret,long offset,char* strCap,char* strText,char* openFlag,char* Address);//写入代码
	void DWORDTOSTR(DWORD dwAddress,unsigned char* chStr);		//DWORD转换为字符串
	bool WriteFile(char* FileName);		
private:
	DWORD dwSpace;				//可用空间
	DWORD dwRAV;				//程序装载地址 一般为0x400000
	DWORD dwVirSize;			//真实大小
	DWORD dwEntryAddress;		//入口地址
	DWORD dwWriteEntry;			//写入地址入口
	DWORD dwOldEntry;			//old入口
	DWORD dwNewEntry;			//新入口
	DWORD dwCodeOffset;			//代码偏移
	DWORD dwPeAddress;			//PE 地址
	DWORD dwFlagAddress;		//标志地址
	DWORD dwVirtualSize;		//虚拟大小
	DWORD dwPhyAddress;			//物理地址
	DWORD dwPhySize;			//物理大小
	DWORD dwCodeAddress;		//写入的MessageBox的函数地址
	DWORD dwShellAddress;		//退出代码
public:
	bool ModifyPE(char* strFileName);	
};
