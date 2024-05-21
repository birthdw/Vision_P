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
	DDX_Control(pDX, IDC_COLOR, m_Color);
	DDX_Control(pDX, IDC_BUTTON4, m_btempdetect);
}

BEGIN_MESSAGE_MAP(ResultForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &ResultForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ResultForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ResultForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ResultForm::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &ResultForm::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &ResultForm::OnBnClickedButton6)
	ON_WM_PAINT()
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
	ToolManager::GetInstance()->SetSpecialOn(false);
	m_btempdetect.EnableWindow(FALSE);

}


void ResultForm::OnBnClickedButton2()
{
	// cam off
	ToolManager::GetInstance()->SetKillFrm(true);
	ToolManager::GetInstance()->SetSpecialOn(false);
	m_btempdetect.EnableWindow(TRUE);

}


void ResultForm::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ToolManager::GetInstance()->Save();
}


void ResultForm::OnBnClickedButton4()
{
	CString str = _T("pic 파일 (*.png, *.jpg) |*.png; *.jpg|"); // 파일 확장자 제한 

	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		ToolManager::GetInstance()->ShowPic(string(CT2CA(strPathName)));

	}
}


void ResultForm::OnBnClickedButton5()
{
}


void ResultForm::OnBnClickedButton6()
{
	CImage image;

	if (cnt > 4)
		cnt = 0;

	switch (cnt)
	{
	case 0:
		image.Load(_T("white.bmp"));//기본
		break;
	case 1:
		image.Load(_T("red.bmp"));//레드
		break;
	case 2:
		image.Load(_T("yellow.bmp"));//노랑
		break;
	case 3:
		image.Load(_T("green.bmp"));//초록
		break;
	case 4:
		image.Load(_T("black.bmp"));//불량 -> 검정
		break;
	default:
		image.Load(_T("white.bmp"));//예외 기본
		break;
	}

	++cnt;

	CRect rect;
	m_Color.GetWindowRect(rect);
	CDC* dc; 
	dc = m_Color.GetDC(); 
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	ReleaseDC(dc);
}


void ResultForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_btempdetect.EnableWindow(FALSE);
	ToolManager::GetInstance()->m_Resform = this;
}


void ResultForm::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CImage image;

	

	switch (ToolManager::GetInstance()->m_Res)
	{
	case RESULT::RES_END:
		image.Load(_T("white.bmp"));//기본
		break;
	case RESULT::RED:
		image.Load(_T("red.bmp"));//레드
		break;
	case RESULT::YELLOW:
		image.Load(_T("yellow.bmp"));//노랑
		break;
	case RESULT::GREEN:
		image.Load(_T("green.bmp"));//초록
		break;
	case RESULT::FAIL:
		image.Load(_T("black.bmp"));//불량 -> 검정
		break;
	default:
		image.Load(_T("white.bmp"));//예외 기본
		break;
	}

	CRect rect;
	m_Color.GetWindowRect(rect);
	CDC* cdc;
	cdc = m_Color.GetDC();
	image.StretchBlt(cdc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	ReleaseDC(cdc);
}






