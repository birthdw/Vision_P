#include "pch.h"
#include "ConnectTread.h"
#include "ServerForm.h"
#include "ToolManager.h"
#include "ResultForm.h"
#include "DataInquiryDlg.h"

#define WM_SOCKET_THREAD_FINISHED (WM_USER + 1)


// AWS ���� ������
UINT initawsT(LPVOID pParam)
{
	ServerForm* thisObj;
	thisObj = (ServerForm*)pParam;
	queue<AWSINFO>& infoALL = thisObj->GetAwsInfo();

	while (1) 
	{
		
		AWSINFO info = AWSINFO::STAY;
		if (!infoALL.empty()) {
			info = infoALL.front();
			infoALL.pop();
		}

		switch (info)
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
				else
				{
					thisObj->GetServerList();
					thisObj->InvalidateRect(NULL, FALSE);
				}
				break;
			}


			// AWS ���� ����
			case AWSINFO::AWSSEND:
			{
				string info = "('" + thisObj->GetAwsColor() + "', '" + thisObj->GetAwsFaulty() + "')";
				thisObj->SetAwsColor("");
				thisObj->SetAwsFaulty("");

				thisObj->GetAWS()->Allinput(thisObj->GetDate(), info.c_str(), thisObj->GetAwsFilename());
				thisObj->GetServerList();
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
				thisObj->GetServerList();
				break;
			}


			// ���� ���� üũ
			case AWSINFO::AWSCHEAK:
			{
				thisObj->GetAWS()->RDSckeckConnection();
				thisObj->GetServerList();
				break;
			}


			// ����� ���� ����
			case AWSINFO::AWSMODIFY:
			{
				thisObj->GetAWS()->RDSupdateData("color", thisObj->GetModifyColor().c_str(), thisObj->GetModifyCurId().c_str());
				thisObj->GetAWS()->RDSupdateData("faulty", thisObj->GetModifyFaulty().c_str(), thisObj->GetModifyCurId().c_str());
				ToolManager::GetInstance()->m_DataInquiryDlg->GetButtonState(true);
				thisObj->SetData();
				ToolManager::GetInstance()->m_DataInquiryDlg->ResetAndUpdate();

				break;
			}

			case AWSINFO::AWSDELETE:
			{
				string id = CT2CA(ToolManager::GetInstance()->m_DataInquiryDlg->CurId);
				ToolManager::GetInstance()->m_Serverform->GetAWS()->AlldeleteData(id.c_str());
				ToolManager::GetInstance()->m_DataInquiryDlg->GetButtonState(true);
				thisObj->SetData();
				ToolManager::GetInstance()->m_DataInquiryDlg->ResetAndUpdate();
			}

			// ���� ����Ʈ �ҷ�����
			default:
			{
				int a = 0;
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

