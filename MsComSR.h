#ifndef _MsComSR
#define _MsComSR           // 从 Windows 头中排除极少使用的资料

class MsComSR
{
public:
	MsComSR();
	~MsComSR();
	CString GetRecvData();//获取接收数据
	void SetRecvData(CString data);//设置接收数据
	CString GetSendData();//获取发送数据
	void SetSendData(CString data);//设置发送的数据
	int SendData(HANDLE m_hComHandle);//发送数据 
	int RecvData(HANDLE m_hComHandle);//接收数据
	void SetComHandle(HANDLE _m_hComHandle);//设置串口
	HANDLE GetComHandle();//获取串口
	void SetThreadRun(bool statc);//设置进程运行标志
	bool GetThreadRun();//获取进程运行标志
	static DWORD WINAPI MyThreadFuncatiuon(LPVOID lp);//进程函数
	HANDLE CreateMyThread();//创建进程
private:
	CString _RecvData;//接收的数据
	CString _SendData;//发送的数据
	HANDLE m_hComHandle;//串口
	bool ThreadRun;//进程运行标志位
};
#endif