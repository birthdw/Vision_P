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

	void ProcessString(const CString& str);
	vector<CString> SplitCString(const CString& str, const CString& delimiter);

	int Count = 0;
};

