#pragma once



// ServerForm 폼 보기
#include "CSocketClient.h"
#include "AWS.h"
#include "RobotInfo.h"


class ServerForm : public CFormView
{
	DECLARE_DYNCREATE(ServerForm)

protected:
	ServerForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ServerForm();
	AWSINFO m_awsinfo;
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
	afx_msg void OnBnClickedTcpBut();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();


	virtual void OnInitialUpdate();


	const CString IPAddress() const;	 // IP Address를 호출합니다.
	void ClientTCP(CString strMessage);				 	 // 서버로 정보를 전송할때 사용합니다.
	void SetList(CString strMessage);	// 리스트 컨트롤에 로그 추가

	AWSINFO GetAwsInfo();
	void SetAwsInfo (AWSINFO pAWS);

	UINT m_Port;
	CIPAddressCtrl m_IP;
	CButton m_TCP_BUTTON;
	CSocketClient m_Client;
	CStatic m_STATIC_TCP;
	CListCtrl m_ListTcp;
	CStatic m_StateColor;
	CStatic m_ServerColor;


	// 스위치
	BOOL m_TCPConnect = TRUE;					 // 연결, 연결끊기 스위치입니다.
	BOOL onlyone = TRUE;
	BOOL AWSRUN = TRUE;
	int Count = 0;
	
	
	vector<vector<string>> m_boxlist;
	

	

	//서버 함수
	SDKOptions m_options;
	AWS* m_aws = nullptr;

	void exit_s3();
	void initaws();

	
	

	
	
	

	
	afx_msg void OnLvnItemchangedListTcp(NMHDR* pNMHDR, LRESULT* pResult);
};


