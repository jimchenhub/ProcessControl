// m_page1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessCtrlProject.h"
#include "m_page1.h"
#include "afxdialogex.h"
#include "ProcessCtrlProjectDlg.h"
#include "NewProceeDlg.h"

//ȫ�ֵ�MainProcess
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
	/*********��ʼ������Ľ����б�*********/
	//���ø�ʽ
	m_List.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ  
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // �����+��ѡ��  
	//�����ͷ����ͷ��ÿһ�Ҫ����
	m_List.InsertColumn(0,_T("PID"),LVCFMT_CENTER);  
	m_List.InsertColumn(1,_T("������"),LVCFMT_CENTER);
	m_List.InsertColumn(2,_T("���ȼ�"),LVCFMT_CENTER);
	m_List.InsertColumn(3,_T("����ʱ��"),LVCFMT_CENTER);
	m_List.InsertColumn(4,_T("��������ʱ��"),LVCFMT_CENTER);
	m_List.InsertColumn(5,_T("������ʱ��"),LVCFMT_CENTER);
	m_List.InsertColumn(6,_T("��������ʱ��"),LVCFMT_CENTER);
	m_List.InsertColumn(7,_T("��������ʱ��"),LVCFMT_CENTER);
	m_List.InsertColumn(8,_T("״̬"),LVCFMT_CENTER);
	//����ÿһ�еĿ��
	CRect rect;  
	m_List.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
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

	/*********��ʼ����������ִ�еĽ����б�*********/
	//���ø�ʽ
	m_ListTop.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ  
	m_ListTop.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // �����+��ѡ��  
	//�����ͷ����ͷ��ÿһ�Ҫ����
	m_ListTop.InsertColumn(0,_T("PID"),LVCFMT_CENTER);  
	m_ListTop.InsertColumn(1,_T("������"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(2,_T("���ȼ�"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(3,_T("����ʱ��"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(4,_T("��������ʱ��"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(5,_T("������ʱ��"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(6,_T("��������ʱ��"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(7,_T("��������ʱ��"),LVCFMT_CENTER);
	m_ListTop.InsertColumn(8,_T("״̬"),LVCFMT_CENTER);
	//����ÿһ�еĿ��
	CRect rectTop;  
	m_ListTop.GetClientRect(rectTop); //��õ�ǰ�ͻ�����Ϣ  
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
	//ʹ��_itow_s����ת��int�Ͳ���
	wchar_t ch[5];
	_itow_s( PID, ch, 5, 10);
	m_List.InsertItem(0, ch);
	//ʹ��A2CW������char* ת��LPCWSTR
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
		m_List.SetItemText(0, 8, _T("����"));
	else if (State == 'W')
		m_List.SetItemText(0, 8, _T("����"));

}

void m_page1::AddProcessIntoListTop( int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State)
{
	//ʹ��_itow_s����ת��int�Ͳ���
	wchar_t ch[5];
	_itow_s( PID, ch, 5, 10);
	m_ListTop.InsertItem(0, ch);
	//ʹ��A2CW������char* ת��LPCWSTR
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
		m_ListTop.SetItemText(0, 8, _T("����"));
	else if (State == 'W')
		m_ListTop.SetItemText(0, 8, _T("����"));
}

void m_page1::UpdateList(PCB *chosenProcess)
{
	PCB *temp;

	/**********���¾�����**************/
	m_List.DeleteAllItems();//ɾ�������������
	for(temp = MainProcess.ProcessList ; temp != NULL; temp = temp->next)
		if (temp != chosenProcess)
		{
			temp->State = 'W';//�����о������̵�״̬��ɵȴ�
			AddProcessIntoList(temp->PID,temp->ProcessName,temp->Priority,temp->EnterTime,
			temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime,temp->State);
		}
	/**********�������б�***************/
	m_ListTop.DeleteAllItems();//ɾ��ԭ���Ľ�����Ϣ
	chosenProcess->State = 'R';//ѡ�еĽ��̱������״̬
	AddProcessIntoListTop(chosenProcess->PID,chosenProcess->ProcessName,chosenProcess->Priority,chosenProcess->EnterTime,
		chosenProcess->AllTime,chosenProcess->UsedTime,chosenProcess->RunTime,chosenProcess->ReadyTime,chosenProcess->State);
	/***********��ӡ���н���****************/
	printf("��%d������Ƭ��\n",MainProcess.AccelerateTime+1);
	for (temp = MainProcess.ProcessList; temp != NULL; temp = temp->next)
	{
		if (temp->State == 'W')
			printf("PID: %d\t������: %s\t������: %d\t��������ʱ��: %d\t��ʹ��CPUʱ��: %d\t��ǰ��������ʱ��: %d\t��������ʱ��: %d\t״̬: ����\n",
			temp->PID,temp->ProcessName,temp->Priority,temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime);
		else
			printf("PID: %d\t������: %s\t������: %d\t��������ʱ��: %d\t��ʹ��CPUʱ��: %d\t��ǰ��������ʱ��: %d\t��������ʱ��: %d\t״̬: ����\n",
			temp->PID,temp->ProcessName,temp->Priority,temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime);
	}
	for (temp = MainProcess.FinishedProcessList ; temp != NULL; temp = temp->next)
		printf("PID: %d\t������: %s\t������: %d\t��������ʱ��: %d\t��ʹ��CPUʱ��: %d\t��ǰ��������ʱ��: %d\t��������ʱ��: %d\t״̬: �����\n",
			temp->PID,temp->ProcessName,temp->Priority,temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime);

	printf("\n");
	/*******************************************/
	//ˢ��ҳ��
	m_ListTop.UpdateWindow();
	m_List.UpdateWindow();
}

void m_page1::OnBnClickedButton1()
{
	//��ʼ������
	if (!NewProcess.FirstCreate)
		NewProcess.Create(IDD_DIALOG3,GetDlgItem(IDC_TAB1));
	NewProcess.ShowWindow(SW_SHOW);
	NewProcess.SetActiveWindow();
	NewProcess.SetWindowText(_T("��ӽ���"));
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
		AfxMessageBox(_T("���ȴ���һЩ����"));
	else
	{
		//����˿�ʼ���к�Ϳ��Կ�ʼָ��CPUѡȡִ���ʵ��Ľ���
		if ( !MainProcess.CPURunState )
		{
			MainProcess.CPURunState = true;	
			SetDlgItemText(IDC_BUTTON3,L"ֹͣCPU"); 
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			RunCPU();
		}
		else
		{
			MainProcess.CPURunState = false;
			SetDlgItemText(IDC_BUTTON3,L"����CPU");
			if (MainProcess.CPUBusyState == true)
				GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
				EndCPU();
		}
	}
}

int m_page1::RunCPU()
{
	PCB * chosenProcess;
	//����Ѿ��������б�Ϳ�ʼ���в���
	if (MainProcess.ProcessList == NULL)
		return 0;

	//���ö�ʱ��
	SetTimer(3,MainProcess.TIMEPIECE,NULL);
	
	//������һ��
	if (MainProcess.CPUBusyState){
		//ѡȡCPU��Ҫ����Ľ���
		chosenProcess = MainProcess.ProcessRun();
		
		//��������List
		UpdateList(chosenProcess);

		//�޸Ľ��̵���Ϣ
		MainProcess.ChangeProcess(chosenProcess);
		}
		else
		{
			m_ListTop.DeleteAllItems();//ɾ��ԭ���Ľ�����Ϣ
			//ˢ��ҳ��
			m_ListTop.UpdateWindow();
			m_List.UpdateWindow();
			MainProcess.CPURunState = false;//cpuδ������
			//�ı䰴ť��״̬��Ϊ��һ�������µĽ�����׼��
			SetDlgItemText(IDC_BUTTON3,L"����CPU");
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			//ɱ����ʱ��
			KillTimer(3);
		}

	return 0;
}

int m_page1::EndCPU()
{
	//MainProcess.CPUBusyState = false;//ֹͣCPU��æµ״̬����ɿ���
	KillTimer(3);
	return 0;
}

void m_page1::OnTimer(UINT_PTR nIDEvent)
{
	PCB *chosenProcess;

	if (nIDEvent == 3)
	{
		if (MainProcess.CPUBusyState){
		//ѡȡCPU��Ҫ����Ľ���
		chosenProcess = MainProcess.ProcessRun();
		
		//��������List
		UpdateList(chosenProcess);

		//�޸Ľ��̵���Ϣ
		MainProcess.ChangeProcess(chosenProcess);
		}
		else
		{
			m_ListTop.DeleteAllItems();//ɾ��ԭ���Ľ�����Ϣ
			//ˢ��ҳ��
			m_ListTop.UpdateWindow();
			m_List.UpdateWindow();
			MainProcess.CPURunState = false;//cpuδ������
			//�ı䰴ť��״̬��Ϊ��һ�������µĽ�����׼��
			SetDlgItemText(IDC_BUTTON3,L"����CPU");
			GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
			//ɱ����ʱ��
			KillTimer(3);
		}
	}
	else if (nIDEvent == 4)
	{
		if (! NewProcess.Exist)
		{
			PCB * temp;
			//�������Ľ�����Ϣ��ȫ
			for(temp = NewProcess.NewProcessList; temp != NULL; temp = temp->next)
			{	
				temp->EnterTime = MainProcess.AccelerateTime;
				MainProcess.ProcessNum ++;
				temp->PID = MainProcess.ProcessNum;
				temp->ReadyTime = temp->RunTime = temp->UsedTime = 0;
				temp->State = 'W';
			}
			//�γɽ�������
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
			//���û��������CPU�Ż�ֱ�Ӹ����б������������ʱ�ٸ���
			//�����б�
			if (!MainProcess.CPURunState)
			{
				m_List.DeleteAllItems();//ɾ�������������
				m_ListTop.DeleteAllItems();//ɾ�����б������
				for(temp = MainProcess.ProcessList ; temp != NULL; temp = temp->next)
				{
					temp->State = 'W';//ȫ����ɵȴ�״̬
					AddProcessIntoList(temp->PID,temp->ProcessName,temp->Priority,temp->EnterTime,
													temp->AllTime,temp->UsedTime,temp->RunTime,temp->ReadyTime,temp->State);	
				}
			}
			//������List
			MainProcess.CreateList(MainProcess.ProcessNum);
			//�ر������ʱ��
			KillTimer(4);
			//��ʼ��������һЩ�Ϊ��һ�δ�����׼��
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
	// ������ɽ��̵���
	if (MainProcess.CPUBusyState){
		//ѡȡCPU��Ҫ����Ľ���
		chosenProcess = MainProcess.ProcessRun();
		
		//��������List
		UpdateList(chosenProcess);

		//�޸Ľ��̵���Ϣ
		MainProcess.ChangeProcess(chosenProcess);
		}
	else
		{
			m_ListTop.DeleteAllItems();//ɾ��ԭ���Ľ�����Ϣ
			//ˢ��ҳ��
			m_ListTop.UpdateWindow();
			m_List.UpdateWindow();
		}
}
