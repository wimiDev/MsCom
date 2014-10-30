
// MsComDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MsCom.h"
#include "MsComDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMsComDlg �Ի���



CMsComDlg::CMsComDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMsComDlg::IDD, pParent)
, SendData(_T(""))
, RecvData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ComSR = MsComSR();
}

void CMsComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Comnum);
	DDX_Control(pDX, IDC_COMBO2, Bps);
	DDX_Control(pDX, IDC_COMBO3, DataBit);
	DDX_Control(pDX, IDC_COMBO4, StopBit);
	DDX_Control(pDX, IDC_COMBO5, CheckBit);
	DDX_Control(pDX, IDC_COMSTA, ComStatc);
	//  DDX_Control(pDX, IDC_RECVDATA, RecvData);

	//  DDX_Control(pDX, IDC_SENDDATA, SendData);
	DDX_Text(pDX, IDC_SENDDATA, SendData);
	DDX_Text(pDX, IDC_RECVDATA, RecvData);
}

BEGIN_MESSAGE_MAP(CMsComDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMsComDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CLEAR, &CMsComDlg::OnBnClickedClear)
	ON_BN_CLICKED(ID_EXIT, &CMsComDlg::OnBnClickedExit)
	ON_BN_CLICKED(ID_OPEN, &CMsComDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SEND, &CMsComDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_BEGINRECV, &CMsComDlg::OnBnClickedBedinrecv)
	ON_BN_CLICKED(IDC_CLOSE, &CMsComDlg::OnBnClickedClose)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMsComDlg ��Ϣ�������

BOOL CMsComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	CComboBox*ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	ComboBox->SetCurSel(0);//���ںų�ʼ��Ϊ1
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO2);
	ComboBox->SetCurSel(2);//�����ʳ�ʼ��Ϊ9600
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO3);
	ComboBox->SetCurSel(4);//����λ��ʼ��Ϊ8
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO4);
	ComboBox->SetCurSel(1);//ֹͣλ��ʼ��Ϊ1
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO5);
	ComboBox->SetCurSel(0);//У��λ��ʼ��Ϊ0
	GetDlgItem(IDC_SEND)->EnableWindow(false);//���÷��͹���
	GetDlgItem(IDC_BEGINRECV)->EnableWindow(false);
	CEdit* ComSta = (CEdit*)GetDlgItem(IDC_COMSTA);
	ComStatc.SetWindowTextW(_T("����δ��"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMsComDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CMsComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMsComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMsComDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void CMsComDlg::OnBnClickedClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	SendData.SetString(_T(""));
	RecvData.SetString(_T(""));
	UpdateData(false);
}


void CMsComDlg::OnBnClickedExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CloseWindow();
}
void CMsComDlg::OnBnClickedOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_hComHandle != NULL)
	{
		MessageBox(_T("��������ʹ��"), _T("��ʾ��"), MB_OK);
		CloseHandle(m_hComHandle);
		MsComSR ComSR =  MsComSR();
		return;
	}
	CString Com_Num;
	Comnum.GetLBText(Comnum.GetCurSel(), Com_Num);
	m_hComHandle = CreateFile(Com_Num, GENERIC_READ|GENERIC_WRITE,
		0, 0,OPEN_EXISTING, FILE_FLAG_OVERLAPPED,0);//��������
	if (m_hComHandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("���ڴ�ʧ��"),_T("��ʾ��"),MB_OK);
		if (m_hComHandle!=NULL)
		CloseHandle(m_hComHandle);
		return;
	}
	else
	{
		ComStatc.SetWindowTextW(_T("�����Ѵ�"));
		GetDlgItem(IDC_SEND)->EnableWindow(true);//�򿪷��Ͱ�ť
		GetDlgItem(IDC_BEGINRECV)->EnableWindow(true);//�򿪿�ʼ���հ�ť
		ComSR.SetComHandle(m_hComHandle);
		ComSR.SetThreadRun(true);
		SetTimer(1,200,0);
	}
	SetupComm(m_hComHandle,512,1024);//�������������������С
	DCB dcb;
	CString str_Bps;
	CString str_DataBit;
	CString str_StopBit;
	CString str_CheckBit;
	Bps.GetLBText(Bps.GetCurSel(), str_Bps);
	DataBit.GetLBText(DataBit.GetCurSel(), str_DataBit);
	StopBit.GetLBText(StopBit.GetCurSel(), str_StopBit);
	CheckBit.GetLBText(CheckBit.GetCurSel(), str_CheckBit);
	GetCommState(m_hComHandle,&dcb);//��ȡ�����豸��Ϣ
	dcb.BaudRate =_ttoi(str_Bps);//������
	dcb.ByteSize = _ttoi(str_DataBit);// ����λ
	dcb.StopBits = _ttoi(str_StopBit);//ֹͣλ
	dcb.Parity = _ttoi(str_CheckBit);//У��λ
	SetCommState(m_hComHandle,&dcb);
	PurgeComm(m_hComHandle,PURGE_TXCLEAR|PURGE_RXCLEAR);
	UpdateData(false);
}

void CMsComDlg::OnBnClickedSend()
{
	UpdateData();
	ComSR.SetSendData(SendData);
	ComSR.SetComHandle(m_hComHandle);
	ComSR.SendData(ComSR.GetComHandle());
	//UpdateData(false);
}
void  CMsComDlg::RecvThread()
{
}
void CMsComDlg::OnBnClickedBedinrecv()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	if (ComSR.CreateMyThread() == NULL)
	{
		RecvData = "�����߳�ʧ��\n";
	}
	RecvData += ComSR.GetRecvData();
	
}


void CMsComDlg::OnBnClickedClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_SEND)->EnableWindow(false);
	CloseHandle(m_hComHandle);
	m_hComHandle = NULL;
	ComSR.SetThreadRun(false);
	KillTimer(1);
	ComStatc.SetWindowTextW(_T("�����ѹر�"));
}
DWORD WINAPI CMsComDlg::MyThreadFunction(LPVOID pParam)
{
	return 0;
}


void CMsComDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(true);
	if (nIDEvent == 1)
	{
		this->RecvData += ComSR.GetRecvData();
		ComSR.SetRecvData(_T(""));
	}
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}
