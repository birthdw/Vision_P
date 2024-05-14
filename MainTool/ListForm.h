#pragma once

#include "TestTab.h"
#include "DetectTab.h"

class ListForm : public CFormView
{
	DECLARE_DYNCREATE(ListForm)

protected:
	ListForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ListForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ListForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual void OnInitialUpdate();


	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_TabCtrl;
	TestTab m_TestTab;
	DetectTab m_Detecttab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};


