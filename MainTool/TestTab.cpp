// TestTab.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "TestTab.h"
#include "ToolManager.h"
#include "CModDlg.h"
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


	if(ToolManager::GetInstance()->m_strPickinLst !=L"")
		LoadOnlineImage(ToolManager::GetInstance()->m_strPickinLst);
	else
	{
		CImage png;
		CPaintDC dc(this);
		png.StretchBlt(dc, 0, 0, 700, 467);
		png.Load(L"ns.png");
	}

	SetDlgItemTextW(IDC_EDIT1,ToolManager::GetInstance()->m_strPickinLst2);
	UpdateData(FALSE);

}


void TestTab::OnBnClickedButton1()
{
	
}


void TestTab::OnBnClickedButton2()
{
	CModDlg dlg;
	if (dlg.DoModal() == IDOK)
	{

	}

}


void TestTab::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

CString TestTab::GetLast(CString url)
{
	vector<CString> vec;
	CString res=L"";
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


	return CString(vec[vec.size()-1]);
}

void TestTab::Setcnt(int cnt)
{
	Curcnt = cnt;
}

int TestTab::Getcnt()
{
	return Curcnt;
}
