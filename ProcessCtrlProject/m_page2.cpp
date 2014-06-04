// m_page2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProcessCtrlProject.h"
#include "m_page2.h"
#include "afxdialogex.h"


// m_page2 �Ի���

IMPLEMENT_DYNAMIC(m_page2, CDialog)

m_page2::m_page2(CWnd* pParent /*=NULL*/)
	: CDialog(m_page2::IDD, pParent)
{
}

m_page2::~m_page2()
{
}

void m_page2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List2);
}


BEGIN_MESSAGE_MAP(m_page2, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &m_page2::OnLvnItemchangedList1)
END_MESSAGE_MAP()

//��ʼ��page2��ҳ�溯��
void m_page2::InitialTabPage()
{
	//���ø�ʽ
	m_List2.ModifyStyle( 0, LVS_REPORT );               // ����ģʽ  
	m_List2.SetExtendedStyle(m_List2.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);  // �����+��ѡ��  
	//�����ͷ����ͷ��ÿһ�Ҫ����
	m_List2.InsertColumn(0,_T("PID"),LVCFMT_CENTER);  
	m_List2.InsertColumn(1,_T("������"),LVCFMT_CENTER);
	m_List2.InsertColumn(2,_T("���ȼ�"),LVCFMT_CENTER);
	m_List2.InsertColumn(3,_T("����ʱ��"),LVCFMT_CENTER);
	m_List2.InsertColumn(4,_T("����ʱ��"),LVCFMT_CENTER);
	m_List2.InsertColumn(5,_T("�˳�ʱ��"),LVCFMT_CENTER);
	m_List2.InsertColumn(6,_T("��Ȩ������תʱ��"),LVCFMT_CENTER);
	m_List2.InsertColumn(7,_T("״̬"),LVCFMT_CENTER);
	//����ÿһ�еĿ��
	CRect rect;  
	m_List2.GetClientRect(rect); //��õ�ǰ�ͻ�����Ϣ  
	m_List2.SetColumnWidth(0, rect.Width()*8 / 100); 
	m_List2.SetColumnWidth(1, rect.Width() *12/ 100);  
	m_List2.SetColumnWidth(2, rect.Width() *12/ 100);
	m_List2.SetColumnWidth(3, rect.Width() *12/ 100);
	m_List2.SetColumnWidth(4, rect.Width() *12/ 100);
	m_List2.SetColumnWidth(5, rect.Width() *12/ 100);
	m_List2.SetColumnWidth(6, rect.Width() *20/ 100);
	m_List2.SetColumnWidth(7, rect.Width() *12/ 100);
}

void m_page2::AddProcessIntoFinishedList( int PID,char ProcessName[50], int Priority, int EnterTime, int UsedTime, int EndTime)
{
	//ʹ��_itow_s����ת��int�Ͳ���
	wchar_t ch[5]; 
	_itow_s( PID, ch, 5, 10); 
	m_List2.InsertItem(0, ch);
	//ʹ��A2CW������char* ת��LPCWSTR
	CString str = CString(ProcessName);  
	USES_CONVERSION;
	LPCWSTR wszProcessName = A2CW(W2A(str));  
	str.ReleaseBuffer(); 
	m_List2.SetItemText(0, 1, wszProcessName); 
	/***********/
	_itow_s( Priority, ch, 5, 10);
	m_List2.SetItemText(0, 2, ch); 
	/***********/
	_itow_s( EnterTime, ch, 5, 10);
	m_List2.SetItemText(0, 3, ch);
	/***********/
	_itow_s( UsedTime, ch, 5, 10);
	m_List2.SetItemText(0, 4, ch);
	/***********/
	_itow_s( EndTime, ch, 5, 10);
	m_List2.SetItemText(0, 5, ch);
	/***********/
	double Weight = (double)(EndTime - EnterTime)/UsedTime;
	wchar_t *t=new wchar_t[64];
	swprintf(t,64,L"%f",Weight);
	m_List2.SetItemText(0, 6, t);
	delete(t);
	/***********/
	m_List2.SetItemText(0, 7, L"���"); 
}

void m_page2::RefreshPage(PCB * FinishedProcessList)
{
	double WeightSum = 0;
	PCB * temp;
	m_List2.DeleteAllItems();
	for (temp = FinishedProcessList; temp != NULL; temp = temp->next)
	{
		AddProcessIntoFinishedList(temp->PID,temp->ProcessName,temp->Priority,temp->EnterTime,temp->UsedTime,temp->EndTime);
		WeightSum += (double)(temp->EndTime - temp->EnterTime)/temp->UsedTime;
	}
	m_List2.UpdateWindow();
	int Rows = m_List2.GetItemCount();
	if (Rows != 0)
	{
		wchar_t *t=new wchar_t[64];
		swprintf(t,64,L"%f",WeightSum/Rows);
		GetDlgItem(IDC_STATICWeightSum)->SetWindowText(t);
		delete(t);
	}
}

void m_page2::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
