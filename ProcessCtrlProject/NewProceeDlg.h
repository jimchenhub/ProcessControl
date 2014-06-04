#pragma once
#include "afxcmn.h"
#include "m_page1.h"
// CNewProceeDlg 对话框

class CNewProceeDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewProceeDlg)

public:
	CNewProceeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewProceeDlg();
	void InitialPage();
	PCB * NewProcessList;
	void AddProcessIntoNewProcessList(char ProcessName[50], int Priority, int AllTime);
	bool Exist;//当前窗口是否存在
	bool FirstCreate;//记录是否已经创建过这个窗口

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListNewProcess;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
