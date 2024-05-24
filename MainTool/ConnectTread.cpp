#include "pch.h"
#include "ConnectTread.h"
#include "ServerForm.h"
#include "ToolManager.h"
#include "ResultForm.h"
#include "DetectTab.h"

#define WM_SOCKET_THREAD_FINISHED (WM_USER + 1)


UINT initawsT(LPVOID pParam)//����
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
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSSEND) {
			string info = "('" + thisObj->m_awscolor + "', '" + thisObj->m_awsfaulty + "')";
			thisObj->m_awscolor = "";
			thisObj->m_awsfaulty = "";

			thisObj->m_aws->Allinput(info.c_str(), "BOX.jpg");
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSCHEAK) {
			thisObj->m_aws->RDSckeckConnection();
		}
		else if (thisObj->GetAwsInfo() == AWSINFO::AWSMODIFY) {	
			thisObj->m_aws->RDSupdateData("color", thisObj->m_modifyColor.c_str(), thisObj->m_modifyCurId.c_str());
			thisObj->m_aws->RDSupdateData("faulty", thisObj->m_modifyFaulty.c_str(), thisObj->m_modifyCurId.c_str());
		}

		// ����Ʈ�� �ֱ������� �ҷ���
		if (thisObj->GetAwslist() == AWSINFO::AWSLIST) {
			thisObj->m_boxrun = false;
			thisObj->m_boxlist = thisObj->m_aws->RDSjoinData();
			TRACE("%d\r\n", thisObj->m_boxlist);
			thisObj->m_boxrun = true;
		}

		thisObj->SetAwslist(AWSINFO::STAY);
		thisObj->SetAwsInfo(AWSINFO::STAY);
		Sleep(100);
	}

	return 0;
}


UINT ThreadSocket(LPVOID pParam)//���
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

	// ���� �����忡 �޽��� ������
	::PostMessage(thisObj->GetSafeHwnd(), WM_SOCKET_THREAD_FINISHED, (WPARAM)success, 0);

	return 0;
}


UINT COLORRODING(LPVOID pParam) //MFC ���� ���� �׸��� ������
{
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;

	while (1) 
	{
		if (thisObj->m_ThreadColor == COLORTHREAD::THREADEXIT) {
			return 0;
		}
		else if (thisObj->m_ThreadColor == COLORTHREAD::THREADRUN) {
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

