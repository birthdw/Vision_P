#pragma once
#include "afxdialogex.h"


// DetectTab 대화 상자

class DetectTab : public CDialog
{
	DECLARE_DYNAMIC(DetectTab)

public:
	DetectTab(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DetectTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DetectTab };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
