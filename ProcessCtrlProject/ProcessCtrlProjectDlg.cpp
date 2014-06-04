
// ProcessCtrlProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ProcessCtrlProject.h"
#include "ProcessCtrlProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


PCB *FinishedProcessListAll = NULL;
int ProcessNumAll = 0;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProcessCtrlProjectDlg 对话框




CProcessCtrlProjectDlg::CProcessCtrlProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessCtrlProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//构造函数初始化
	TIMEPIECE = 1000;//时间片时间
	DELETEPRI = 3;//每运行一个时间片运行进程减少的优先数
	ADDPRI =1;//没运行一个时间片等待进程增加的优先数
	ProcessList = NULL;//初始化PCB队列
	FinishedProcessList = NULL;//初始化已完成的进程为空
	AccelerateTime = 0;//当前时间，单位是CPU时间片
	CPUBusyState = false;//初始是没有进程要执行
	CPURunState = false;//初始默认不允许cpu工作
	ProcessNum = 0;//初始的进程数是0
}

void CProcessCtrlProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CProcessCtrlProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CProcessCtrlProjectDlg::OnTcnSelchangeTab1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProcessCtrlProjectDlg 消息处理程序

BOOL CProcessCtrlProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	void InitialTabPage();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	/*************************************/
	SetWindowText(_T("进程管理器"));

	m_TabCtrl.InsertItem(0,_T("当前进程"));
	m_TabCtrl.InsertItem(1,_T("已结束"));
    
	//设置IDC_TAB1为父窗口
	page1.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB1));
	page2.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB1));

	//获得IDC_TABTEST客户区大小
	CRect rc;
	m_TabCtrl.GetClientRect(&rc);
    
	//调整子对话框在父窗口中的位置
	rc.top += 22;
	rc.bottom -= 2;
	rc.left += 1;
	rc.right -= 3;

	//设置子对话框尺寸并移动到指定位置
	page1.MoveWindow(&rc);
	page2.MoveWindow(&rc);

	//分别设置隐藏和显示
	page1.ShowWindow(true);
	page2.ShowWindow(false);

	//初始化页面
	page1.InitialTabPage();
	page2.InitialTabPage();

	//设置默认的选项卡
	m_TabCtrl.SetCurSel(0);

	//打开要写入的文件
	/*
	CString str; //获取系统时间 　　
	CTime tm;
	tm=CTime::GetCurrentTime(); 
	str=tm.Format("%X");
	CString Name;
	CString Part1("./进程调度记录");
	CString Part2(".txt");
	Name.Append(Part1);
	Name.Append(str);
	Name.Append(Part2);//形成完整的路径和名字
	int nLength = Name.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP,0,Name,nLength,NULL,0,NULL,NULL);
	char* TrueName = new char[nBytes+1];
	memset(TrueName,0, nLength+1);
	WideCharToMultiByte(CP_OEMCP, 0, Name, nLength, TrueName, nBytes, NULL, NULL); 
	TrueName[nBytes] = 0;
	*/
	freopen("./进程调度记录.txt","w",stdout); 
	printf("调度开始\n\n");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProcessCtrlProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProcessCtrlProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProcessCtrlProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//进行Tab标签之间的切换
void CProcessCtrlProjectDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int CurSel = m_TabCtrl.GetCurSel();

    switch(CurSel)
    {
    case 0:
		KillTimer(1);
        page1.ShowWindow(true);
        page2.ShowWindow(false);
        break;
    case 1:
		SetTimer(1,1000,NULL);
        page1.ShowWindow(false);
        page2.ShowWindow(true);
		if (FinishedProcessListAll != NULL)
		{
			page2.RefreshPage(FinishedProcessListAll);
			//如果所有进程都结束的话就可以不再刷新了
			int num = 0;
			for (PCB * temp = FinishedProcessListAll ; temp != NULL ; temp = temp->next)
				num ++;
			if (num == ProcessNumAll )
				KillTimer(1);
		}
        break;
    }
	*pResult = 0;
}

void CProcessCtrlProjectDlg::CreateList(int num)
{
	ProcessNumAll += num;

	//由于创建了进程，所以CPU需要执行
	CPUBusyState = true;
}

//进程执行函数，选取需要执行的进程，即优先数最高的进程
PCB *CProcessCtrlProjectDlg::ProcessRun()
{
	PCB * temp;
	PCB *chosenProcess = ProcessList;
	
	//选取出需要执行的进程
	for (temp = ProcessList ; temp != NULL ; temp = temp->next)
		if (temp->EnterTime <= AccelerateTime && temp->Priority > chosenProcess->Priority)
			chosenProcess = temp;
	return chosenProcess;
}

void CProcessCtrlProjectDlg::FreeProcess(PCB *finishedProcess)
{
	finishedProcess->EndTime = AccelerateTime;
	finishedProcess->next = FinishedProcessListAll;
	FinishedProcessListAll = finishedProcess;
	//重新创建一个新的进程，传给本身类的链表，以方便每次结束后
	//打印所有进程的状态与参数
	PCB * finishedOne = (struct PCB *)malloc(sizeof( struct PCB));
	//赋值
	finishedOne->AllTime = finishedProcess->AllTime;
	finishedOne->EndTime = finishedProcess->EndTime;
	finishedOne->EnterTime = finishedProcess->EnterTime;
	finishedOne->PID = finishedProcess->PID;
	finishedOne->Priority = finishedProcess->Priority;
	finishedOne->ReadyTime = finishedProcess->ReadyTime;
	finishedOne->RunTime = finishedProcess->RunTime;
	finishedOne->State = finishedProcess->State;
	finishedOne->UsedTime = finishedProcess->UsedTime;
	for (int i = 0 ; i < 50; i++)
		finishedOne->ProcessName[i] = finishedProcess->ProcessName[i];
	finishedOne->next = FinishedProcessList;
	FinishedProcessList = finishedOne;
}

//删除进程链表中的一个进程
void CProcessCtrlProjectDlg::DeleteProcess(PCB *chosenProcess)
{
	PCB *temp;
	PCB * tempnow;

	chosenProcess->State = 'D';
	//删除这个节点
	if (chosenProcess == ProcessList)
	{
		temp = ProcessList->next;
		FreeProcess(ProcessList);
		ProcessList = temp;
	}
	else
	{
		//找到chosenProcess前面的那个结点
		for (temp = ProcessList; temp != chosenProcess; temp = temp->next)
			tempnow = temp;
		//删除结点
		tempnow->next = temp->next;
		FreeProcess(temp);
	}
	//如果删除后ProcessList变为空链表，则通知CPU没有进程需要执行了
	if (ProcessList == NULL)
		CPUBusyState = false;
}

//每运行完一个时间片要对每个进程的时间优先数等参数进行调整
void CProcessCtrlProjectDlg::ChangeProcess(PCB *chosenProcess)
{
	PCB * temp;
	
	AccelerateTime++;
	for (temp = ProcessList ; temp != NULL ; temp = temp->next)
	{
		if (temp == chosenProcess)
		{
			temp->AllTime --;
			temp->Priority -= DELETEPRI;
			temp->UsedTime ++;//使用CPU时间
			temp->RunTime ++;//连续运行时间
			temp->State = 'R';//状态是正在运行
			temp->ReadyTime = 0;//连续等待时间为0
		}
		else
		{
			temp->Priority += ADDPRI;
			temp->ReadyTime ++;
			temp->RunTime = 0;
			temp->State = 'W';
		}
	}
	//如果AllTime为0，即如果已经运行完毕
	if (chosenProcess->AllTime == 0)
		DeleteProcess(chosenProcess);
}

void CProcessCtrlProjectDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		if (FinishedProcessListAll != NULL)
		{
			page2.RefreshPage(FinishedProcessListAll);
			//如果所有进程都结束的话就可以不再刷新了
			int num = 0;
			for (PCB * temp = FinishedProcessListAll ; temp != NULL ; temp = temp->next)
				num ++;
			if (num == ProcessNumAll )
				KillTimer(1);
		}
	}
	else
	{
		KillTimer(nIDEvent);
	}
}
