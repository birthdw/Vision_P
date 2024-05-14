#pragma once

class Infernece;
class ServerForm;
class DetectTab;
class TestTab;

class ToolManager
{
private:
	ToolManager(ToolManager&);

private:
	ToolManager();
	~ToolManager();


private:
	static ToolManager* m_pInstance;

public:
	static ToolManager* GetInstance();
	void DestroyInstance();

public:
	void Initialize();
	bool Update();
	void LateUpdate();
	void Render(double t);

public:
	void Detect();

public:
	void Setserverform(ServerForm* s);
public:
	void SetMainHndl(HWND mhd);
	void SetToolviewhdl(HWND tvhd);
	void SetListFormHndle(HWND tvhd);

	void SetTab(DetectTab* d, TestTab* t);

public:
	void SetForceQuit(bool set);
	void SetKillFrm(bool set);
	void Settest(bool set);
	void SetRec(bool set);
public:
	CTabCtrl* GetTabctrl();
public:
	bool  GetFramekill();


	
public:
	HWND MainHndle;
	HWND Toolviewhandle;
	HWND ListFormHndle;
	Mat frame;
	VideoCapture cap;
	Inference *inf;

public:
	bool btest = false;
	bool ForceQuit = false;
	bool FrmKilled = false;
	bool RecCtrl = false;
public:
	double dfps;
	double fpscnt;
	double dtime;
public:
	CString m_strPickinLst;
	CString m_strPickinLst2;
public:
	ServerForm* m_Serverform;
	CTabCtrl* m_tab;
	DetectTab* m_detecttab;
	TestTab* m_Testtab;
};