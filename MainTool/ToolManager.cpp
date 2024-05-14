#include "pch.h"
#include "ToolManager.h"


ToolManager* ToolManager::m_pInstance = nullptr;



ToolManager::ToolManager()
{
	ForceQuit = false;
	FrmKilled = true;
	btest = false;
	fpscnt = 0;
	dfps = 0;
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
	cap.open(0, cv::CAP_DSHOW);
	//inf = new Inference("C:\\Users\\user\\Desktop\\Project1\\yolov8s.onnx", cv::Size(640, 480), "C:\\Users\\user\\Desktop\\Project1\\classes.txt", true);

}

bool ToolManager::Update()
{
	if (ForceQuit == true)
		return false;

	return true;
}

void ToolManager::LateUpdate()
{
}

void ToolManager::Render(double t)
{
	//임시 렌더 코드 

	++fpscnt;
	dtime += t;
	

	if (FrmKilled == false)
	{
		cap >> frame;
		resize(frame, frame, Size(600, 450));
	}
	else
		frame = imread("ns.png");

	if (1.0 <= dtime)
	{
		dfps = fpscnt;
		fpscnt = 0;
		dtime = 0;
	}

	putText(frame, "fps: " + to_string(dfps), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 1);
	cv::imshow("TEST", frame);
	int key = cv::waitKey(1);
	if (key == 27)
		::PostQuitMessage(WM_QUIT);




}

void ToolManager::Detect()
{
	/*vector<Detection> output = inf->runInference(frame);
int detections = output.size();
std::cout << "Number of detections:" << detections << std::endl;

for (int i = 0; i < detections; ++i)
{
	Detection detection = output[i];
	if (detection.className != "person")
		continue;
	if (detection.confidence <= 0.8)
		continue;
	cv::Rect box = detection.box;
	std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
	if (RecCtrl == true)
	{
		cv::Scalar color = detection.color;
		cv::rectangle(frame, box, color, 2);
		cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
		cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);
		cv::rectangle(frame, textBox, color, cv::FILLED);
		cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
	}
}*/
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


bool ToolManager::GetFramekill()
{
	return FrmKilled;
}
