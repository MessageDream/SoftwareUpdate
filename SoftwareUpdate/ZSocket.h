#pragma once
#include "MyFuncLib.h"
#include <ws2tcpip.h>
class ZSocket
{
public:
	enum TIMEOUT	
	{	
		TIMEOUT_CONT= 0,
		TIMEOUT_ACCEPT,
		TIMEOUT_SEND,	
		TIMEOUT_RECV,	
		MAX_TIMEOUT
	};
	enum ERRORINFO
	{
		ERROR_OK=0,//�ɹ�
		ERROR_SOCKDLL,//����SOCK�����
		ERROR_INVALIDSOCK,//��Ч�׽���
		ERROR_INITSOCK,//��ʼ������
		ERROR_CLOSESOCK,//�ر��׽��ֳ���
		ERROR_CONT,//���ӳ���
		ERROR_CONT_TIMEOUT,//���ӳ�ʱ
		ERROR_CONT_STOP,//����ֹͣ
		ERROR_BIND,//�󶨳���
		ERROR_LISTEN,//��������
		ERROR_ACCEPT,//���ܳ���
		ERROR_ACCEPT_TIMEOUT,//���ܳ�ʱ
		ERROR_ACCEPT_STOP,//����ֹͣ
		ERROR_SEND,//���ͳ���
		ERROR_SEND_TIMEOUT,//���ͳ�ʱ
		ERROR_SEND_STOP,//����ֹͣ
		ERROR_RECV,//���ճ���
		ERROR_RECV_TIMEOUT,//���ճ�ʱ
		ERROR_RECV_STOP,//����ֹͣ
		ERROR_OTHER//��������
	};
private:
	SOCKET m_sock;
	HANDLE m_hEvtExitComm;
	bool m_bIsStopCont;
	bool m_bIsStopAccept;
	bool m_bIsStopSend;
	bool m_bIsStopRecv;
	DWORD m_sz_dwTimeout[MAX_TIMEOUT];
public:
	ZSocket(void);
	~ZSocket(void);
	static int CallSocketDll(void);
	static int UncallSocketDll(void);
	int InitSocket(void);
	int CloseSocket(void);
	int Connect(const char * in_p_cServerIp,const unsigned short & in_nServerPort);
	int Connect(const CString & in_strServerIp,const CString & in_strServerPort);
	int Bind(const char * in_p_cLocalIp,const unsigned short & in_nLocalPort);
	int Bind(const CString & in_strLocalIp,const CString & in_strLocalPort);
	int Listen(const int & in_nBackLog);
	int Accept(ZSocket & out_sockClient,CString * out_p_strClientIP=NULL);
	int Send(const char * in_p_cData,const int & in_nSendLen,int & out_nActSendLen);
	int Send(const char * in_p_cData,const int & in_nSendLen);
	int Send(const CString & in_strData);
	int Recv(char * out_p_cData,const int & in_nMaxRecvLen,int & out_nActRecvLen);
	int Recv(char * out_p_cData,const int & in_nRecvLen);
	int Recv(CString & out_strData,const int & in_nMaxRecvLen,const bool & in_bIsBlocking=true);
	int Recv(CString & out_strData, const bool & in_bIsBlocking = true);
	BOOL ExecReq(const CString & in_strReq,CString & out_strRslt,const int & in_nMaxRecvLen);
	void StopComm(void);
	BOOL SetTimeOut(const BYTE & in_cTimeoutIndex,const DWORD & in_dwTimeOut);
	CString DomainNameToIp(const CString & strDomainName);
	bool IsStrIP(const CString & str);
};

