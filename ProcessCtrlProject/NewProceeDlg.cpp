// NewProceeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessCtrlProject.h"
#include "NewProceeDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include<CString>
using namespace std;

// CNewProceeDlg �Ի���

IMPLEMENT_DYNAMIC(CNewProceeDlg, CDialog)

CNewProceeDlg::CNewProceeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProceeDlg::IDD, pParent)
{
	NewProcessList = NULL;//�´����Ľ���Ϊ��
	Exist = true;//��ʼ������ʱ�򴰿���Ȼ����
	FirstCreate = false;//�ʼû�д��� 
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


// CNewProceeDlg ��Ϣ�������

void CNewProceeDlg::InitialPage()
{
	//���ø�ʽ
	m_ListNewProcess.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ  
	m_ListNewProcess.SetExtendedStyle(m_ListNewProcess.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // �����+��ѡ��  
	//�����ͷ����ͷ��ÿһ�Ҫ����
	m_ListNewProcess.InsertColumn(0,_T("������"),LVCFMT_CENTER);
	m_ListNewProcess.InsertColumn(1,_T("���ȼ�"),LVCFMT_CENTER);
	m_ListNewProcess.InsertColumn(2,_T("����ʱ��"),LVCFMT_CENTER);
	//����ÿһ�еĿ��
	CRect rect;  
	m_ListNewProcess.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
	m_ListNewProcess.SetColumnWidth(0, rect.Width() *40/ 100);  
	m_ListNewProcess.SetColumnWidth(1, rect.Width() *30/ 100);
	m_ListNewProcess.SetColumnWidth(2, rect.Width() *30/ 100);

}


void CNewProceeDlg::OnBnClickedButton1()
{
	int Priority = 0;
	int AllTime = 0;
	//��ȡ�༭������Ϣ
	CString s_ProcessName;
	CString s_Priority;
	CString s_AllTime;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(s_ProcessName);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(s_Priority);
	GetDlgItem(IDC_EDIT3)->GetWindowTextW(s_AllTime);
	//���༭������Ϣ
	//���û����д���������򲻽�������Ĳ���
	if (s_ProcessName.IsEmpty())
	{
		AfxMessageBox(_T("����д������"));
	}
	else if (s_ProcessName.GetLength() >= 50)
	{
		AfxMessageBox(_T("������̫��"));
	}
	//�����д�˽��̣������������ӽ���
	//����Ϣ��ֵ��һ��PCB�����в�����ӵ��б���
	else
	{
		//����PCB
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
		//�����б�
		AddProcessIntoNewProcessList(newProcess->ProcessName, newProcess->Priority, newProcess->AllTime);
		m_ListNewProcess.UpdateWindow();
		SetDlgItemText(IDC_EDIT1, _T(""));//��������
		SetDlgItemText(IDC_EDIT2, _T(""));
		SetDlgItemText(IDC_EDIT3, _T(""));
	}
}


void CNewProceeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Exist = false;
	//�������б�
	SetDlgItemText(IDC_EDIT1, _T(""));//��������
	SetDlgItemText(IDC_EDIT2, _T(""));
	SetDlgItemText(IDC_EDIT3, _T(""));
	m_ListNewProcess.DeleteAllItems();
	CDialog::OnOK();
}


void CNewProceeDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT1, _T(""));//��������
	SetDlgItemText(IDC_EDIT2, _T(""));
	SetDlgItemText(IDC_EDIT3, _T(""));
	m_ListNewProcess.DeleteAllItems();
	//���Ҫ��ӵĽ����б�
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