#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// m_page1 对话框
struct PCB{
		int PID; //进程ID
		char ProcessName[50];//进程名
		int Priority;//进程优先数
		int EnterTime;//到达时间
		int AllTime;//进程余下时间
		int UsedTime;//已使用CPU时间
		int RunTime;//当前连续运行时间
		int ReadyTime;//连续就绪时间
		char State;//状态，‘W’就绪，‘R’运行，‘D’结束
		int EndTime;//结束时间
		struct PCB *next;
};

class m_page1 : public CDialog
{
	DECLARE_DYNAMIC(m_page1)

public:
	m_page1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~m_page1();
	void InitialTabPage(); //初始化页面的函数
	void AddProcessIntoList( int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State);
	void AddProcessIntoListTop( int PID,char ProcessName[50], int Priority, int EnterTime, int AllTime, int UsedTime, int RunTime, int ReadyTime, char State);
	void UpdateList(PCB *chosenProcess);
	int RunCPU();//启动Cpu工作
	int EndCPU();//停止CPU工作
	void OnTimer(UINT_PTR nIDEvent);

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListTop;
	afx_msg void OnBnClickedButton3();	
	afx_msg void OnBnClickedButton2();
};
