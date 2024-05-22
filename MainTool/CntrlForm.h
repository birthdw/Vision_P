#pragma once


//GOD DO WON
//GOD GOD GOD
// CntrlForm 폼 보기

class CntrlForm : public CFormView
{
	DECLARE_DYNCREATE(CntrlForm)

protected:
	CntrlForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CntrlForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CntrlForm };
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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedb1();
	afx_msg void OnBnClickedb2();
	afx_msg void OnBnClickedb3();
	afx_msg void OnBnClickedb4();
	afx_msg void OnBnClickedb5();
	afx_msg void OnBnClickedb6();
	afx_msg void OnBnClickedb8();
	afx_msg void OnBnClickedb7();
	afx_msg void OnBnClickedButton1();

	bool m_isRailOn;
};


