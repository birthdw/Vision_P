// TestTab.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "TestTab.h"
#include "ToolManager.h"

// TestTab 대화 상자

IMPLEMENT_DYNAMIC(TestTab, CDialog)

TestTab::TestTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TestTab, pParent)
{

}

TestTab::~TestTab()
{
}

void TestTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);




	DDX_Control(pDX, IDC_EDIT1, m_Testtxt);
}


BEGIN_MESSAGE_MAP(TestTab, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &TestTab::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &TestTab::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &TestTab::OnBnClickedButton5)
END_MESSAGE_MAP()


// TestTab 메시지 처리기




BOOL TestTab::OnInitDialog()
{
	CDialog::OnInitDialog();







	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TestTab::OnPaint()
{
	UpdateData(TRUE);
	CImage png;
	HRESULT res;
	if(ToolManager::GetInstance()->m_strPickinLst !=L"")
		 res = png.Load(ToolManager::GetInstance()->m_strPickinLst);
	else
		 res = png.Load(L"ns.png");

	if (res == S_OK)
	{
		CPaintDC dc(this);
		png.StretchBlt(dc, 0, 0, 640, 480);
		SetDlgItemTextW(IDC_EDIT1,ToolManager::GetInstance()->m_strPickinLst2);
	}
	UpdateData(FALSE);
}


void TestTab::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void TestTab::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void TestTab::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
