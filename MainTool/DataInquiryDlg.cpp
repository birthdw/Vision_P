// DataInquiryDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "DataInquiryDlg.h"


// DataInquiryDlg 대화 상자

IMPLEMENT_DYNAMIC(DataInquiryDlg, CDialogEx)

DataInquiryDlg::DataInquiryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DataInquiry, pParent)
{

}

DataInquiryDlg::~DataInquiryDlg()
{
}

void DataInquiryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, EndTime);
	DDX_Control(pDX, IDC_COMBO2, m_ColorBox);
	DDX_Control(pDX, IDC_COMBO3, m_FaultyBox);
}


BEGIN_MESSAGE_MAP(DataInquiryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DataInquiryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// DataInquiryDlg 메시지 처리기


void DataInquiryDlg::OnBnClickedButton1()
{
	









}
