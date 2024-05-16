#pragma once
#include "afxdialogex.h"


// CModDlg 대화 상자

class CModDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModDlg)

public:
	CModDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Mod };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit Modtext;
	afx_msg void OnBnClickedButton1();
};
