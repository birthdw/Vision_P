// CSocketClient.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "CSocketClient.h"


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

	CSocket::OnReceive(nErrorCode);
}
