#pragma once



// ResultForm 폼 보기

class ResultForm : public CFormView
{
	DECLARE_DYNCREATE(ResultForm)

protected:
	ResultForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ResultForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ResultForm };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CStatic m_Color;
	afx_msg void OnBnClickedButton6();
	int cnt = 0;
	CButton m_btempdetect;
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBstart();
	afx_msg void OnBnClickedBstop();

	void Setbutton(bool n);
};


