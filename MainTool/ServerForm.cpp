﻿// ServerForm.cpp: 구현 파일
//

#include "pch.h"
#include "MainTool.h"
#include "ServerForm.h"
#include "ToolManager.h"
#include "ConnectTread.h"
#include "ResultForm.h"

#define WM_SOCKET_THREAD_FINISHED (WM_USER + 1)

// ServerForm

IMPLEMENT_DYNCREATE(ServerForm, CFormView)

ServerForm::ServerForm()
	: CFormView(IDD_ServerForm)
	, m_Port(0)
{

}

ServerForm::~ServerForm()
{
	m_awsinfo = AWSINFO::AWSEXIT;
	m_ThreadColor = COLORTHREAD::THREADEXIT;	
	if (m_aws != nullptr) { delete m_aws; m_aws = nullptr; }
}

void ServerForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TCP_PORT, m_Port);
	DDX_Control(pDX, IDC_TCP_IP, m_IP);
	DDX_Control(pDX, IDC_TCP_BUT, m_TCP_BUTTON);
	DDX_Control(pDX, IDC_LIST_TCP, m_ListTcp);
	DDX_Control(pDX, IDC_STATE, m_StateColor);
	DDX_Control(pDX, IDC_SERCOLOR, m_ServerColor);
}

BEGIN_MESSAGE_MAP(ServerForm, CFormView)
	ON_BN_CLICKED(IDC_TCP_BUT, &ServerForm::OnBnClickedTcpBut)
	ON_WM_PAINT()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TCP, &ServerForm::OnLvnItemchangedListTcp)
	ON_MESSAGE(WM_SOCKET_THREAD_FINISHED, &ServerForm::OnSocketThreadFinished)
	ON_BN_CLICKED(IDC_LOG_BUT, &ServerForm::OnBnClickedLogBut)
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

	LPWSTR Column_list[4] = { _T("번호"),_T("송수신"), _T("로그"), _T("시간")};
	int cx[4] = { 100, 100, 400, 200 };

	int Column_size = sizeof(Column_list) / sizeof(Column_list[0]);
	for (int i = 0; i < Column_size; i++) {
		Column.cx = cx[i];
		Column.pszText = Column_list[i];
		m_ListTcp.InsertColumn(i, &Column);
	}

	m_IP.SetAddress(192, 168, 0, 215);
	m_Port = 6667;
	
	UpdateData(FALSE);
	m_awsinfo = AWSINFO::SEVERSTART;
	AfxBeginThread(COLORRODING, this);

	AfxBeginThread(initawsT, this);
}


void ServerForm::OnBnClickedTcpBut()
{
	// 소켓 통신 연결, 연결끊기를 정의합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_SocketThreadSWICHT) 
	{
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
	SetList(_T("송신"),strMessage);
	
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
				m_SocketThreadSWICHT = TRUE;
				m_TCP_BUTTON.SetWindowText(L"연결");
				GetDlgItem(IDC_TCP_BUT)->EnableWindow(true);
				m_Client.Close();
				return 0;
			}
			m_TCP_BUTTON.SetWindowText(L"연결끊기");
			m_TCPConnect = FALSE;
			m_ControlColor = STATUCOLOR::SOCKETGREEN;
			ToolManager::GetInstance()->m_Resform->Setbutton(true);
		}
		else if (!m_TCPConnect) {
			ClientTCP(_T("END"));
			m_Client.Close();
			m_TCP_BUTTON.SetWindowText(L"연결");
			m_TCPConnect = TRUE;
			m_ControlColor = STATUCOLOR::SOCKETRED;
			ToolManager::GetInstance()->m_Resform->Setbutton(false);
		}
	}
	else
	{
		AfxMessageBox(_T("Failed to connect socket."));
		m_ControlColor = STATUCOLOR::SOCKETRED;
		ToolManager::GetInstance()->m_Resform->Setbutton(false);
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
void ServerForm::SetList(CString str,CString strMessage) 
{
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	CString time_s = CString(std::to_string(t->tm_year + 1900).c_str()) + _T("/") +
		CString(std::to_string(t->tm_mon + 1).c_str()) + _T("/") +
		CString(std::to_string(t->tm_hour).c_str()) + _T("/") +
		CString(std::to_string(t->tm_min).c_str()) + _T("/") +
		CString(std::to_string(t->tm_sec).c_str());
	m_ListTcp.InsertItem(0, (CString(std::to_string(Count + 1).c_str())));
	m_ListTcp.SetItemText(0, 1, str);
	m_ListTcp.SetItemText(0, 2, strMessage);
	m_ListTcp.SetItemText(0, 3, static_cast<LPCTSTR>(time_s));
	Count++;
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
	SetControlColor(STATUCOLOR::SERVERGREEN);
	SetServerSwitch(STATUCOLOR::SERVERGREEN);
}

vector<CString> ServerForm::SplitCString(const CString& str, const CString& delimiter)
{
	// 문자열을 분할하여 저장할 벡터 생성
	std::vector<CString> tokens;

	// 시작 위치 초기화
	int startPos = 0;

	// 문자열을 주어진 구분자(delimiter)로 분할하고 첫 번째 토큰 가져오기
	CString token = str.Tokenize(delimiter, startPos);

	// 토큰이 비어 있지 않은 동안 반복
	while (!token.IsEmpty())
	{
		// 토큰을 벡터에 추가
		tokens.push_back(token);
		// 다음 토큰을 가져오기 위해 시작 위치 이동
		token = str.Tokenize(delimiter, startPos);
	}

	// 분할된 토큰들을 저장한 벡터 반환
	return tokens;
}


AWSINFO ServerForm::GetAwsInfo()
{
	return m_awsinfo;
}


void ServerForm::SetAwsInfo(AWSINFO pAWS)
{
	m_awsinfo = pAWS;
}

void ServerForm::SetModify(string color, string faulty, string curId)
{
	m_modifyColor = color;
	m_modifyFaulty = faulty;
	m_modifyCurId = curId;
	m_awsinfo = AWSINFO::AWSMODIFY;
}

void ServerForm::SetAwsColor(string set)
{
	m_awscolor = set;
}

string ServerForm::GetAwsColor()
{
	return m_awscolor;
}

void ServerForm::SetAwsFaulty(string set)
{
	m_awsfaulty = set;
}

string ServerForm::GetAwsFaulty()
{
	return m_awsfaulty;
}

void ServerForm::SetAwsFilename(string set)
{
	m_awsfilename = set;
}

string ServerForm::GetAwsFilename()
{
	return m_awsfilename;
}

void ServerForm::SetModifyColor(string set)
{
	m_modifyColor = set;
}

string ServerForm::GetModifyColor()
{
	return m_modifyColor;
}

void ServerForm::SetModifyFaulty(string set)
{
	m_modifyFaulty = set;
}

string ServerForm::GetModifyFaulty()
{
	return m_modifyFaulty;
}

void ServerForm::SetModifyCurId(string set)
{
	m_modifyCurId = set;
}

string ServerForm::GetModifyCurId()
{
	return m_modifyCurId;
}

void ServerForm::SetDate(string set)
{
	m_awsdate = set;
}

string ServerForm::GetDate()
{
	return m_awsdate;
}

void ServerForm::SetClientClose()
{
	m_Client.Close();
}

void ServerForm::SetThreadColor(COLORTHREAD set)
{
	m_ThreadColor = set;
}

COLORTHREAD ServerForm::GetThreadColor()
{
	return m_ThreadColor;
}

void ServerForm::SetControlColor(STATUCOLOR set)
{
	m_ControlColor = set;
}

STATUCOLOR ServerForm::GetControlColor()
{
	return m_ControlColor;
}

void ServerForm::SetServerSwitch(STATUCOLOR set)
{
	m_ServerSwitch = set;
}

STATUCOLOR ServerForm::GetServerSwitch()
{
	return m_ServerSwitch;
}

void ServerForm::SETTCPConnect(BOOL set)
{
	m_TCPConnect = set;
}

BOOL ServerForm::GetTCPConnect()
{
	return m_TCPConnect;
}

void ServerForm::SETBoxlist(vector<AWSLIST> set)
{
	m_boxlist = set;
}

vector<AWSLIST> ServerForm::GetBoxlist()
{
	return m_boxlist;
}

AWS* ServerForm::GetAWS()
{
	return m_aws;
}


void ServerForm::OnLvnItemchangedListTcp(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void ServerForm::OnBnClickedLogBut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Count = 0;
	m_ListTcp.DeleteAllItems();

}
