// CModDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "CModDlg.h"
#include "ToolManager.h"
#include "TestTab.h"
// CModDlg 대화 상자

IMPLEMENT_DYNAMIC(CModDlg, CDialogEx)

CModDlg::CModDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Mod, pParent)
{

}

CModDlg::~CModDlg()
{
}

void CModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Modtext);
}


BEGIN_MESSAGE_MAP(CModDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CModDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CModDlg 메시지 처리기


void CModDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	CString str;
	Modtext.GetWindowTextW(str);
	if (str != L"")
	{
		int idx = ToolManager::GetInstance()->m_Testtab->Getcnt();
		ToolManager::GetInstance()->Mod_Txt(idx,2, str);
		ToolManager::GetInstance()->Set_Mod_Txt(2, str);
	}
	UpdateData(false);
}
