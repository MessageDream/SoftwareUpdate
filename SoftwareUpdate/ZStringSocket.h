/*
** Version  1.0.0.2
** Date     2019.02.27
** Author   zax
** Copyright (C) Since 2009 Zaxai.Com
*/
#pragma once
#include "ZSocket.h"
class ZStringSocket :
	public ZSocket
{
private:
	int m_nMaxLength;//�ַ�������ֽڳ��� Ĭ��10K
	int m_nMaxNumCount;//�ַ�����󳤶ȵ�λ�� Ĭ��5
	int m_nBufSize;//���ݳ��Ȼ�������С Ĭ��6
	char * m_p_cLengthBuf;//���ݳ��Ȼ�����
	bool InitByMaxLength(void);
	bool SetLengthBufByLength(int nLength);
public:
	ZStringSocket();
	ZStringSocket(ZStringSocket && zstrsock);
	ZStringSocket & operator=(ZStringSocket && zstrsock);
	virtual ~ZStringSocket();
	int StringSend(const CString & in_strData);
	int StringRecv(CString & out_strData);
	bool SetMaxStringLength(int nMaxLength);
};

