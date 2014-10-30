
// MsComDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
//#include"MsComSR.h"
// CMsComDlg 对话框
class CMsComDlg : public CDialogEx
{
// 构造
public:
	CMsComDlg(CWnd* pParent = NULL);	// 标准构造函数
	HANDLE m_hComHandle;
	MsComSR ComSR;
// 对话框数据
	enum { IDD = IDD_MSCOM_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedOpen();
	void RecvThread();
	static  DWORD WINAPI MyThreadFunction(LPVOID pParam);
	//HANDLE CreateRecvThread();
	CComboBox Comnum;
	CComboBox Bps;
	CComboBox DataBit;
	CComboBox StopBit;
	CComboBox CheckBit;

	CEdit ComStatc;
	// 接收数据
//	CEdit RecvData;
	// 要发送的数据
	afx_msg void OnBnClickedSend();
	CString SendData;
	afx_msg void OnBnClickedBedinrecv();
	// 接收到的数据
	CString RecvData;
	afx_msg void OnBnClickedClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
