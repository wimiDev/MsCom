
// MsComDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
//#include"MsComSR.h"
// CMsComDlg �Ի���
class CMsComDlg : public CDialogEx
{
// ����
public:
	CMsComDlg(CWnd* pParent = NULL);	// ��׼���캯��
	HANDLE m_hComHandle;
	MsComSR ComSR;
// �Ի�������
	enum { IDD = IDD_MSCOM_DIALOG };
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
	// ��������
//	CEdit RecvData;
	// Ҫ���͵�����
	afx_msg void OnBnClickedSend();
	CString SendData;
	afx_msg void OnBnClickedBedinrecv();
	// ���յ�������
	CString RecvData;
	afx_msg void OnBnClickedClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
