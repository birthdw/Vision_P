﻿// ServerForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "ServerForm.h"
#include "ToolManager.h"

#define WM_SOCKET_THREAD_FINISHED (WM_USER + 1)

// ServerForm

IMPLEMENT_DYNCREATE(ServerForm, CFormView)

UINT initawsT(LPVOID pParam);
UINT initawsT(LPVOID pParam)
{
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;
	while (1) {
		if (thisObj->GetAwsInfo() == AWSINFO::AWSEXIT) {
			return 0;
		}
		if (thisObj->GetAwsInfo() == AWSINFO::SEVERSTART) {
			TRACE(_T("Thread Index "));
			thisObj->initaws();
			thisObj->SetAwsInfo(AWSINFO::STAY);
		}	
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSSEND) {
			thisObj->m_aws->Allinput("color, faulty", "('red', 'True')", "dog.png");
			thisObj->SetAwsInfo(AWSINFO::STAY);

		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSCHEAK) {
			thisObj->m_aws->RDSckeckConnection();
			thisObj->SetAwsInfo(AWSINFO::STAY);
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSLIST) {
			thisObj->m_boxlist = thisObj->m_aws->RDSjoinData();
			TRACE("%d\r\n", thisObj->m_boxlist);
			thisObj->SetAwsInfo(AWSINFO::STAY);
		}
		thisObj->InvalidateRect(NULL, FALSE);
		Sleep(100);
	}
	
	return 0;
}

UINT ThreadSocket(LPVOID pParam);
UINT ThreadSocket(LPVOID pParam)
{
	ServerForm* thisObj = static_cast<ServerForm*>(pParam);

	CSocketClient hSocket;
	hSocket.Create();
	CString strMessage = _T("END");
	int nLength = strMessage.GetLength() * sizeof(TCHAR);
	

	BOOL success = FALSE;
	if (thisObj->m_TCPConnect) {
		if (hSocket.Connect(thisObj->IPAddress(), thisObj->m_Port) == FALSE)
		{
			hSocket.Close();
			success = FALSE;
		}
		else
		{
			Sleep(100);
			hSocket.Send((LPCTSTR)strMessage, nLength);
			hSocket.Close();
			success = TRUE;
		}
	}
	else {
		thisObj->m_ControlColor = STATUCOLOR::SOCKETRED;
		success = TRUE;
	}
	
	// 메인 스레드에 메시지 보내기
	::PostMessage(thisObj->GetSafeHwnd(), WM_SOCKET_THREAD_FINISHED, (WPARAM)success, 0);

	return 0;
}

UINT COLORRODING(LPVOID pParam);
UINT COLORRODING(LPVOID pParam) {
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;

	while (1) {
		if (thisObj->m_ThreadColor == COLORTHREAD::THREADEXIT) {
			return 0;
		}	
		else if (thisObj->m_ThreadColor == COLORTHREAD::THREADRUN) {
			thisObj->InvalidateRect(NULL, FALSE);
			Sleep(100);
		}	
	}
}

ServerForm::ServerForm()
	: CFormView(IDD_ServerForm)
	, m_Port(0)
{

}

ServerForm::~ServerForm()
{
	m_ThreadColor = COLORTHREAD::THREADEXIT;
}

void ServerForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TCP_PORT, m_Port);
	DDX_Control(pDX, IDC_TCP_IP, m_IP);
	DDX_Control(pDX, IDC_TCP_BUT, m_TCP_BUTTON);
	DDX_Control(pDX, IDC_STATIC_TCP_CON, m_STATIC_TCP);
	DDX_Control(pDX, IDC_LIST_TCP, m_ListTcp);
	DDX_Control(pDX, IDC_STATE, m_StateColor);
	DDX_Control(pDX, IDC_SERCOLOR, m_ServerColor);
}

BEGIN_MESSAGE_MAP(ServerForm, CFormView)
	ON_BN_CLICKED(IDC_TCP_BUT, &ServerForm::OnBnClickedTcpBut)
	ON_BN_CLICKED(IDC_BUTTON1, &ServerForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ServerForm::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TCP, &ServerForm::OnLvnItemchangedListTcp)
	ON_MESSAGE(WM_SOCKET_THREAD_FINISHED, &ServerForm::OnSocketThreadFinished)
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

	LPWSTR Column_list[2] = { _T("번호"), _T("로그") };
	int cx[2] = { 50, 200 };

	int Column_size = sizeof(Column_list) / sizeof(Column_list[0]);
	for (int i = 0; i < Column_size; i++) {
		Column.cx = cx[i];
		Column.pszText = Column_list[i];
		m_ListTcp.InsertColumn(i, &Column);
	}

	m_IP.SetAddress(192, 168, 0, 213);
	m_Port = 6667;
	
	UpdateData(FALSE);
	m_awsinfo = AWSINFO::SEVERSTART;
	AfxBeginThread(COLORRODING, this);
	AfxBeginThread(initawsT, this);
}


void ServerForm::OnBnClickedTcpBut()
{

	onlyone = false;
	
	// 소켓 통신 연결, 연결끊기를 정의합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_SocketThreadSWICHT) {
		GetDlgItem(IDC_TCP_BUT)->EnableWindow(false);
		m_ControlColor = STATUCOLOR::SOCKETYELLOW;
		m_SocketThreadSWICHT = FALSE;
		UpdateData(TRUE);
		AfxBeginThread(ThreadSocket, this);
	}
}


// ip 주소 얻어오는 객체
const CString ServerForm::IPAddress() const {
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
	CString str = _T("TEST");
	ClientTCP(str);

}


LRESULT ServerForm::OnSocketThreadFinished(WPARAM wParam, LPARAM lParam)
{
	BOOL success = static_cast<BOOL>(wParam);

	if (success)
	{
		UpdateData(TRUE);

		if (m_TCPConnect) {
			m_Client.Create();
			if (m_Client.Connect(IPAddress(), m_Port) == FALSE) {
				AfxMessageBox(_T("ERROR : Failed to connect Server"));
				m_Client.Close();
				return 0;
			}
			m_TCP_BUTTON.SetWindowText(L"연결끊기");
			m_STATIC_TCP.SetWindowTextW(L"연결됨");
			m_TCPConnect = FALSE;
			m_ControlColor = STATUCOLOR::SOCKETGREEN;
		}
		else if (!m_TCPConnect) {
			ClientTCP(_T("END"));
			m_Client.Close();
			m_TCP_BUTTON.SetWindowText(L"연결");
			m_STATIC_TCP.SetWindowTextW(L"연결끊김");
			m_TCPConnect = TRUE;
			m_ControlColor = STATUCOLOR::SOCKETRED;
		}
	}
	else
	{
		AfxMessageBox(_T("Failed to connect socket."));
		m_ControlColor = STATUCOLOR::SOCKETRED;
	}

	
	m_SocketThreadSWICHT = TRUE;
	GetDlgItem(IDC_TCP_BUT)->EnableWindow(true);

	return 0;
}


void ServerForm::exit_s3()
{
	ShutdownAPI(m_options);
}


// 소켓통신 로그
void ServerForm::SetList(CString strMessage) {
	m_ListTcp.InsertItem(Count, (CString(std::to_string(Count + 1).c_str())));
	m_ListTcp.SetItemText(Count, 1, strMessage);
	Count++;
}

void ServerForm::OnBnClickedButton2()
{
	//m_aws->PutObject("dog.png");

	//m_aws->Allinput("color, faulty", "('red', 'True')","dog.png");

	m_awsinfo = AWSINFO::AWSSEND;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ServerForm::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	switch (m_ControlColor)
	{
	case STATUCOLOR::SERVERRED:
		m_SColor = L"red";
		m_ControlColor = STATUCOLOR::STAY;
		break;
	case STATUCOLOR::SERVERYELLOW:
		m_SColor = L"yellow";
		m_ControlColor = STATUCOLOR::STAY;
		break;
	case STATUCOLOR::SERVERGREEN:
		m_SColor = L"green";
		m_ControlColor = STATUCOLOR::STAY;
		break;
	case STATUCOLOR::SOCKETRED:
		m_KColor = L"red";
		break;
	case STATUCOLOR::SOCKETYELLOW:
		m_KColor = L"yellow";
		break;
	case STATUCOLOR::SOCKETGREEN:
		m_KColor = L"green";
		break;
	}

	CString SERVERCOLOR = m_SColor + L".bmp";
	CString SOCKETCOLOR = m_KColor + L".bmp";

	ToolManager::GetInstance()->RenderImg(&m_ServerColor, SERVERCOLOR);
	ToolManager::GetInstance()->RenderImg(&m_StateColor, SOCKETCOLOR);
}

void ServerForm::initaws()
{
	InitAPI(m_options);
	if (m_aws == nullptr) {
		m_aws = new AWS();
	}
	else {
		exit_s3();
		delete m_aws;
		m_aws = new AWS();
	}
	m_ControlColor = STATUCOLOR::SERVERGREEN;
}

AWSINFO ServerForm::GetAwsInfo()
{
	return m_awsinfo;
}

void ServerForm::SetAwsInfo(AWSINFO pAWS)
{
	m_awsinfo = pAWS;
}


void ServerForm::OnLvnItemchangedListTcp(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
