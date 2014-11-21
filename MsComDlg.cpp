
// MsComDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MsCom.h"
#include "MsComDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMsComDlg 对话框



CMsComDlg::CMsComDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMsComDlg::IDD, pParent)
, SendData(_T(""))
, RecvData(_T(""))
, iTimeSend(0)
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
	DDX_Text(pDX, IDC_TIMESEND, iTimeSend);
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
	ON_BN_CLICKED(IDC_CLOSE, &CMsComDlg::OnBnClickedClose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SCANCOM, &CMsComDlg::OnBnClickedScancom)
	ON_BN_CLICKED(IDC_CLREARRECV, &CMsComDlg::OnBnClickedClrearrecv)
ON_BN_CLICKED(IDC_BTIMESEND, &CMsComDlg::OnBnClickedBtimesend)
END_MESSAGE_MAP()


// CMsComDlg 消息处理程序

BOOL CMsComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码
	
	CComboBox*ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO1);
	ComboBox->SetCurSel(0);//串口号初始化为1
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO2);
	ComboBox->SetCurSel(4);//波特率初始化为9600
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO3);
	ComboBox->SetCurSel(4);//数据位初始化为8
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO4);
	ComboBox->SetCurSel(1);//停止位初始化为1
	ComboBox = (CComboBox*)GetDlgItem(IDC_COMBO5);
	ComboBox->SetCurSel(0);//校检位初始化为0
	GetDlgItem(IDC_SEND)->EnableWindow(false);//禁用发送功能
	GetDlgItem(IDC_BTIMESEND)->EnableWindow(false);
	CEdit* ComSta = (CEdit*)GetDlgItem(IDC_COMSTA);
	ComStatc.SetWindowTextW(_T("串口未打开"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CMsComDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMsComDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMsComDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CMsComDlg::OnBnClickedClear()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	SendData.SetString(_T(""));
	UpdateData(false);
}


void CMsComDlg::OnBnClickedExit()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(0);
}
void CMsComDlg::OnBnClickedOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_hComHandle != NULL)
	{
		MessageBox(_T("串口正在使用"), _T("提示："), MB_OK);
		CloseHandle(m_hComHandle);
		MsComSR ComSR =  MsComSR();
		m_hComHandle = NULL;
		return;
	}
	if (Com_Num=="")
	Comnum.GetLBText(Comnum.GetCurSel(), Com_Num);
	m_hComHandle = CreateFile(Com_Num, 
		GENERIC_READ|GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
		0);//创建串口
	if (m_hComHandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("串口打开失败"),_T("提示："),MB_OK);
		if (m_hComHandle != NULL)
			m_hComHandle = NULL;
		return;
	}
	else
	{
		UpdateData();
		ComStatc.SetWindowTextW(_T("串口已打开"));
		GetDlgItem(IDC_SEND)->EnableWindow(true);//打开发送按钮
		GetDlgItem(IDC_BTIMESEND)->EnableWindow(true);
		ComSR.SetComHandle(m_hComHandle);
		if (ComSR.CreateMyThread() == NULL)
		{
			RecvData = "创建线程失败\n";
		}
		ComSR.SetThreadRun(true);
		SetTimer(1,100,0);
		RecvData += ComSR.GetRecvData();
	}
	SetupComm(m_hComHandle,512,1024);//设置输入输出缓存区大小
	DCB dcb;
	CString str_Bps;
	CString str_DataBit;
	CString str_StopBit;
	CString str_CheckBit;
	Bps.GetLBText(Bps.GetCurSel(), str_Bps);
	DataBit.GetLBText(DataBit.GetCurSel(), str_DataBit);
	StopBit.GetLBText(StopBit.GetCurSel(), str_StopBit);
	CheckBit.GetLBText(CheckBit.GetCurSel(), str_CheckBit);
	GetCommState(m_hComHandle,&dcb);//获取串口设备信息
	dcb.BaudRate =_ttoi(str_Bps);//波特率
	dcb.ByteSize = _ttoi(str_DataBit);// 数据位
	dcb.StopBits = _ttoi(str_StopBit);//停止位
	dcb.Parity = _ttoi(str_CheckBit);//校验位
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
void CMsComDlg::OnBnClickedClose()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_SEND)->EnableWindow(false);
	GetDlgItem(IDC_BTIMESEND)->EnableWindow(false);
	CloseHandle(m_hComHandle);
	m_hComHandle = NULL;
	ComSR.SetThreadRun(false);
	KillTimer(1);
	ComStatc.SetWindowTextW(_T("串口已关闭"));
}
DWORD WINAPI CMsComDlg::MyThreadFunction(LPVOID pParam)
{
	return 0;
}


void CMsComDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	UpdateData(true);
	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == 1)
	{
		this->RecvData += ComSR.GetRecvData();
		ComSR.SetRecvData(_T(""));
	}
	if (nIDEvent == 2)
	{
		ComSR.SetSendData(SendData);
		ComSR.SetComHandle(m_hComHandle);
		ComSR.SendData(ComSR.GetComHandle());
	}
	UpdateData(false);
	
}
void CMsComDlg::OnBnClickedScancom()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	HANDLE SCAN;
	TCHAR Keydata[128]=_T("HARDWARE\\DEVICEMAP\\SERIALCOMM");
	ULONG size = sizeof(Keydata) / sizeof(*Keydata);
	TCHAR _Keydata[5] = _T("");
	CRegKey*key = new CRegKey();
	long int cout=key->Open(HKEY_LOCAL_MACHINE,Keydata,KEY_READ);
	if (cout!=0)
	{
		UpdateData(true);
		RecvData += "\n！！该计算机未使用任何串口，或者串口故障！！\n";
		return;
	}
	cout=key->QueryStringValue(_T("\\Device\\Serial2"),_Keydata,&size);
	
	Com_Num = _Keydata;
	Comnum.SetWindowTextW(Com_Num);
	key->Close();
	UpdateData(false);
	return;
}
void CMsComDlg::OnBnClickedClrearrecv()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	RecvData.SetString(_T(""));
	UpdateData(FALSE);
}

void CMsComDlg::OnBnClickedBtimesend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (iTimeSend <= 0)
	{
		RecvData += "!!!您的输入的发送时间间隔有误!!!，\n!!!!使用该功能时时间间隔数据不能为空或者为负数!!!!\n";
	}
	SetTimer(2,iTimeSend,0);
	UpdateData(false);
}

