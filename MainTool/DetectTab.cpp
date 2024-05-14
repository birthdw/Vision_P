// DetectTab.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "DetectTab.h"


// DetectTab 대화 상자

IMPLEMENT_DYNAMIC(DetectTab, CDialog)

DetectTab::DetectTab(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DetectTab, pParent)
{

}

DetectTab::~DetectTab()
{
}

void DetectTab::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DetectTab, CDialog)
END_MESSAGE_MAP()


// DetectTab 메시지 처리기
