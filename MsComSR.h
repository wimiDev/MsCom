#ifndef _MsComSR
#define _MsComSR           // �� Windows ͷ���ų�����ʹ�õ�����

class MsComSR
{
public:
	MsComSR();
	~MsComSR();
	CString GetRecvData();//��ȡ��������
	void SetRecvData(CString data);//���ý�������
	CString GetSendData();//��ȡ��������
	void SetSendData(CString data);//���÷��͵�����
	int SendData(HANDLE m_hComHandle);//�������� 
	int RecvData(HANDLE m_hComHandle);//��������
	void SetComHandle(HANDLE _m_hComHandle);//���ô���
	HANDLE GetComHandle();//��ȡ����
	void SetThreadRun(bool statc);//���ý������б�־
	bool GetThreadRun();//��ȡ�������б�־
	static DWORD WINAPI MyThreadFuncatiuon(LPVOID lp);//���̺���
	HANDLE CreateMyThread();//��������
private:
	CString _RecvData;//���յ�����
	CString _SendData;//���͵�����
	HANDLE m_hComHandle;//����
	bool ThreadRun;//�������б�־λ
};
#endif