
// ProcessCtrlProjectDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "m_page1.h"
#include "m_page2.h"

#include <windows.h>
//PCB在m_page1.h里面已经定义了

// CProcessCtrlProjectDlg 对话框
class CProcessCtrlProjectDlg : public CDialogEx
{
// 构造
public:
	CProcessCtrlProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PROCESSCTRLPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;  //Tab成员变量
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	m_page1 page1;//页面1
	m_page2 page2;//页面2

	int TIMEPIECE;//每个时间片的时间
	int DELETEPRI;//每运行一个时间片运行进程减少的优先数
	int ADDPRI;//没运行一个时间片等待进程增加的优先数
	PCB* ProcessList;//PCB进程链表
	int AccelerateTime;//累计运行时间
	bool CPUBusyState;//指示是否需要CPU工作，true代表cpu需要工作，false代表没有进程需要工作
	bool CPURunState;//指示CPU现在是否可以工作，默认是未启动CPU工作的，当添加了新任务时就可以自动开始工作
	int ProcessNum;//进程的总数
	PCB * FinishedProcessList;

public:
	void CreateList(int num);//创建PCB进程链表
	PCB * ProcessRun();//进程执行函数，选取需要执行的进程，即优先数最高的进程
	void DeleteProcess(PCB *chosenProcess);//删除进程链表中的一个进程
	void ChangeProcess(PCB *chosenProcess);//每运行完一个时间片要对每个进程的时间优先数等参数进行调整
	void FreeProcess(PCB * finishedProcess);//将完成了的进程添加到已完成进程链表
	void OnTimer(UINT_PTR nIDEvent);//定时器的处理函数
};
