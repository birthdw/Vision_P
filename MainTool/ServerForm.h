﻿#pragma once



// ServerForm 폼 보기
#include "CSocketClient.h"
#include "AWS.h"


class ServerForm : public CFormView
{
	DECLARE_DYNCREATE(ServerForm)

protected:
	ServerForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ServerForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ServerForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_Port;
	CIPAddressCtrl m_IP;
	afx_msg void OnBnClickedTcpBut();

	const CString IPAddress() const;	 // IP Address를 호출합니다.
	void ClientTCP(CString strMessage);				 	 // 서버로 정보를 전송할때 사용합니다.
	void SetList(CString strMessage);	// 리스트 컨트롤에 로그 추가

	BOOL m_TCPConnect;					 // 연결, 연결끊기 스위치입니다.
	CButton m_TCP_BUTTON;
	CSocketClient m_Client;
	CStatic m_STATIC_TCP;
	
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListTcp;

	int Count;

	//서버용
	bool initaws();
	void exit_s3();

	SDKOptions m_options;
	AWS* m_aws;

	afx_msg void OnBnClickedButton2();
};


