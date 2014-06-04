// NewProceeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProcessCtrlProject.h"
#include "NewProceeDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include<CString>
using namespace std;

// CNewProceeDlg 对话框

IMPLEMENT_DYNAMIC(CNewProceeDlg, CDialog)

CNewProceeDlg::CNewProceeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProceeDlg::IDD, pParent)
{
	NewProcessList = NULL;//新创建的进程为空
	Exist = true;//初始创建的时候窗口显然存在
	FirstCreate = false;//最开始没有创建 
}

CNewProceeDlg::~CNewProceeDlg()
{
}

void CNewProceeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListNewProcess);
}


BEGIN_MESSAGE_MAP(CNewProceeDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewProceeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CNewProceeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNewProceeDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CNewProceeDlg 消息处理程序

void CNewProceeDlg::InitialPage()
{
	//设置格式
	m_ListNewProcess.ModifyStyle( 0, LVS_REPORT );               // 报表模式  
	m_ListNewProcess.SetExtendedStyle(m_ListNewProcess.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // 间隔线+行选中  
	//插入表头，表头的每一项都要居中
	m_ListNewProcess.InsertColumn(0,_T("进程名"),LVCFMT_CENTER);
	m_ListNewProcess.InsertColumn(1,_T("优先级"),LVCFMT_CENTER);
	m_ListNewProcess.InsertColumn(2,_T("所需时间"),LVCFMT_CENTER);
	//设置每一列的宽度
	CRect rect;  
	m_ListNewProcess.GetClientRect(rect); //获得当前客户区信息  
	m_ListNewProcess.SetColumnWidth(0, rect.Width() *40/ 100);  
	m_ListNewProcess.SetColumnWidth(1, rect.Width() *30/ 100);
	m_ListNewProcess.SetColumnWidth(2, rect.Width() *30/ 100);

}


void CNewProceeDlg::OnBnClickedButton1()
{
	int Priority = 0;
	int AllTime = 0;
	//获取编辑栏的信息
	CString s_ProcessName;
	CString s_Priority;
	CString s_AllTime;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(s_ProcessName);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(s_Priority);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(s_AllTime);
	//检测编辑栏的信息
	//如果没有填写进程名，则不进行下面的操作
	if (s_ProcessName.IsEmpty())
	{
		AfxMessageBox(_T("请填写进程名"));
	}
	else if (s_ProcessName.GetLength() >= 50)
	{
		AfxMessageBox(_T("进程名太长"));
	}
	//如果填写了进程，则将这个进程添加进来
	//将信息赋值到一个PCB链表中并且添加到列表中
	else
	{
		//创建PCB
		int nLength = s_ProcessName.GetLength();
		int nBytes = WideCharToMultiByte(CP_ACP,0,s_ProcessName,nLength,NULL,0,NULL,NULL);
		char* ProcessName = new char[50];
		memset(ProcessName,0, 50);
		WideCharToMultiByte(CP_OEMCP, 0, s_ProcessName, nLength, ProcessName, nBytes, NULL, NULL); 
		ProcessName[nBytes] = 0;
		if (s_Priority.IsEmpty())
			Priority = 30;
		else
			Priority = _ttoi(s_Priority);
		if (s_AllTime.IsEmpty())
			AllTime = 50;
		else
			AllTime = _ttoi(s_AllTime);
		PCB * newProcess = (struct PCB *)malloc(sizeof(PCB));
		newProcess->AllTime = AllTime;
		newProcess->Priority = Priority;
		for (int i = 0 ; i < 50 ; i++)
			newProcess->ProcessName[i] = ProcessName[i];
		newProcess->next = NewProcessList;
		NewProcessList = newProcess;
		//更新列表
		AddProcessIntoNewProcessList(newProcess->ProcessName, newProcess->Priority, newProcess->AllTime);
		m_ListNewProcess.UpdateWindow();
		SetDlgItemText(IDC_EDIT1, _T(""));//清空输入框
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
	}
}


void CNewProceeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Exist = false;
	//清空这个列表
	SetDlgItemText(IDC_EDIT1, _T(""));//清空输入框
	SetDlgItemText(IDC_EDIT2, _T(""));
	SetDlgItemText(IDC_EDIT3, _T(""));
	m_ListNewProcess.DeleteAllItems();
	CDialog::OnOK();
}


void CNewProceeDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT1, _T(""));//清空输入框
	SetDlgItemText(IDC_EDIT2, _T(""));
	SetDlgItemText(IDC_EDIT3, _T(""));
	m_ListNewProcess.DeleteAllItems();
	//清空要添加的进程列表
	NewProcessList = NULL;
	CDialog::OnCancel();
}

void CNewProceeDlg::AddProcessIntoNewProcessList(char ProcessName[50], int Priority, int AllTime)
{
	CString str = CString(ProcessName);  
	USES_CONVERSION;
	LPCWSTR wszProcessName = A2CW(W2A(str));  
	str.ReleaseBuffer(); 
	m_ListNewProcess.InsertItem(0, wszProcessName); 

	wchar_t ch[5];
	_itow_s( Priority, ch, 5, 10);
	m_ListNewProcess.SetItemText(0, 1, ch); 

	_itow_s( AllTime, ch, 5, 10);
	m_ListNewProcess.SetItemText(0, 2, ch); 
}