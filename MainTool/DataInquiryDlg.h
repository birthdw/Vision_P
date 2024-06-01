#pragma once
#include "afxdialogex.h"


// DataInquiryDlg 대화 상자

class DataInquiryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DataInquiryDlg)

public:
	DataInquiryDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DataInquiryDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DataInquiry };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
