#pragma once
#include "afxdialogex.h"


// TestTab 대화 상자

class TestTab : public CDialog
{
	DECLARE_DYNAMIC(TestTab)

public:
	TestTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TestTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TestTab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CEdit m_Testtxt;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
};
