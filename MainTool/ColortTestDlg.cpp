// ColortTestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "ColortTestDlg.h"
#include "ToolManager.h"


// ColortTestDlg 대화 상자

IMPLEMENT_DYNAMIC(ColortTestDlg, CDialogEx)

ColortTestDlg::ColortTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COLORTEST, pParent)
{

}

ColortTestDlg::~ColortTestDlg()
{
}

void ColortTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, redmin);
	DDX_Control(pDX, IDC_EDIT2, redmax);
	DDX_Control(pDX, IDC_EDIT5, greenmin);
	DDX_Control(pDX, IDC_EDIT6, greenmax);
	DDX_Control(pDX, IDC_EDIT3, yellowmin);
	DDX_Control(pDX, IDC_EDIT4, yellowmax);
}


BEGIN_MESSAGE_MAP(ColortTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ColortTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ColortTestDlg 메시지 처리기


void ColortTestDlg::OnBnClickedButton1()
{
	CString Credmin;
	CString Credmax;
	CString Cyellowmin;
	CString Cyellowmax;
	CString Cgreenmin;
	CString Cgreenmax;

	GetDlgItemText(IDC_EDIT1, Credmin);
	GetDlgItemText(IDC_EDIT2, Credmax);
	GetDlgItemText(IDC_EDIT3, Cyellowmin);
	GetDlgItemText(IDC_EDIT4, Cyellowmax);
	GetDlgItemText(IDC_EDIT5, Cgreenmin);
	GetDlgItemText(IDC_EDIT6, Cgreenmax);


	int rmin = stoi(string(CT2CA(Credmin)));
	int rmax = stoi(string(CT2CA(Credmax)));
	int ymin = stoi(string(CT2CA(Cyellowmin)));
	int ymax = stoi(string(CT2CA(Cyellowmax)));
	int gmin = stoi(string(CT2CA(Cgreenmin)));
	int gmax = stoi(string(CT2CA(Cgreenmax)));



	ToolManager::GetInstance()->rmin = rmin;
	ToolManager::GetInstance()->rmax = rmax;
	ToolManager::GetInstance()->ymin = ymin;
	ToolManager::GetInstance()->ymax = ymax;
	ToolManager::GetInstance()->gmin = gmin;
	ToolManager::GetInstance()->gmax = gmax;

}
