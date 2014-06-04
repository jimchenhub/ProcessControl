#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// m_page1 �Ի���
struct PCB{
		int PID; //����ID
		char ProcessName[50];//������
		int Priority;//����������
		int EnterTime;//����ʱ��
		int AllTime;//��������ʱ��
		int UsedTime;//��ʹ��CPUʱ��
		int RunTime;//��ǰ��������ʱ��
		int ReadyTime;//��������ʱ��
		char State;//״̬����W����������R�����У���D������
		int EndTime;//����ʱ��
		struct PCB *next;
};

class m_page1 : public CDialog
{
	DECLARE_DYNAMIC(m_page1)

public:
	m_page1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~m_page1();
	void InitialTabPage(); //��ʼ��ҳ��ĺ���
	void AddProcessIntoList( int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State);
	void AddProcessIntoListTop( int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State);
	void UpdateList(PCB *chosenProcess);
	int RunCPU();//����Cpu����
	int EndCPU();//ֹͣCPU����
	void OnTimer(UINT_PTR nIDEvent);

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListTop;
	afx_msg void OnBnClickedButton3();	
	afx_msg void OnBnClickedButton2();
};
