// TestTab.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "TestTab.h"
#include "ToolManager.h"
#include "CModDlg.h"
#include "AWS.h"
#include "ServerForm.h"


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



	DDX_Control(pDX, IDC_ColorEdit, m_ColorEdit);
	DDX_Control(pDX, IDC_FaultyEdit, m_FaultyEdit);
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









void TestTab::LoadOnlineImage(LPCTSTR url)
{
	CInternetSession session;
	CHttpFile* pFile = NULL;

	try {
		pFile = (CHttpFile*)session.OpenURL(url);
		DWORD dwStatusCode;
		pFile->QueryInfoStatusCode(dwStatusCode);
		if (dwStatusCode == HTTP_STATUS_OK) {
			CFile file;
			CString tempPath;
			GetTempPath(MAX_PATH, tempPath.GetBuffer(MAX_PATH));
			tempPath.ReleaseBuffer();

			CString tempFile = tempPath + GetLast(url);
			file.Open(tempFile, CFile::modeCreate | CFile::modeWrite);
			DWORD dwRead;
			BYTE pBuffer[1024];
			while ((dwRead = pFile->Read(pBuffer, sizeof(pBuffer))) > 0) {
				file.Write(pBuffer, dwRead);
			}
			file.Close();


			CImage image;
			image.Load(tempFile);//예외 기본

			CPaintDC dc(this);
			image.StretchBlt(dc, 0, 0, 700, 467);
		}
		else {
			// 오류
		}
	}
	catch (CInternetException* pEx) {
		pEx->Delete();
	}

	if (pFile)
		pFile->Close();
	session.Close();
}


void TestTab::OnPaint()
{
	UpdateData(TRUE);


	if (ToolManager::GetInstance()->m_strPickinLst != L"")
		LoadOnlineImage(ToolManager::GetInstance()->m_strPickinLst);
	else
	{
		CImage png;
		png.Load(L"ns.png");
		CPaintDC dc(this);
		png.StretchBlt(dc, 0, 0, 700, 467);
	}

	SetDlgItemTextW(IDC_ColorEdit, Color);
	SetDlgItemTextW(IDC_FaultyEdit, Faulty);
	UpdateData(FALSE);

}


void TestTab::OnBnClickedButton1()
{

}


void TestTab::OnBnClickedButton2()
{
	UpdateData(FALSE);
	//수정
	CString c;
	CString f;
	GetDlgItemText(IDC_ColorEdit, c);
	GetDlgItemText(IDC_FaultyEdit, f);
	string co = CT2CA(c);
	string fa = CT2CA(f);
	ToolManager::GetInstance()->m_Serverform->m_aws->RDSupdateData("color", co.c_str(), CurId.c_str());
	ToolManager::GetInstance()->m_Serverform->m_aws->RDSupdateData("faulty", fa.c_str(), CurId.c_str());


	UpdateData(TRUE);
}


void TestTab::OnBnClickedButton5()
{
	//삭제
	ToolManager::GetInstance()->m_Serverform->m_aws->AlldeleteData(CurId.c_str());



}

CString TestTab::GetLast(CString url)
{
	vector<CString> vec;
	CString res = L"";
	for (int i = 0; i < url.GetLength(); ++i)
	{
		if (url[i] != '/')
			res += url[i];
		else
		{
			vec.emplace_back(res);
			res = L"";
		}
		if (i == url.GetLength() - 1)
		{
			vec.emplace_back(res);
			res = L"";
		}
	}


	return CString(vec[vec.size() - 1]);
}

void TestTab::Setcnt(int cnt)
{
	Curcnt = cnt;
}

int TestTab::Getcnt()
{
	return Curcnt;
}
