// m_page1.cpp : 实现文件
//

#include "stdafx.h"
#include "ProcessCtrlProject.h"
#include "m_page1.h"
#include "afxdialogex.h"
#include "ProcessCtrlProjectDlg.h"
#include "NewProceeDlg.h"

//全局的MainProcess
CProcessCtrlProjectDlg MainProcess;
CNewProceeDlg NewProcess;

IMPLEMENT_DYNAMIC(m_page1, CDialog)

m_page1::m_page1(CWnd* pParent /*=NULL*/)
	: CDialog(m_page1::IDD, pParent)
{
}

m_page1::~m_page1()
{
}

void m_page1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_LIST3, m_ListTop);
}

BEGIN_MESSAGE_MAP(m_page1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &m_page1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &m_page1::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &m_page1::OnBnClickedButton2)
END_MESSAGE_MAP()

void m_page1::InitialTabPage()
{
	/*********初始化下面的进程列表*********/
	//设置格式
	m_List.ModifyStyle( 0, LVS_REPORT );               // 报表模式  
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // 间隔线+行选中  
	//插入表头，表头的每一项都要居中
	m_List.InsertColumn(0,_T("PID"),LVCFMT_CENTER);  
	m_List.InsertColumn(1,_T("进程名"),LVCFMT_CENTER);
	m_List.InsertColumn(2,_T("优先级"),LVCFMT_CENTER);
	m_List.InsertColumn(3,_T("到达时间"),LVCFMT_CENTER);
	m_List.InsertColumn(4,_T("进程余下时间"),LVCFMT_CENTER);
	m_List.InsertColumn(5,_T("已运行时间"),LVCFMT_CENTER);
	m_List.InsertColumn(6,_T("连续运行时间"),LVCFMT_CENTER);
	m_List.InsertColumn(7,_T("连续就绪时间"),LVCFMT_CENTER);
	m_List.InsertColumn(8,_T("状态"),LVCFMT_CENTER);
	//设置每一列的宽度
	CRect rect;  
	m_List.GetClientRect(rect); //获得当前客户区信息  
	m_List.SetColumnWidth(0, rect.Width()*8 / 100); 
	m_List.SetColumnWidth(1, rect.Width() *12/ 100);  
	m_List.SetColumnWidth(2, rect.Width() *10/ 100);
	m_List.SetColumnWidth(3, rect.Width() *10/ 100);
	m_List.SetColumnWidth(4, rect.Width() *10/ 100);
	m_List.SetColumnWidth(5, rect.Width() *12/ 100);
	m_List.SetColumnWidth(6, rect.Width() *14/ 100);
	m_List.SetColumnWidth(7, rect.Width() *14/ 100);
	m_List.SetColumnWidth(8, rect.Width() *10/ 100);
	/**************************************/

	/*********初始化上面正在执行的进程列表*********/
	//设置格式
	m_ListTop.ModifyStyle( 0, LVS_REPORT );               // 报表模式  
	m_ListTop.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // 间隔线+行选中  
	//插入表头，表头的每一项都要居中
	m_ListTop.InsertColumn(0,_T("PID"),LVCFMT_CENTER);  
	m_ListTop.InsertColumn(1,_T("进程名"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(2,_T("优先级"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(3,_T("到达时间"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(4,_T("进程余下时间"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(5,_T("已运行时间"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(6,_T("连续运行时间"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(7,_T("连续就绪时间"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(8,_T("状态"),LVCFMT_CENTER);
	//设置每一列的宽度
	CRect rectTop;  
	m_ListTop.GetClientRect(rectTop); //获得当前客户区信息  
	m_ListTop.SetColumnWidth(0, rectTop.Width()*8 / 100); 
	m_ListTop.SetColumnWidth(1, rectTop.Width() *12/ 100);  
	m_ListTop.SetColumnWidth(2, rectTop.Width() *10/ 100);
	m_ListTop.SetColumnWidth(3, rectTop.Width() *10/ 100);
	m_ListTop.SetColumnWidth(4, rectTop.Width() *10/ 100);
	m_ListTop.SetColumnWidth(5, rectTop.Width() *12/ 100);
	m_ListTop.SetColumnWidth(6, rectTop.Width() *14/ 100);
	m_ListTop.SetColumnWidth(7, rectTop.Width() *14/ 100);
	m_ListTop.SetColumnWidth(8, rectTop.Width() *10/ 100);
	/***************************************************/
}

void m_page1::AddProcessIntoList(int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State )
{  
	//使用_itow_s方法转换int型参数
	wchar_t ch[5];
	_itow_s( PID, ch, 5, 10);
	m_List.InsertItem(0, ch);
	//使用A2CW方法将char* 转成LPCWSTR
	CString str = CString(ProcessName);  
	USES_CONVERSION;
	LPCWSTR wszProcessName = A2CW(W2A(str));  
	str.ReleaseBuffer(); 
	m_List.SetItemText(0, 1, wszProcessName); 
	/***********/
	_itow_s( Priority, ch, 5, 10);
	m_List.SetItemText(0, 2, ch); 
	/***********/
	_itow_s( EnterTime, ch, 5, 10);
	m_List.SetItemText(0, 3, ch);
	/***********/
	_itow_s( AllTime, ch, 5, 10);
	m_List.SetItemText(0, 4, ch);
	/***********/
	_itow_s( UsedTime, ch, 5, 10);
	m_List.SetItemText(0, 5, ch);
	/***********/
	_itow_s( RunTime, ch, 5, 10);
	m_List.SetItemText(0, 6, ch);
	/***********/
	_itow_s( ReadyTime, ch, 5, 10);
	m_List.SetItemText(0, 7, ch); 
	/***********/
	if (State == 'R')
		m_List.SetItemText(0, 8, _T("运行"));
	else if (State == 'W')
		m_List.SetItemText(0, 8, _T("就绪"));

}

void m_page1::AddProcessIntoListTop( int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State)
{
	//使用_itow_s方法转换int型参数
	wchar_t ch[5];
	_itow_s( PID, ch, 5, 10);
	m_ListTop.InsertItem(0, ch);
	//使用A2CW方法将char* 转成LPCWSTR
	CString str = CString(ProcessName);  
	USES_CONVERSION;
	LPCWSTR wszProcessName = A2CW(W2A(str));  
	str.ReleaseBuffer(); 
	m_ListTop.SetItemText(0, 1, wszProcessName); 
	/***********/
	_itow_s( Priority, ch, 5, 10);
	m_ListTop.SetItemText(0, 2, ch); 
	/***********/
	_itow_s( EnterTime, ch, 5, 10);
	m_ListTop.SetItemText(0, 3, ch);
	/***********/
	_itow_s( AllTime, ch, 5, 10);
	m_ListTop.SetItemText(0, 4, ch);
	/***********/
	_itow_s( UsedTime, ch, 5, 10);
	m_ListTop.SetItemText(0, 5, ch);
	/***********/
	_itow_s( RunTime, ch, 5, 10);
	m_ListTop.SetItemText(0, 6, ch);
	/***********/
	_itow_s( ReadyTime, ch, 5, 10);
	m_ListTop.SetItemText(0, 7, ch); 
	if (State == 'R')
		m_ListTop.SetItemText(0, 8, _T("运行"));
	else if (State == 'W')
		m_ListTop.SetItemText(0, 8, _T("就绪"));
}

void m_page1::UpdateList(PCB *chosenProcess)
{
	PCB *temp;

	/**********更新就绪表**************/
	m_List.DeleteAllItems();//删除就绪表的内容
	for(temp = MainProcess.ProcessList ; temp != NULL; temp = temp->next)
		if (temp != chosenProcess)
		{
			temp->State = 'W';//将所有就绪进程的状态变成等待
			AddProcessIntoList(temp->PID,temp->ProcessName,temp->Priority,temp->EnterTime,
			temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime,temp->State);
		}
	/**********更新运行表***************/
	m_ListTop.DeleteAllItems();//删除原来的进程信息
	chosenProcess->State = 'R';//选中的进程变成运行状态
	AddProcessIntoListTop(chosenProcess->PID,chosenProcess->ProcessName,chosenProcess->Priority,chosenProcess->EnterTime,
		chosenProcess->AllTime,chosenProcess->UsedTime,chosenProcess->RunTime,chosenProcess->ReadyTime,chosenProcess->State);
	/***********打印所有进程****************/
	printf("第%d个进程片：\n",MainProcess.AccelerateTime+1);
	for (temp = MainProcess.ProcessList; temp != NULL; temp = temp->next)
	{
		if (temp->State == 'W')
			printf("PID: %d\t进程名: %s\t优先数: %d\t进程余下时间: %d\t已使用CPU时间: %d\t当前连续运行时间: %d\t连续就绪时间: %d\t状态: 就绪\n",
			temp->PID,temp->ProcessName,temp->Priority,temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime);
		else
			printf("PID: %d\t进程名: %s\t优先数: %d\t进程余下时间: %d\t已使用CPU时间: %d\t当前连续运行时间: %d\t连续就绪时间: %d\t状态: 运行\n",
			temp->PID,temp->ProcessName,temp->Priority,temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime);
	}
	for (temp = MainProcess.FinishedProcessList ; temp != NULL; temp = temp->next)
		printf("PID: %d\t进程名: %s\t优先数: %d\t进程余下时间: %d\t已使用CPU时间: %d\t当前连续运行时间: %d\t连续就绪时间: %d\t状态: 已完成\n",
			temp->PID,temp->ProcessName,temp->Priority,temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime);

	printf("\n");
	/*******************************************/
	//刷新页面
	m_ListTop.UpdateWindow();
	m_List.UpdateWindow();
}

void m_page1::OnBnClickedButton1()
{
	//初始化界面
	if (!NewProcess.FirstCreate)
		NewProcess.Create(IDD_DIALOG3,GetDlgItem(IDC_TAB1));
	NewProcess.ShowWindow(SW_SHOW);
	NewProcess.SetActiveWindow();
	NewProcess.SetWindowText(_T("添加进程"));
	if (!NewProcess.FirstCreate)
	{
		NewProcess.InitialPage();
		NewProcess.FirstCreate = true;
	}
	SetTimer(4,200,NULL);
}

void m_page1::OnBnClickedButton3()
{
	if (MainProcess.ProcessList == NULL)
		AfxMessageBox(_T("请先创建一些进程"));
	else
	{
		//点击了开始运行后就可以开始指挥CPU选取执行适当的进程
		if ( !MainProcess.CPURunState )
		{
			MainProcess.CPURunState = true;	
			SetDlgItemText(IDC_BUTTON3,L"停止CPU"); 
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			RunCPU();
		}
		else
		{
			MainProcess.CPURunState = false;
			SetDlgItemText(IDC_BUTTON3,L"启动CPU");
			if (MainProcess.CPUBusyState == true)
				GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
				EndCPU();
		}
	}
}

int m_page1::RunCPU()
{
	PCB * chosenProcess;
	//如果已经创建了列表就开始进行操作
	if (MainProcess.ProcessList == NULL)
		return 0;

	//设置定时器
	SetTimer(3,MainProcess.TIMEPIECE,NULL);
	
	//先运行一次
	if (MainProcess.CPUBusyState){
		//选取CPU需要处理的进程
		chosenProcess = MainProcess.ProcessRun();
		
		//更新两个List
		UpdateList(chosenProcess);

		//修改进程的信息
		MainProcess.ChangeProcess(chosenProcess);
		}
		else
		{
			m_ListTop.DeleteAllItems();//删除原来的进程信息
			//刷新页面
			m_ListTop.UpdateWindow();
			m_List.UpdateWindow();
			MainProcess.CPURunState = false;//cpu未运行了
			//改变按钮的状态，为下一次运行新的进程做准备
			SetDlgItemText(IDC_BUTTON3,L"启动CPU");
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			//杀死定时器
			KillTimer(3);
		}

	return 0;
}

int m_page1::EndCPU()
{
	//MainProcess.CPUBusyState = false;//停止CPU的忙碌状态，变成空闲
	KillTimer(3);
	return 0;
}

void m_page1::OnTimer(UINT_PTR nIDEvent)
{
	PCB *chosenProcess;

	if (nIDEvent == 3)
	{
		if (MainProcess.CPUBusyState){
		//选取CPU需要处理的进程
		chosenProcess = MainProcess.ProcessRun();
		
		//更新两个List
		UpdateList(chosenProcess);

		//修改进程的信息
		MainProcess.ChangeProcess(chosenProcess);
		}
		else
		{
			m_ListTop.DeleteAllItems();//删除原来的进程信息
			//刷新页面
			m_ListTop.UpdateWindow();
			m_List.UpdateWindow();
			MainProcess.CPURunState = false;//cpu未运行了
			//改变按钮的状态，为下一次运行新的进程做准备
			SetDlgItemText(IDC_BUTTON3,L"启动CPU");
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			//杀死定时器
			KillTimer(3);
		}
	}
	else if (nIDEvent == 4)
	{
		if (! NewProcess.Exist)
		{
			PCB * temp;
			//将新增的进程信息补全
			for(temp = NewProcess.NewProcessList; temp != NULL; temp = temp->next)
			{	
				temp->EnterTime = MainProcess.AccelerateTime;
				MainProcess.ProcessNum ++;
				temp->PID = MainProcess.ProcessNum;
				temp->ReadyTime = temp->RunTime = temp->UsedTime = 0;
				temp->State = 'W';
			}
			//形成进程链表
			if (MainProcess.ProcessList == NULL)
			{
				MainProcess.ProcessList = NewProcess.NewProcessList;
			}
			else
			{
			PCB * tempnow;
			for (temp = MainProcess.ProcessList ; temp != NULL ; temp = temp->next)
				tempnow = temp;
			tempnow->next = NewProcess.NewProcessList;
			}
			//如果没有在启动CPU才会直接更新列表，否则会在运行时再更新
			//更新列表
			if (!MainProcess.CPURunState)
			{
				m_List.DeleteAllItems();//删除就绪表的内容
				m_ListTop.DeleteAllItems();//删除运行表的内容
				for(temp = MainProcess.ProcessList ; temp != NULL; temp = temp->next)
				{
					temp->State = 'W';//全部变成等待状态
					AddProcessIntoList(temp->PID,temp->ProcessName,temp->Priority,temp->EnterTime,
													temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime,temp->State);	
				}
			}
			//创建了List
			MainProcess.CreateList(MainProcess.ProcessNum);
			//关闭这个定时器
			KillTimer(4);
			//初始化弹窗的一些项，为下一次处理做准备
			NewProcess.Exist = true;
			//NewProcess.NewProcessList = (struct PCB *)malloc(sizeof(PCB));
			NewProcess.NewProcessList = NULL;
		}
	}
	else
	{
		KillTimer(nIDEvent);
	}
}

void m_page1::OnBnClickedButton2()
{
	PCB *chosenProcess;
	// 步进完成进程调度
	if (MainProcess.CPUBusyState){
		//选取CPU需要处理的进程
		chosenProcess = MainProcess.ProcessRun();
		
		//更新两个List
		UpdateList(chosenProcess);

		//修改进程的信息
		MainProcess.ChangeProcess(chosenProcess);
		}
	else
		{
			m_ListTop.DeleteAllItems();//删除原来的进程信息
			//刷新页面
			m_ListTop.UpdateWindow();
			m_List.UpdateWindow();
		}
}
