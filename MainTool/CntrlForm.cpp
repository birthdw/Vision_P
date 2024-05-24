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
	ON_WM_PAINT()
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

	Grab_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb2()
{
	//모터 1
	//앞- 
	CString str = _T("RBT:M1_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Grab_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb3()
{
	//모터 2 +
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M2_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Morter_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb4()
{
	//모터2 -
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M2_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Morter_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb5()
{
	//모터3 +
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M3_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Morter2_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb6()
{
	//모터3 -
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M3_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Morter2_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb8()
{
	//모터4 -
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str = _T("RBT:M4_M10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Morter3_on = true;
	Invalidate(false);
}


void CntrlForm::OnBnClickedb7()
{
	//모터4 +
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("RBT:M4_P10");
	ToolManager::GetInstance()->m_Serverform->ClientTCP(str);

	Morter3_on = true;
	Invalidate(false);

}


void CntrlForm::OnBnClickedButton1()
{
	//레일 ON OFF 버튼
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 버튼 상태를 토글

	// 버튼 텍스트 변경
	if (!ToolManager::GetInstance()->m_Serverform->GetTCPConnect())
	{
		CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON1);
		m_isRailOn = !m_isRailOn;
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

}


void CntrlForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ToolManager::GetInstance()->SetCntrlForm(this);
}


void CntrlForm::OnPaint()
{
	// device context for painting
 // TODO: 여기에 메시지 처리기 코드를 추가합니다.
 // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
	CPaintDC dc(this);


	CImage png_grab, grab_on, morter, frame, morter2, morter3;

	if (Grab_on == false)
		png_grab.Load(L"Grab.png");
	else
		png_grab.Load(L"Grab_on.png");


	if (Morter_on == false)
		morter.Load(L"morter.png");
	else
		morter.Load(L"morter_on.png");


	if (Morter2_on == false)
		morter2.Load(L"morter.png");
	else
		morter2.Load(L"morter_on.png");


	if (Morter3_on == false)
		morter3.Load(L"morter.png");
	else
		morter3.Load(L"morter_on.png");


	// 이미지를 지정된 크기로 그리기
	png_grab.StretchBlt(dc, 250, 100, 100, 100);
	morter.StretchBlt(dc, 250, 200, 100, 100);
	morter2.StretchBlt(dc, 250, 300, 100, 100);
	morter3.StretchBlt(dc, 250, 400, 100, 100);

}
