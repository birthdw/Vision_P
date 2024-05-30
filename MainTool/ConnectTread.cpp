#include "pch.h"
#include "ConnectTread.h"
#include "ServerForm.h"
#include "ToolManager.h"
#include "ResultForm.h"
#include "DetectTab.h"
#include "TestTab.h"

#define WM_SOCKET_THREAD_FINISHED (WM_USER + 1)


// AWS ���� ������
UINT initawsT(LPVOID pParam)//����
{
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;

	while (1) 
	{
		switch (thisObj->GetAwsInfo()) 
		{

			// AWS ���� ������ ����
			case AWSINFO::AWSEXIT:
			{
				return 0;
			}
				

			// AWS ���� ����
			case AWSINFO::SEVERSTART:
			{
				TRACE(_T("Thread Index "));
				thisObj->initaws();

				// ���� ��Ʈ����
				if (thisObj->GetAWS() == nullptr) 
				{
					thisObj->ServerState(STATUCOLOR::SERVERRED);
					thisObj->SetAwsInfo(AWSINFO::SEVERSTART);			
				}
				else thisObj->SetAwsInfo(AWSINFO::STAY);
				break;
			}


			// AWS ���� ����
			case AWSINFO::AWSSEND:
			{
				string info = "('" + thisObj->GetAwsColor() + "', '" + thisObj->GetAwsFaulty() + "')";
				thisObj->SetAwsColor("");
				thisObj->SetAwsFaulty("");

				thisObj->GetAWS()->Allinput(thisObj->GetDate(), info.c_str(), thisObj->GetAwsFilename());

				thisObj->SetAwsInfo(AWSINFO::STAY);
				break;
			}
				

			// ���ö� ����� ���� ������ ����
			case AWSINFO::AWSTEMPLIST:
			{
				ToolManager* pInstance = ToolManager::GetInstance();
				for (int i = 0; i < pInstance->m_TempVec.size(); ++i)
				{
					string info = "('" + pInstance->m_TempVec[i].color + "', '" + pInstance->m_TempVec[i].faulty + "')";
					thisObj->GetAWS()->Allinput(pInstance->m_TempVec[i].date, info.c_str(), pInstance->m_TempVec[i].filename);
				}
				pInstance->m_TempVec.clear();
				thisObj->SetAwsInfo(AWSINFO::STAY);
				break;
			}


			// ���� ���� üũ
			case AWSINFO::AWSCHEAK:
			{
				thisObj->GetAWS()->RDSckeckConnection();
				thisObj->SetAwsInfo(AWSINFO::STAY);
				break;
			}
				

			// ����� ���� ����
			case AWSINFO::AWSMODIFY:
			{
				ToolManager::GetInstance()->m_Testtab->GetButtonState(false);
				thisObj->GetAWS()->RDSupdateData("color", thisObj->GetModifyColor().c_str(), thisObj->GetModifyCurId().c_str());
				thisObj->GetAWS()->RDSupdateData("faulty", thisObj->GetModifyFaulty().c_str(), thisObj->GetModifyCurId().c_str());
				thisObj->SetAwsInfo(AWSINFO::STAY);
				ToolManager::GetInstance()->m_Testtab->GetButtonState(true);
				break;
			}
				
			case AWSINFO::STAY:
			{
				thisObj->SETBoxlist(thisObj->GetAWS()->RDSjoinData());
				//TRACE("%d\r\n", thisObj->GetBoxlist());
				break;
			}

			// ���� ����Ʈ �ҷ�����
			default:	
			{
				thisObj->SETBoxlist(thisObj->GetAWS()->RDSjoinData());
				//TRACE("%d\r\n", thisObj->GetBoxlist());
				break;
			}
		
		}
		Sleep(100);
	}

	return 0;
}


// ������� ù ���� ������
UINT ThreadSocket(LPVOID pParam)
{
	ServerForm* thisObj = static_cast<ServerForm*>(pParam);

	CSocketClient hSocket;
	hSocket.Create();
	CString strMessage = _T("END");
	int nLength = strMessage.GetLength() * sizeof(TCHAR);


	BOOL success = FALSE;

	// ���� üũ
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

	// ���� ����
	else {
		thisObj->SetControlColor(STATUCOLOR::SOCKETRED);
		success = TRUE;
	}

	// ���� �����忡 �޽��� ������ (�̺�Ʈ)
	::PostMessage(thisObj->GetSafeHwnd(), WM_SOCKET_THREAD_FINISHED, (WPARAM)success, 0);

	return 0;
}


//MFC ���� ���� üũ ������
UINT COLORRODING(LPVOID pParam) 
{
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;

	while (1) 
	{
		
		// ������ �ڿ� ����
		if (thisObj->GetThreadColor() == COLORTHREAD::THREADEXIT) {
			return 0;
		}

		// paint üũ
		else if (thisObj->GetThreadColor() == COLORTHREAD::THREADRUN) {
			thisObj->InvalidateRect(NULL, FALSE);

			// �α� ���� ��ư Ȱ��ȭ ����
			if (thisObj->m_ListTcp.GetItemCount() > 0) {
				thisObj->GetDlgItem(IDC_LOG_BUT)->EnableWindow(true);
			}
			else {
				thisObj->GetDlgItem(IDC_LOG_BUT)->EnableWindow(false);
			}
		}
		Sleep(500);
	}
}

UINT ThreadCamera(LPVOID pParam) {
	ToolManager* thisObj;
	thisObj = (ToolManager*)pParam;
	int Count = 1;

	// ī�޶� ����
	while (thisObj->cameraR) {
		if (Count < 0) {
			AfxMessageBox(_T("NO CAMERA"));
			return 0;
		}

		if (thisObj->SetCap(Count) == true)
		{
			thisObj->SetInference();
			thisObj->m_strPickinLst = L"";
			thisObj->m_Res = RESULT::RES_END;

			thisObj->cap >> thisObj->frame;

			thisObj->cameraR = false;
			break;
		}
		else {
			Count--;
		}
	}
	
	vector<Detection> output = thisObj->inf->runInference(thisObj->frame);
	thisObj->m_Resform->SetCameraButton(true);
	
	return 0;
}

// ����Ʈ ������Ʈ ������
UINT ThreadUpdate(LPVOID pParam) {
	DetectTab* thisObj;
	thisObj = (DetectTab*)pParam;
	CString youngID;

	while (1) {
		if (thisObj->Threadupdate) 
			return 0;
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

