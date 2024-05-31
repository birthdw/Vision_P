// ListForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "ListForm.h"
#include "ToolManager.h"


// ListForm

IMPLEMENT_DYNCREATE(ListForm, CFormView)

ListForm::ListForm()
	: CFormView(IDD_ListForm)
{

}

ListForm::~ListForm()
{
}

void ListForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
}

void ListForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_TabCtrl.InsertItem(0, L"detect tab");
	m_TabCtrl.InsertItem(1, L"test tab");

	CRect rt;
	m_TabCtrl.GetWindowRect(&rt);

	m_Detecttab.Create(IDD_DetectTab, &m_TabCtrl);
	m_Detecttab.MoveWindow(0, 0, rt.Width(), rt.Height());
	m_Detecttab.SetWindowPos(NULL, 5, 25, rt.Width() - 10, rt.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_TestTab.Create(IDD_TestTab, &m_TabCtrl);
	m_TestTab.MoveWindow(0, 0, rt.Width(), rt.Height());
	m_TestTab.SetWindowPos(NULL, 5, 25, rt.Width() - 10, rt.Height() - 30, SWP_NOZORDER);

	ToolManager::GetInstance()->m_tab = &m_TabCtrl;
	ToolManager::GetInstance()->SetTab(&m_Detecttab, &m_TestTab);

}

BEGIN_MESSAGE_MAP(ListForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &ListForm::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// ListForm 진단

#ifdef _DEBUG
void ListForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ListForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ListForm 메시지 처리기


void ListForm::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int tabIndex = m_TabCtrl.GetCurSel();

	switch (tabIndex)
	{
	case 0:
		ToolManager::GetInstance()->m_strPickinLst = L"";
		m_Detecttab.ShowWindow(SW_SHOW);
		m_TestTab.ShowWindow(SW_HIDE);
		m_Detecttab.Update();
		break;
	case 1:
		m_Detecttab.ShowWindow(SW_HIDE);
		m_TestTab.ShowWindow(SW_SHOW);

		m_Detecttab.m_List.DeleteAllItems();
		m_Detecttab.Update();


		break;
	}

	*pResult = 0;
}


