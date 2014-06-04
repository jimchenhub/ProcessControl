
// ProcessCtrlProjectDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CProcessCtrlProjectDlg �Ի���




CProcessCtrlProjectDlg::CProcessCtrlProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessCtrlProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//���캯����ʼ��
	TIMEPIECE = 1000;//ʱ��Ƭʱ��
	DELETEPRI = 3;//ÿ����һ��ʱ��Ƭ���н��̼��ٵ�������
	ADDPRI =1;//û����һ��ʱ��Ƭ�ȴ��������ӵ�������
	ProcessList = NULL;//��ʼ��PCB����
	FinishedProcessList = NULL;//��ʼ������ɵĽ���Ϊ��
	AccelerateTime = 0;//��ǰʱ�䣬��λ��CPUʱ��Ƭ
	CPUBusyState = false;//��ʼ��û�н���Ҫִ��
	CPURunState = false;//��ʼĬ�ϲ�����cpu����
	ProcessNum = 0;//��ʼ�Ľ�������0
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


// CProcessCtrlProjectDlg ��Ϣ�������

BOOL CProcessCtrlProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	void InitialTabPage();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	/*************************************/
	SetWindowText(_T("���̹�����"));

	m_TabCtrl.InsertItem(0,_T("��ǰ����"));
	m_TabCtrl.InsertItem(1,_T("�ѽ���"));
    
	//����IDC_TAB1Ϊ������
	page1.Create(IDD_DIALOG1,GetDlgItem(IDC_TAB1));
	page2.Create(IDD_DIALOG2,GetDlgItem(IDC_TAB1));

	//���IDC_TABTEST�ͻ�����С
	CRect rc;
	m_TabCtrl.GetClientRect(&rc);
    
	//�����ӶԻ����ڸ������е�λ��
	rc.top += 22;
	rc.bottom -= 2;
	rc.left += 1;
	rc.right -= 3;

	//�����ӶԻ���ߴ粢�ƶ���ָ��λ��
	page1.MoveWindow(&rc);
	page2.MoveWindow(&rc);

	//�ֱ��������غ���ʾ
	page1.ShowWindow(true);
	page2.ShowWindow(false);

	//��ʼ��ҳ��
	page1.InitialTabPage();
	page2.InitialTabPage();

	//����Ĭ�ϵ�ѡ�
	m_TabCtrl.SetCurSel(0);

	//��Ҫд����ļ�
	/*
	CString str; //��ȡϵͳʱ�� ����
	CTime tm;
	tm=CTime::GetCurrentTime(); 
	str=tm.Format("%X");
	CString Name;
	CString Part1("./���̵��ȼ�¼");
	CString Part2(".txt");
	Name.Append(Part1);
	Name.Append(str);
	Name.Append(Part2);//�γ�������·��������
	int nLength = Name.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP,0,Name,nLength,NULL,0,NULL,NULL);
	char* TrueName = new char[nBytes+1];
	memset(TrueName,0, nLength+1);
	WideCharToMultiByte(CP_OEMCP, 0, Name, nLength, TrueName, nBytes, NULL, NULL); 
	TrueName[nBytes] = 0;
	*/
	freopen("./���̵��ȼ�¼.txt","w",stdout); 
	printf("���ȿ�ʼ\n\n");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProcessCtrlProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProcessCtrlProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����Tab��ǩ֮����л�
void CProcessCtrlProjectDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			//������н��̶������Ļ��Ϳ��Բ���ˢ����
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

	//���ڴ����˽��̣�����CPU��Ҫִ��
	CPUBusyState = true;
}

//����ִ�к�����ѡȡ��Ҫִ�еĽ��̣�����������ߵĽ���
PCB *CProcessCtrlProjectDlg::ProcessRun()
{
	PCB * temp;
	PCB *chosenProcess = ProcessList;
	
	//ѡȡ����Ҫִ�еĽ���
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
	//���´���һ���µĽ��̣�����������������Է���ÿ�ν�����
	//��ӡ���н��̵�״̬�����
	PCB * finishedOne = (struct PCB *)malloc(sizeof( struct PCB));
	//��ֵ
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

//ɾ�����������е�һ������
void CProcessCtrlProjectDlg::DeleteProcess(PCB *chosenProcess)
{
	PCB *temp;
	PCB * tempnow;

	chosenProcess->State = 'D';
	//ɾ������ڵ�
	if (chosenProcess == ProcessList)
	{
		temp = ProcessList->next;
		FreeProcess(ProcessList);
		ProcessList = temp;
	}
	else
	{
		//�ҵ�chosenProcessǰ����Ǹ����
		for (temp = ProcessList; temp != chosenProcess; temp = temp->next)
			tempnow = temp;
		//ɾ�����
		tempnow->next = temp->next;
		FreeProcess(temp);
	}
	//���ɾ����ProcessList��Ϊ��������֪ͨCPUû�н�����Ҫִ����
	if (ProcessList == NULL)
		CPUBusyState = false;
}

//ÿ������һ��ʱ��ƬҪ��ÿ�����̵�ʱ���������Ȳ������е���
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
			temp->UsedTime ++;//ʹ��CPUʱ��
			temp->RunTime ++;//��������ʱ��
			temp->State = 'R';//״̬����������
			temp->ReadyTime = 0;//�����ȴ�ʱ��Ϊ0
		}
		else
		{
			temp->Priority += ADDPRI;
			temp->ReadyTime ++;
			temp->RunTime = 0;
			temp->State = 'W';
		}
	}
	//���AllTimeΪ0��������Ѿ��������
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
			//������н��̶������Ļ��Ϳ��Բ���ˢ����
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
