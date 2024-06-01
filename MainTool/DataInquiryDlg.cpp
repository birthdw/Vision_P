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
}


BEGIN_MESSAGE_MAP(DataInquiryDlg, CDialogEx)
END_MESSAGE_MAP()


// DataInquiryDlg 메시지 처리기
