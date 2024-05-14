#pragma once

// CSocketClient 명령 대상
#include "resource.h"
#include <afxsock.h>

class CSocketClient : public CSocket
{
public:
	CSocketClient();
	virtual ~CSocketClient();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void socketend();
	void recvinfo(CString strMessage);

	int Count = 0;
};


