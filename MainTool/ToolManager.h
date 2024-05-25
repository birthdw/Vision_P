#pragma once

class Infernece;
class ServerForm;
class DetectTab;
class TestTab;
class ResultForm;
class CntrlForm;

enum class PROCESSSTATE;

enum RESULT
{
	FAIL,RED,YELLOW,GREEN,RES_NONE,RES_END
};


class ToolManager
{
private:
	ToolManager(ToolManager&);

public:
	ToolManager();
	~ToolManager();


private:
	static ToolManager* m_pInstance;

public:
	static ToolManager* GetInstance();
	void DestroyInstance();

public:
	void Initialize();
	bool Update(double t);
	void LateUpdate();
	void Render();

public:
	RESULT Detect();


	void Save();
	void ShowPic(string Filename);

	void RenderImg(CStatic* p, CString filepath);

public:
	void Setserverform(ServerForm* s);
	void SetCntrlForm(CntrlForm* c);
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
	void SetSpecialOn(bool set);
public:
	CTabCtrl* GetTabctrl();
public:
	bool  GetFramekill();

public:
	void Mod_Txt(int cur, int idx, CString cstr);
	void Set_Mod_Txt(int idx, CString cstr);

	void findMostFrequentColor(const Mat& roi, int& maxR, int& maxG, int& maxB);
	void SendResult(RESULT res);
	
	void SetProcessState(PROCESSSTATE s);


	void TempVecSendAll();




	vector<TEMPINFO>  GetVec();



public:
	HWND MainHndle;
	HWND Toolviewhandle;
	HWND ListFormHndle;
	Mat frame;
	Mat roi;
	VideoCapture cap;
	Inference *inf;

public:
	bool btest = false;
	bool ForceQuit = false;
	bool FrmKilled = false;
	bool RecCtrl = false;
	bool SpecialOn = false;
	bool bGrap = false;
public:
	double dfps;
	double fpscnt;
	double dtime;
	double updatetime;
public:
	CString m_strPickinLst;
	CString m_strPickinLst2;
public:
	ServerForm* m_Serverform;
	CTabCtrl* m_tab;
	DetectTab* m_detecttab;
	TestTab* m_Testtab;
	ResultForm* m_Resform;
	CntrlForm* m_CntrlForm;

public:
	int maxR, maxG, maxB;


	RESULT m_Res;

public:
	string specFileName;

public:
	int testcnt=0;

	int tempboxcnt = 0;
	



//새로 만들것들 
	public:
		PROCESSSTATE m_OldState;
		PROCESSSTATE m_CurState;

		vector<TEMPINFO> m_TempVec;


		bool m_bReadyState = false;

		void SetReady(bool bReady);


};
