#include"stdafx.h"
//#include"MsComSR.h"
MsComSR::MsComSR()
{
	_RecvData = "";
	_SendData = "";
	ThreadRun = true;
}
MsComSR::~MsComSR()
{

}
void MsComSR::SetRecvData(CString data)
{
	this->_RecvData = data;
}
void MsComSR::SetSendData(CString data)
{
	this->_SendData = data;
}
void MsComSR::SetComHandle(HANDLE _m_hComHandle)
{
	this->m_hComHandle = _m_hComHandle;
}
CString MsComSR::GetRecvData()
{
	return this->_RecvData;
}
HANDLE MsComSR::GetComHandle()
{
	return this->m_hComHandle;
}
bool MsComSR::GetThreadRun()
{
	return this->ThreadRun;
}
void MsComSR::SetThreadRun(bool statc)
{
	this->ThreadRun = statc;
}
int MsComSR::SendData(HANDLE m_hComHandle)
{
	OVERLAPPED oWrite;//重叠变量
	BOOL bWrite;
	memset(&oWrite, 0, sizeof(OVERLAPPED));//初始化重叠变量
	oWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);//创建写串口事件
	DWORD dwWrite = _SendData.GetLength();
	this->ThreadRun = false;
	bWrite = WriteFile(m_hComHandle, (char*)(LPCTSTR)_SendData, dwWrite, &dwWrite, &oWrite);
	if (!bWrite)
	{
		DWORD Error = GetLastError();
		if (Error == ERROR_IO_PENDING)
		{
			WaitForSingleObject(oWrite.hEvent, 1000);
		}
	}
	this->ThreadRun = true;
	return 0;
}
int MsComSR::RecvData(HANDLE m_hComHandle)
{
	OVERLAPPED oRead;
	BOOL bRead;
	memset(&oRead, 0, sizeof(OVERLAPPED));
	oRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	char *cRecvData;
	cRecvData = new char[1024];
	memset(cRecvData, 0, 1024);
	DWORD dwRead = 1024;
	if (ThreadRun)
	{
	bRead = ReadFile(m_hComHandle, cRecvData, dwRead, &dwRead, &oRead);
	if (!bRead&&ThreadRun)
	{
		DWORD Error = GetLastError();
		if (Error == ERROR_IO_PENDING)
		{
			Error=WaitForSingleObject(oRead.hEvent, 1000);
			 Error=0;
		}
	}
	_RecvData = cRecvData;
	PurgeComm(m_hComHandle, PURGE_TXCLEAR | PURGE_RXCLEAR);
	delete[]cRecvData;
	}
	return 0;
}
DWORD WINAPI MsComSR::MyThreadFuncatiuon(LPVOID lp)
{
	MsComSR*RecvThread = (MsComSR*)lp;
	while (true)
	{
		RecvThread->RecvData(RecvThread->m_hComHandle);
		Sleep(1);
	}
	return 0;
}
HANDLE MsComSR::CreateMyThread()
{
	DWORD ThreadID;
	return CreateThread(NULL, 0,MyThreadFuncatiuon, this, 0, &ThreadID);
}