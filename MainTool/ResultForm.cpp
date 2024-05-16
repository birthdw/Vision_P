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
	ON_BN_CLICKED(IDC_BUTTON3, &ResultForm::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ResultForm::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &ResultForm::OnBnClickedButton5)
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
}


void ResultForm::OnBnClickedButton2()
{
	// cam off
	ToolManager::GetInstance()->SetKillFrm(true);
	ToolManager::GetInstance()->SetSpecialOn(false);
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
