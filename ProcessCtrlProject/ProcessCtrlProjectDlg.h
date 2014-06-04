
// ProcessCtrlProjectDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "m_page1.h"
#include "m_page2.h"

#include <windows.h>
//PCB��m_page1.h�����Ѿ�������

// CProcessCtrlProjectDlg �Ի���
class CProcessCtrlProjectDlg : public CDialogEx
{
// ����
public:
	CProcessCtrlProjectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROCESSCTRLPROJECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;  //Tab��Ա����
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	m_page1 page1;//ҳ��1
	m_page2 page2;//ҳ��2

	int TIMEPIECE;//ÿ��ʱ��Ƭ��ʱ��
	int DELETEPRI;//ÿ����һ��ʱ��Ƭ���н��̼��ٵ�������
	int ADDPRI;//û����һ��ʱ��Ƭ�ȴ��������ӵ�������
	PCB* ProcessList;//PCB��������
	int AccelerateTime;//�ۼ�����ʱ��
	bool CPUBusyState;//ָʾ�Ƿ���ҪCPU������true����cpu��Ҫ������false����û�н�����Ҫ����
	bool CPURunState;//ָʾCPU�����Ƿ���Թ�����Ĭ����δ����CPU�����ģ��������������ʱ�Ϳ����Զ���ʼ����
	int ProcessNum;//���̵�����
	PCB * FinishedProcessList;

public:
	void CreateList(int num);//����PCB��������
	PCB * ProcessRun();//����ִ�к�����ѡȡ��Ҫִ�еĽ��̣�����������ߵĽ���
	void DeleteProcess(PCB *chosenProcess);//ɾ�����������е�һ������
	void ChangeProcess(PCB *chosenProcess);//ÿ������һ��ʱ��ƬҪ��ÿ�����̵�ʱ���������Ȳ������е���
	void FreeProcess(PCB * finishedProcess);//������˵Ľ�����ӵ�����ɽ�������
	void OnTimer(UINT_PTR nIDEvent);//��ʱ���Ĵ�����
};
