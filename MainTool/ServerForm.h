﻿#pragma once



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
	// 이벤트 함수
	afx_msg void OnBnClickedTcpBut();
	afx_msg void OnPaint();
	afx_msg void OnLvnItemchangedListTcp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnSocketThreadFinished(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedLogBut();


	// 가상함수
	virtual void OnInitialUpdate();


	// 도구 자료형
	UINT m_Port;						// PORT를 가져옴
	CIPAddressCtrl m_IP;				// IP를 가져옴
	CButton m_TCP_BUTTON;				// 소켓 통신 연결 버튼
	CListCtrl m_ListTcp;				// 소켓 통신 로그 표시
	CStatic m_StateColor;				// 소켓 통신상태 픽쳐 컨트롤
	CStatic m_ServerColor;				// 서버 통신상태 픽쳐 컨트롤

private:
	// 서버 스위치
	AWSINFO m_awsinfo;

public:
	// 소켓통신 함수
	const CString IPAddress() const;	// IP Address를 호출합니다.
	void ClientTCP(CString strMessage);	// 서버로 정보를 전송할때 사용합니다.
	void SetList(CString str, CString strMessage);	// 리스트 컨트롤에 로그 추가


	// 서버 동작 함수
	void exit_s3();						// 서버 종료 함수
	void initaws();						// 서버 연결 함수


private:
	// 소켓 통신 자료형
	CSocketClient m_Client;				// 소켓 연결
	int Count = 0;						// 소켓 로그 카운트


private:
	// 통신상태 색깔 자료형
	STATUCOLOR m_ControlColor = STATUCOLOR::STAY;			// 통신상태 색깔 정할 수 있음
	COLORTHREAD m_ThreadColor = COLORTHREAD::THREADRUN;		// 통신상태 색깔 쓰레드 종료
	CString m_SColor = L"yellow";							// 서버 통신상태 색깔
	CString m_KColor = L"red";								// 소켓 통신상태 색깔


private:
	// 스위치
	BOOL m_TCPConnect = TRUE;			// 연결, 연결끊기 스위치
	BOOL AWSRUN = TRUE;					// 서버 연결 스위치
	BOOL m_SocketThreadSWICHT = TRUE;	// 소켓 쓰레드 병목 막는 스위치
	bool m_boxrun = false;
	

private:
	// DB 리스트 불러오면 여기에 저장
	vector<AWSLIST> m_boxlist;
	
private:
	//서버 기동 자료형
	SDKOptions m_options;
	AWS* m_aws = nullptr;


private:
	// 서버 저장 자료형
	string m_awscolor = "";
	string m_awsfaulty = "";
	string m_modifyColor;
	string m_modifyFaulty;
	string m_modifyCurId;


public:
	AWSINFO GetAwsInfo();				// 서버 동작 얻어옴
	void SetAwsInfo(AWSINFO pAWS);		// 서버 동작 
	void SetModify(string color, string faulty, string curId);


	void SetAwsColor(string set);
	string GetAwsColor();
	void SetAwsFaulty(string set);
	string GetAwsFaulty();

	void SetModifyColor(string set);
	string GetModifyColor();
	void SetModifyFaulty(string set);
	string GetModifyFaulty();
	void SetModifyCurId(string set);
	string GetModifyCurId();

	void SetClientClose();

	void SetThreadColor(COLORTHREAD set);
	COLORTHREAD GetThreadColor();
	void SetControlColor(STATUCOLOR set);
	STATUCOLOR GetControlColor();

	void SETTCPConnect(BOOL set);
	BOOL GetTCPConnect();

	void SETBoxlist(vector<AWSLIST> set);
	vector<AWSLIST> GetBoxlist();

	AWS* GetAWS();
};


