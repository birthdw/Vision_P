// DetectTab.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "afxdialogex.h"
#include "DetectTab.h"
#include "ToolManager.h"
#include "TestTab.h"

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
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_EDIT1, m_TestTxt);
}


BEGIN_MESSAGE_MAP(DetectTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DetectTab::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &DetectTab::OnNMClickList1)
END_MESSAGE_MAP()


// DetectTab 메시지 처리기


BOOL DetectTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	LVCOLUMN Column;

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	UpdateData();

	Column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	Column.fmt = LVCFMT_LEFT;

	LPWSTR Column_list[4] = { _T("No"), _T("Date") , _T("Result"),_T("File") };
	int cx[4] = { 50, 200,100,300 };

	int Column_size = sizeof(Column_list) / sizeof(Column_list[0]);
	for (int i = 0; i < Column_size; i++) {
		Column.cx = cx[i];
		Column.pszText = Column_list[i];
		m_List.InsertColumn(i, &Column);
	}

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DetectTab::OnBnClickedButton1()
{
	CString teststr;
	m_TestTxt.GetWindowTextW(teststr);
	m_List.InsertItem(Count, (CString(std::to_string(Count + 1).c_str())));
	teststr += L".png";
	m_List.SetItemText(Count, 1, teststr);
	m_List.SetItemText(Count, 2, L"This is test Code");
	++Count;
}








void DetectTab::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int clickindex = m_List.GetSelectionMark();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ToolManager::GetInstance()->m_tab->SetCurSel(1);
	ToolManager::GetInstance()->m_detecttab->ShowWindow(SW_HIDE);
	ToolManager::GetInstance()->m_Testtab->ShowWindow(SW_SHOW);
	CString test = m_List.GetItemText(clickindex, 1);
	CString test2 = m_List.GetItemText(clickindex, 2);
	ToolManager::GetInstance()->m_strPickinLst = test;
	ToolManager::GetInstance()->m_strPickinLst2 = test2;


	*pResult = 0;
}
