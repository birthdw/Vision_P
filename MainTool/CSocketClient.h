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
	vector<CString> CSocketClient::SplitCString(const CString& str, const CString& delimiter);
	void CSocketClient::ProcessString(const CString& str);

	int Count = 0;
};

