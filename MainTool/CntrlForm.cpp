﻿// CntrlForm.cpp: 구현 파일
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
	int a = 0;
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
	ON_BN_CLICKED(IDC_b7, &CntrlForm::OnBnClickedb7)
	ON_BN_CLICKED(IDC_BUTTON1, &CntrlForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CntrlForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CntrlForm::OnBnClickedButton4)
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
	CString str = _T("RBT:HOME");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}





void CntrlForm::OnBnClickedb1()
{
	//모터1 +
	//앞+
	CString str = _T("RBT:M1_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb2()
{
	//모터 1
	//앞- 
	CString str = _T("RBT:M1_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb3()
{
	//모터 2 +
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M2_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb4()
{
	//모터2 -
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M2_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb5()
{
	//모터3 +
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M3_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb6()
{
	//모터3 -
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M3_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb8()
{
	//모터4 -
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str = _T("RBT:M4_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedb7()
{
	//모터4 +
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M4_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

}


void CntrlForm::OnBnClickedButton1()
{
	//레일 ON OFF 버튼
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 버튼 상태를 토글
	m_isRailOn = !m_isRailOn;

	// 버튼 텍스트 변경
	CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON1);
	if (m_isRailOn)
	{
		pButton->SetWindowText(_T("Rail_ON"));
		CString str = _T("RBT:RAIL_ON");
		ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	}
	else
	{
		pButton->SetWindowText(_T("Rail_OFF"));
		CString str = _T("RBT:RAIL_OFF");
		ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	}

}


void CntrlForm::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("START");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}


void CntrlForm::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("STOP");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
}
