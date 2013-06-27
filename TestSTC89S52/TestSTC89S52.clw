; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestSTC89S52Dlg
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestSTC89S52.h"

ClassCount=4
Class1=CTestSTC89S52App
Class2=CTestSTC89S52Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMScomm
Resource3=IDD_TESTSTC89S52_DIALOG

[CLS:CTestSTC89S52App]
Type=0
HeaderFile=TestSTC89S52.h
ImplementationFile=TestSTC89S52.cpp
Filter=N

[CLS:CTestSTC89S52Dlg]
Type=0
HeaderFile=TestSTC89S52Dlg.h
ImplementationFile=TestSTC89S52Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=TestSTC89S52Dlg.h
ImplementationFile=TestSTC89S52Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTSTC89S52_DIALOG]
Type=1
Class=CTestSTC89S52Dlg
ControlCount=6
Control1=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control2=IDC_EDIT1,edit,1350631552
Control3=IDC_CONTROL,button,1342242816
Control4=IDC_TREE1,SysTreeView32,1350631424
Control5=IDC_TREECTRL1,{C74190B6-8589-11D1-B16A-00C0F0283628},1342242816
Control6=IDC_LIST1,SysListView32,1350631425

[CLS:CMScomm]
Type=0
HeaderFile=MScomm.h
ImplementationFile=MScomm.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=IDC_MSCOMM1

