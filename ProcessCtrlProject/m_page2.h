#pragma once
#include "afxcmn.h"
#include "m_page1.h"

// m_page2 �Ի���

class m_page2 : public CDialog
{
	DECLARE_DYNAMIC(m_page2)
	 
public:
	m_page2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_page2();
	void InitialTabPage(); //��ʼ��ҳ��ĺ���
	void RefreshPage(PCB *FinishedProcessList);//ˢ��ҳ��
	void AddProcessIntoFinishedList( int PID,char ProcessName[50], int Priority, int EnterTime, int UsedTime, int EndTime);

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List2;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
