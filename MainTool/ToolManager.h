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
	FAIL, RED, YELLOW, GREEN, RES_NONE, RES_END
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
	RESULT Detect();   //�����ڵ�
	void Save();  //���� ������ �̹��� ����
	void ShowPic(string Filename);    //���Ͽ����� �̹��� �����ٷ��¿�
	void RenderImg(CStatic* p, CString filepath);  //�����н����ִ� �̹��� ������

	RESULT Detecttest();   //�����ڵ�

public:
	void Setserverform(ServerForm* s);
	void SetCntrlForm(CntrlForm* c);
	void SetMainHndl(HWND mhd);
	void SetToolviewhdl(HWND tvhd);
	void SetListFormHndle(HWND tvhd);
	void SetTab(DetectTab* d, TestTab* t);
	void SetForceQuit(bool set);
	void SetKillFrm(bool set);
	void SetSpecialOn(bool set);
	void SetProcessState(PROCESSSTATE s);  //���º���

public:
	CTabCtrl* GetTabctrl();
	bool  GetFramekill();

public:
	void Mod_Txt(int cur, int idx, CString cstr);
	void findMostFrequentColor(const Mat& roi, int& maxR, int& maxG, int& maxB); //������
	void SendResult(RESULT res);     //����������

public:
	void TempVecSendAll();     //�ӽú��� ���� ���� 
	vector<TEMPINFO>  GetVec(); //�ӽú��� ��


public:
	HWND MainHndle;
	HWND Toolviewhandle;
	HWND ListFormHndle;
	Mat frame;  //����������
	Mat roi;    //�˻��� ����Ǵ� roi
	VideoCapture cap;
	Inference* inf; //for onnx

public:
	bool ForceQuit = false; //update���� �޽� ����� ���� �ӽú���
	bool FrmKilled = false; // ķ on off ����
	bool SpecialOn = false; // ���� ��� ���� ���� ������ ����
	bool bGrap = false;     // �׷� ��ȣ ���� 
public:
	double dfps;            //fps
	double fpscnt;			//fpsī��Ʈ ��
	double dtime;           //��ŸŸ��
	double updatetime;      //�ӽ� ��ŸŸ�� �����
	bool onlycam = false;   //�˻� ���ϴ� ķŰ�� ����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	bool cameraR = true;   //                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
public:
	CString m_strPickinLst;  //�����̸� ����Ʈ�ǿ� ����
public:
	ServerForm* m_Serverform;
	CTabCtrl* m_tab;
	DetectTab* m_detecttab;
	TestTab* m_Testtab;
	ResultForm* m_Resform;
	CntrlForm* m_CntrlForm;

public:
	int maxR, maxG, maxB;      //�˻�� rgb��
	RESULT m_Res;				//�˻� ���


public:
	string specFileName;         //���� ��� ���� ���� ���̴� �����̸� ����

public:
	int testcnt = 0;               //���� �����Ҷ� �ڿ� ��ȣ ���̴� ������ ���̴� ����
	int tempboxcnt = 0;          //���� �������� �ڽ���� �̹��� �����Ҷ� �ڿ� ��ȣ ���̴� ������ ���� ���� 

	//���� ����͵� 
public:
	PROCESSSTATE m_OldState;       //���� ����
	PROCESSSTATE m_CurState;       //���� ����
public:
	vector<TEMPINFO> m_TempVec;    //���� �������� �ڽ����� ��� �ӽ� �־���� ����
public:
	bool m_bReadyState = false;    //ó�� ���Ĺ��̻��¿��� ���̴� �Һ���
	void SetReady(bool bReady);
	bool SetCap(int set);
	void SetInference();




public:

	//0 red / 1 yellow / 2 green
	//0~1 r 2~3 g 4~5 b
	int forcolor[3][6];


	




};
