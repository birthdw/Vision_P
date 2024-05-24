#include "pch.h"
#include "ToolManager.h"

#include "DetectTab.h"
#include "TestTab.h"
#include "ResultForm.h"
#include "ServerForm.h"
#include "CntrlForm.h"
#include "ConnectTread.h"
#include "struct.h"

ToolManager* ToolManager::m_pInstance = nullptr;



ToolManager::ToolManager()
{
	ForceQuit = false;
	FrmKilled = true;
	btest = false;
	fpscnt = 0;
	dfps = 0;
	updatetime = 0;
	m_OldState = PROCESSSTATE::STANDBY;
}

ToolManager::~ToolManager()
{

}

ToolManager* ToolManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ToolManager();
	}
	return m_pInstance;
}

void ToolManager::DestroyInstance()
{
	cap.release();

	delete inf;
	inf = nullptr;
	delete m_pInstance;
	m_pInstance = nullptr;

}

void ToolManager::Initialize()
{
	if (cap.open(0, cv::CAP_DSHOW) == true)
	{
		inf = new Inference("C:\\C\\github\\Vision_P\\MainTool\\block.onnx", cv::Size(640, 480), "C:\\C\\github\\Vision_P\\MainTool\\block.txt", true);
		m_strPickinLst = L"";
		m_Res = RESULT::RES_END;

		AfxBeginThread(ThreadCamera, this);
	}

}

bool ToolManager::Update(double t)
{

	if (ForceQuit == true)
		return false;

	++fpscnt;
	dtime += t;
	updatetime += t;
	maxR = 0;
	maxG = 0;
	maxB = 0;



	if (FrmKilled == false)
	{
		cap >> frame;
		resize(frame, frame, Size(600, 450));

		if (m_OldState != m_CurState)
			m_OldState = m_CurState;

		switch (m_OldState)
		{
		case PROCESSSTATE::STANDBY:
			break;
		case PROCESSSTATE::INSPECT:
			m_Res = Detect();

			if (m_Res == RES_END)
			{
				m_Serverform->ClientTCP(_T("ST/PROC:ERROR/END"));
			}
			else if (m_Res == RES_NONE)
			{
				m_Serverform->ClientTCP(_T("ST/PROC:RETRY/END"));
			}
			else
			{
				imwrite("BOX.jpg", frame);
				SendResult(m_Res);
				m_Serverform->SetAwsInfo(AWSINFO::AWSSEND);
			}
			m_Resform->RedrawWindow();
			m_CurState = PROCESSSTATE::STANDBY;
			break;
		case PROCESSSTATE::ABNORMAL:
			break;
		default:
			break;
		}
	}
	else
	{
		if (SpecialOn == false)
			frame = imread("ns.png");
		else
			frame = imread(specFileName);

		resize(frame, frame, Size(600, 450));
	}


	

	if (1.0 <= dtime)
	{
		dfps = fpscnt;
		fpscnt = 0;
		dtime = 0;
	}

	return true;
}

void ToolManager::LateUpdate()
{



}

void ToolManager::Render()
{
	putText(frame, "R:" + to_string(maxR), Point(0, 70), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
	putText(frame, "G:" + to_string(maxG), Point(0, 110), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
	putText(frame, "B:" + to_string(maxB), Point(0, 150), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
	putText(frame, "fps: " + to_string(dfps), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
	cv::imshow("TEST", frame);
	int key = cv::waitKey(1);
	if (key == 27)
		::PostQuitMessage(WM_QUIT);
}

RESULT ToolManager::Detect()
{
	vector<Detection> output = inf->runInference(frame);
	int detections = output.size();
	std::cout << "Number of detections:" << detections << std::endl;

	if (detections <= 0)
		return RESULT::RES_NONE;

	for (int i = 0; i < detections; ++i)
	{
		Detection detection = output[i];
		if (detection.confidence < 0.8)
			continue;
		cv::Rect box = detection.box;
		std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
		cv::Scalar color = detection.color;
		cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
		cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

		if (box.x > 0 && box.y > 0 && box.x + box.width < frame.cols && box.y + box.height < frame.rows)
		{

			roi = Mat(frame, box);
			findMostFrequentColor(roi, maxR, maxG, maxB);
			if (detection.className == "fail")
			{
				cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
				return RESULT::FAIL;
			}
			else
			{
				if ((maxR >= 150 && maxR <= 255) && (maxG >= 150 && maxG <= 255) && (maxB >= 0 && maxB <= 100))
				{
					putText(frame, "YELLOW" + std::to_string(detection.confidence).substr(0, 4), cv::Point(box.x + 5, box.y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 2);
					return RESULT::YELLOW;
				}
				else if ((maxR >= 130 && maxR <= 255) && (maxG >= 0 && maxG <= 90) && (maxB >= 0 && maxB <= 90))
				{
					putText(frame, "RED" + std::to_string(detection.confidence).substr(0, 4), cv::Point(box.x + 5, box.y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 2);
					return RESULT::RED;
				}
				else if ((maxR >= 0 && maxR <= 120) && (maxG >= 100 && maxG <= 255) && (maxB >= 0 && maxB <= 140))
				{
					putText(frame, "GREEN" + std::to_string(detection.confidence).substr(0, 4), cv::Point(box.x + 5, box.y - 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 2);
					return RESULT::GREEN;
				}

			}
		}
	}
	return RESULT::RES_END;
}

void ToolManager::Save()
{
	if (FrmKilled == false)
	{
		imwrite(to_string(testcnt) + ".png", frame);
		++testcnt;
	}
}

void ToolManager::ShowPic(string Filename)
{
	specFileName = Filename;

	if (FrmKilled == true)
	{
		SpecialOn = true;
	}
}

void ToolManager::RenderImg(CStatic* p, CString filepath)
{
	CImage image;
	image.Load(filepath);//레드
	CRect rect;
	p->GetWindowRect(rect);
	CDC* dc;
	dc = p->GetDC();
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	ReleaseDC(p->GetSafeHwnd(), dc->m_hDC);
}

void ToolManager::Setserverform(ServerForm* s)
{
	m_Serverform = s;
}

void ToolManager::SetCntrlForm(CntrlForm* c)
{
	m_CntrlForm = c;
}


void ToolManager::SetMainHndl(HWND mhd)
{
	MainHndle = mhd;
}

void ToolManager::SetToolviewhdl(HWND tvhd)
{
	//툴뷰에 cv로생성한 윈도우창 자식으로 넣기 

	Toolviewhandle = tvhd;
	cv::namedWindow("TEST", 0);
	HWND hWnd = FindWindowA(NULL, "TEST");
	::SetParent(hWnd, Toolviewhandle);
	::SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);
	::SetWindowPos(hWnd, NULL, 0, 0, 640, 480, SWP_NOZORDER | SWP_FRAMECHANGED);

}

void ToolManager::SetListFormHndle(HWND lhd)
{
	ListFormHndle = lhd;
}

void ToolManager::SetTab(DetectTab* d, TestTab* t)
{
	m_detecttab = d;
	m_Testtab = t;
}

void ToolManager::SetForceQuit(bool set)
{
	ForceQuit = set;
}

void ToolManager::SetKillFrm(bool set)
{
	FrmKilled = set;
}

void ToolManager::Settest(bool set)
{
	btest = set;
}

void ToolManager::SetRec(bool set)
{
	RecCtrl = set;
}

void ToolManager::SetSpecialOn(bool set)
{
	SpecialOn = set;
}

CTabCtrl* ToolManager::GetTabctrl()
{
	return m_tab;
}


bool ToolManager::GetFramekill()
{
	return FrmKilled;
}

void ToolManager::Mod_Txt(int cur, int idx, CString cstr)
{
	m_detecttab->Set_Text(cur, idx, cstr);
}

void ToolManager::Set_Mod_Txt(int idx, CString cstr)
{
	switch (idx)
	{
	case 1:
		m_strPickinLst = cstr;
		break;
	case 2:
		m_strPickinLst2 = cstr;
		break;
	default:
		break;
	}
}


void ToolManager::findMostFrequentColor(const Mat& roi, int& maxR, int& maxG, int& maxB)
{

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true, accumulate = false;

	Mat b_hist, g_hist, r_hist;

	vector<Mat> bgr_planes;
	split(roi, bgr_planes);

	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	maxR = maxG = maxB = 0;
	int maxCountR = 0, maxCountG = 0, maxCountB = 0;
	for (int i = 0; i < histSize; ++i) {
		if (b_hist.at<float>(i) > maxCountB) {
			maxCountB = b_hist.at<float>(i);
			maxB = i;
		}
		if (g_hist.at<float>(i) > maxCountG) {
			maxCountG = g_hist.at<float>(i);
			maxG = i;
		}
		if (r_hist.at<float>(i) > maxCountR) {
			maxCountR = r_hist.at<float>(i);
			maxR = i;
		}
	}
}

void ToolManager::SendResult(RESULT res)
{
	
	if (res == RESULT::YELLOW) {
		if (m_Serverform->GetControlColor() == STATUCOLOR::SERVERGREEN)
		{
			m_Serverform->SetAwsColor("yellow");
			m_Serverform->SetAwsFaulty("false");
		}
		else
		{
			AWSLIST res;
			res.color = "yellow";
			res.faulty = "false";
			m_TempVec.emplace_back(res);
		}
		m_Serverform->ClientTCP(_T("ST/PROC:YELLOW/END"));
	}
	else if (res == RESULT::RED) {
		if (m_Serverform->GetControlColor() == STATUCOLOR::SERVERGREEN)
		{
			m_Serverform->SetAwsColor("red");
			m_Serverform->SetAwsFaulty("false");
		}
		else
		{
			AWSLIST res;
			res.color = "red";
			res.faulty = "false";
			m_TempVec.emplace_back(res);
		}
		
		m_Serverform->ClientTCP(_T("ST/PROC:RED/END"));
	}
	else if (res == RESULT::GREEN) {
		if (m_Serverform->GetControlColor() == STATUCOLOR::SERVERGREEN)
		{
			m_Serverform->SetAwsColor("green");
			m_Serverform->SetAwsFaulty("false");
		}
		else
		{
			AWSLIST res;
			res.color = "green";
			res.faulty = "false";
			m_TempVec.emplace_back(res);
		}
		m_Serverform->ClientTCP(_T("ST/PROC:GREEN/END"));
	}
	else if (res == RESULT::FAIL) {
		if (m_Serverform->GetControlColor() == STATUCOLOR::SERVERGREEN)
		{
			m_Serverform->SetAwsColor("fail");
			m_Serverform->SetAwsFaulty("true");
		}
		else
		{
			AWSLIST res;
			res.color = "fail";
			res.faulty = "true";
			m_TempVec.emplace_back(res);
		}
		m_Serverform->ClientTCP(_T("ST/PROC:FAIL/END"));
	}
	



}

void ToolManager::SetProcessState(PROCESSSTATE s)
{
	m_CurState = s;
}

vector<AWSLIST> ToolManager::GetVec()
{
	return m_TempVec;
}
