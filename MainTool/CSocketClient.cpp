// CSocketClient.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "CSocketClient.h"
#include "ServerForm.h"
#include "ToolManager.h"

// CSocketClient

CSocketClient::CSocketClient()
{
}

CSocketClient::~CSocketClient()
{
}


// CSocketClient 멤버 함수


void CSocketClient::OnClose(int nErrorCode)
{
	// 서버 연결이 끊길 때를 정의합니다.
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);
}


void CSocketClient::OnReceive(int nErrorCode)
{
	// 서버에서 오는 데이터를 받습니다.
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	ServerForm* serecv = (ServerForm*)AfxGetMainWnd();
	char szBuffer[1024];
	memset(szBuffer, 0, sizeof(szBuffer));

	int nRead = Receive(szBuffer, sizeof(szBuffer));
	if (nRead > 0) {
		szBuffer[nRead] = '\0';
		CString strReceive(szBuffer);
		ToolManager::GetInstance()->m_Serverform->SetList(strReceive);
	}

	CSocket::OnReceive(nErrorCode);
}
