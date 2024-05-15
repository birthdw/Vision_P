// CntrlForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "CntrlForm.h"


// CntrlForm

IMPLEMENT_DYNCREATE(CntrlForm, CFormView)

CntrlForm::CntrlForm()
	: CFormView(IDD_CntrlForm)
{
	int a;
}

CntrlForm::~CntrlForm()
{
}

void CntrlForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CntrlForm, CFormView)
END_MESSAGE_MAP()


// CntrlForm 진단

#ifdef _DEBUG
void CntrlForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CntrlForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CntrlForm 메시지 처리기
