// ServerForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "ServerForm.h"
#include "ToolManager.h"

// ServerForm

IMPLEMENT_DYNCREATE(ServerForm, CFormView)

ServerForm::ServerForm()
	: CFormView(IDD_ServerForm)
	, m_Port(0)
{
	
}

ServerForm::~ServerForm()
{
}

void ServerForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TCP_PORT, m_Port);
	DDX_Control(pDX, IDC_TCP_IP, m_IP);
	DDX_Control(pDX, IDC_TCP_BUT, m_TCP_BUTTON);
	DDX_Control(pDX, IDC_STATIC_TCP_CON, m_STATIC_TCP);
	DDX_Control(pDX, IDC_LIST_TCP, m_ListTcp);
}

BEGIN_MESSAGE_MAP(ServerForm, CFormView)
	ON_BN_CLICKED(IDC_TCP_BUT, &ServerForm::OnBnClickedTcpBut)
	ON_BN_CLICKED(IDC_BUTTON1, &ServerForm::OnBnClickedButton1)
END_MESSAGE_MAP()


// ServerForm 진단

#ifdef _DEBUG
void ServerForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ServerForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ServerForm 메시지 처리기

// 서버 폼 초기화 함수
void ServerForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ToolManager::GetInstance()->Setserverform(this);
	

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	LVCOLUMN Column;

	UpdateData();

	Column.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	Column.fmt = LVCFMT_LEFT;

	LPWSTR Column_list[2] = { _T("번호"), _T("로그")};
	int cx[2] = { 50, 200};

	int Column_size = sizeof(Column_list) / sizeof(Column_list[0]);
	for (int i = 0; i < Column_size; i++) {
		Column.cx = cx[i];
		Column.pszText = Column_list[i];
		m_ListTcp.InsertColumn(i, &Column);
	}

	Count = 0;
	m_TCPConnect = TRUE;
	m_IP.SetAddress(192, 168, 0, 213);
	m_Port = 6667;
	UpdateData(FALSE);
}


void ServerForm::OnBnClickedTcpBut()
{
	// 소켓 통신 연결, 연결끊기를 정의합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_TCPConnect) {
		m_Client.Create();
		if (m_Client.Connect(IPAddress(), m_Port) == FALSE) {
			AfxMessageBox(_T("ERROR : Failed to connect Server"));
			m_Client.Close();
			return;
		}
		m_TCP_BUTTON.SetWindowText(L"연결끊기");
		m_STATIC_TCP.SetWindowTextW(L"연결됨");
		m_TCPConnect = FALSE;
	}
	else if (!m_TCPConnect) {
		m_Client.Close();
		m_TCP_BUTTON.SetWindowText(L"연결");
		m_STATIC_TCP.SetWindowTextW(L"연결끊김");
		m_TCPConnect = TRUE;
	}
}

// ip 주소 얻어오는 객체
const CString ServerForm::IPAddress() const{
	CString strIPAddr;
	BYTE IP1, IP2, IP3, IP4;

	m_IP.GetAddress(IP1, IP2, IP3, IP4);
	strIPAddr.Format(_T("%d.%d.%d.%d"), IP1, IP2, IP3, IP4);

	return strIPAddr;
}

// 서버에 정보를 송신하는 객체
void ServerForm::ClientTCP(CString strMessage) {
	int nLength = strMessage.GetLength() * sizeof(TCHAR);

	m_Client.Send((LPCTSTR)strMessage, nLength);
}


void ServerForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("asdf");
	ClientTCP(str);
	
}


// 소켓통신 로그
void ServerForm::SetList(CString strMessage) {
	m_ListTcp.InsertItem(Count, (CString(std::to_string(Count + 1).c_str())));
	m_ListTcp.SetItemText(Count, 1, strMessage);
	Count++;
}