// ResultForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "ResultForm.h"
#include "ToolManager.h"

// ResultForm

IMPLEMENT_DYNCREATE(ResultForm, CFormView)

ResultForm::ResultForm()
	: CFormView(IDD_ResultForm)
{

}

ResultForm::~ResultForm()
{
}

void ResultForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ResultForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &ResultForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ResultForm::OnBnClickedButton2)
END_MESSAGE_MAP()


// ResultForm 진단

#ifdef _DEBUG
void ResultForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ResultForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ResultForm 메시지 처리기


void ResultForm::OnBnClickedButton1()
{
	// cam on
	ToolManager::GetInstance()->SetKillFrm(false);
}


void ResultForm::OnBnClickedButton2()
{
	// cam off
	ToolManager::GetInstance()->SetKillFrm(true);
}
