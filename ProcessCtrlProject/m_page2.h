#pragma once
#include "afxcmn.h"
#include "m_page1.h"

// m_page2 对话框

class m_page2 : public CDialog
{
	DECLARE_DYNAMIC(m_page2)
	 
public:
	m_page2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_page2();
	void InitialTabPage(); //初始化页面的函数
	void RefreshPage(PCB *FinishedProcessList);//刷新页面
	void AddProcessIntoFinishedList( int PID,char ProcessName[50], int Priority, int EnterTime, int UsedTime, int EndTime);

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List2;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
