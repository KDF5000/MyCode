; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Test
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestTreeCtrl.h"

ClassCount=5
Class1=CTestTreeCtrlApp
Class2=CTestTreeCtrlDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=bulidTreeCtrl
Class5=Test
Resource3=IDD_TESTTREECTRL_DIALOG

[CLS:CTestTreeCtrlApp]
Type=0
HeaderFile=TestTreeCtrl.h
ImplementationFile=TestTreeCtrl.cpp
Filter=N

[CLS:CTestTreeCtrlDlg]
Type=0
HeaderFile=TestTreeCtrlDlg.h
ImplementationFile=TestTreeCtrlDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BULIDING

[CLS:CAboutDlg]
Type=0
HeaderFile=TestTreeCtrlDlg.h
ImplementationFile=TestTreeCtrlDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTTREECTRL_DIALOG]
Type=1
Class=CTestTreeCtrlDlg
ControlCount=2
Control1=IDC_BULIDING,SysTreeView32,1350631431
Control2=IDC_ROOMLIST,SysListView32,1350631425

[CLS:bulidTreeCtrl]
Type=0
HeaderFile=bulidTreeCtrl.h
ImplementationFile=bulidTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W

[CLS:Test]
Type=0
HeaderFile=Test.h
ImplementationFile=Test.cpp
BaseClass=CTreeCtrl
Filter=W

