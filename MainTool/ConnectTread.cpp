#include "pch.h"
#include "ConnectTread.h"
#include "ServerForm.h"
#include "ToolManager.h"
#include "ResultForm.h"
#include "DetectTab.h"

#define WM_SOCKET_THREAD_FINISHED (WM_USER + 1)

UINT ThreadRecv(LPVOID pParam) {
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;
	
	while (1) {
		CString str = thisObj->GetSocketMessage();
		if (str != _T("")) {
			if (str.Find(_T('/')) != -1)
			{
				// '/'가 포함되어 있는 경우

				// '/'로 문자열을 분할하여 첫 번째 단계의 결과를 저장할 벡터 생성
				std::vector<CString> firstSplit = thisObj->SplitCString(str, _T("/"));

				// 첫 번째 단계의 결과를 반복하여 처리
				for (const auto& part : firstSplit)
				{
					int colonPos = part.Find(':');
					if (colonPos != -1)
					{
						CString betweenColonAndSlash = part.Mid(colonPos + 1);

						if (betweenColonAndSlash.Find(_T("GRAP")) != -1)
						{
							// "GRAP" 포함하면 전달
							ToolManager::GetInstance()->bGrap = true;
							ToolManager::GetInstance()->m_Serverform->ClientTCP(betweenColonAndSlash);
						}

						else if (betweenColonAndSlash.Find(_T("DONE")) != -1)
						{
							// "DONE을 포함하면 전달
							CString str = _T("START");
							ToolManager::GetInstance()->m_Serverform->ClientTCP(str);
						}

					}
				}
			}
			else
			{
				// '/'가 포함되어 있지 않은 경우
				// 전체 문자열을 그대로 출력
				CString str_ar = _T("올바른 명령이 아닙니다");
				ToolManager::GetInstance()->m_Serverform->ClientTCP(str_ar);
			}
		}
		Sleep(100);
	}
}

UINT initawsT(LPVOID pParam)//서버
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

			if (thisObj->GetAWS() == nullptr) {
				thisObj->SetAwsInfo(AWSINFO::SEVERSTART);
			}
			else thisObj->SetAwsInfo(AWSINFO::STAY);
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSSEND) {
			string info = "('" + thisObj->GetAwsColor() + "', '" + thisObj->GetAwsColor() + "')";
			thisObj->SetAwsColor("");
			thisObj->SetAwsFaulty("");

			thisObj->GetAWS()->Allinput(thisObj->GetDate(), info.c_str(), "BOX.jpg");

			thisObj->SetAwsInfo(AWSINFO::STAY);
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSCHEAK) {
			thisObj->GetAWS()->RDSckeckConnection();
			thisObj->SetAwsInfo(AWSINFO::STAY);
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSMODIFY) {	
			thisObj->GetAWS()->RDSupdateData("color", thisObj->GetModifyColor().c_str(), thisObj->GetModifyCurId().c_str());
			thisObj->GetAWS()->RDSupdateData("faulty", thisObj->GetModifyFaulty().c_str(), thisObj->GetModifyCurId().c_str());
			thisObj->SetAwsInfo(AWSINFO::STAY);
		}

		/*thisObj->SETBoxlist(thisObj->GetAWS()->RDSjoinData());
		TRACE("%d\r\n", thisObj->GetBoxlist());*/
		Sleep(100);
	}

	return 0;
}


UINT ThreadSocket(LPVOID pParam)//통신
{
	ServerForm* thisObj = static_cast<ServerForm*>(pParam);

	CSocketClient hSocket;
	hSocket.Create();
	CString strMessage = _T("END");
	int nLength = strMessage.GetLength() * sizeof(TCHAR);


	BOOL success = FALSE;
	if (thisObj->GetTCPConnect()) {
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
		thisObj->SetControlColor(STATUCOLOR::SOCKETRED);
		success = TRUE;
	}

	// 메인 스레드에 메시지 보내기
	::PostMessage(thisObj->GetSafeHwnd(), WM_SOCKET_THREAD_FINISHED, (WPARAM)success, 0);

	return 0;
}


UINT COLORRODING(LPVOID pParam) //MFC 연결 상태 그리는 스레드
{
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;

	while (1) 
	{
		if (thisObj->GetThreadColor() == COLORTHREAD::THREADEXIT) {
			return 0;
		}
		else if (thisObj->GetThreadColor() == COLORTHREAD::THREADRUN) {
			thisObj->InvalidateRect(NULL, FALSE);

			if (thisObj->m_ListTcp.GetItemCount() > 0) {
				thisObj->GetDlgItem(IDC_LOG_BUT)->EnableWindow(true);
			}
			else {
				thisObj->GetDlgItem(IDC_LOG_BUT)->EnableWindow(false);
			}
		}
		Sleep(200);
	}
}

UINT ThreadCamera(LPVOID pParam) {
	ToolManager* thisObj;
	thisObj = (ToolManager*)pParam;
	
	thisObj->cap >> thisObj->frame;
	vector<Detection> output = thisObj->inf->runInference(thisObj->frame);
	thisObj->m_Resform->camera = true;
	
	return 0;
}

UINT ThreadCameraButton(LPVOID pParam) {
	ResultForm* thisObj;
	thisObj = (ResultForm*)pParam;

	while (1) {
		if (!thisObj->camera) {
			thisObj->GetDlgItem(IDC_BStart)->EnableWindow(false);
			thisObj->GetDlgItem(IDC_BStop)->EnableWindow(false);
			thisObj->GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
			thisObj->GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
		}
		else {
			thisObj->GetDlgItem(IDC_BStart)->EnableWindow(true);
			thisObj->GetDlgItem(IDC_BStop)->EnableWindow(true);
			thisObj->GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
			thisObj->GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
			return 0;
		}
	}
	return 0;
}

UINT ThreadUpdate(LPVOID pParam) {
	DetectTab* thisObj;
	thisObj = (DetectTab*)pParam;
	CString youngID;

	while (1) {
		if (thisObj->Threadupdate) return 0;

		else {
			CString oldID = thisObj->Update(false);
			if (oldID != _T("")) {
				if (oldID != youngID) {
					youngID = oldID;
					thisObj->Update(true);
				}
			}	
		}
		Sleep(100);
	}
	return 0;
}

