#pragma once
#include "afxcmn.h"
#include "m_page1.h"
// CNewProceeDlg �Ի���

class CNewProceeDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewProceeDlg)

public:
	CNewProceeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewProceeDlg();
	void InitialPage();
	PCB * NewProcessList;
	void AddProcessIntoNewProcessList(char ProcessName[50], int Priority, int AllTime);
	bool Exist;//��ǰ�����Ƿ����
	bool FirstCreate;//��¼�Ƿ��Ѿ��������������

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListNewProcess;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
