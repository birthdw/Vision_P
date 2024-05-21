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
	ON_BN_CLICKED(IDC_b1, &CntrlForm::OnBnClickedb1)
	ON_BN_CLICKED(IDC_b2, &CntrlForm::OnBnClickedb2)
	ON_BN_CLICKED(IDC_b3, &CntrlForm::OnBnClickedb3)
	ON_BN_CLICKED(IDC_b4, &CntrlForm::OnBnClickedb4)
	ON_BN_CLICKED(IDC_b5, &CntrlForm::OnBnClickedb5)
	ON_BN_CLICKED(IDC_b6, &CntrlForm::OnBnClickedb6)
	ON_BN_CLICKED(IDC_b8, &CntrlForm::OnBnClickedb8)
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
	//home
	CString str = _T("12312");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}





void CntrlForm::OnBnClickedb1()
{
	//앞+
}


void CntrlForm::OnBnClickedb2()
{
	//앞- 
}


void CntrlForm::OnBnClickedb3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CntrlForm::OnBnClickedb4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CntrlForm::OnBnClickedb5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CntrlForm::OnBnClickedb6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CntrlForm::OnBnClickedb8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
