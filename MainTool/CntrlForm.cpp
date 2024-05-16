// CntrlForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "CntrlForm.h"
#include "ToolManager.h"
#include "ServerForm.h"

// CntrlForm

IMPLEMENT_DYNCREATE(CntrlForm, CFormView)

CntrlForm::CntrlForm()
	: CFormView(IDD_CntrlForm)
{
}

CntrlForm::~CntrlForm()
{
}

void CntrlForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CntrlForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CntrlForm::OnBnClickedButton2)
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


void CntrlForm::OnBnClickedButton2()
{
	CString str = _T("12312");

	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}
