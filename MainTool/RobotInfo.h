#pragma once


// �κ� ���� ����ü
typedef struct RobotInfo {
	int x_limit, y_limit, pos, home;
}RINFO;


// ���� ����ġ 
enum class AWSINFO :int {
	STAY = 0,
	SEVERSTART,
	AWSSEND,
	AWSCHEAK,
	AWSEXIT,
	AWSLIST,
	AWSTEMPLIST,
	AWSMODIFY,
	AWSDELETE
};


// ���� ����Ʈ ���� ����ü
typedef struct {
	string id;
	string color;
	string faulty;
	string date;
	string url;

}AWSLIST;


// ��� ���� ����ġ
enum class STATUCOLOR : int
{
	STAY = 0,
	SERVERRED,
	SERVERYELLOW,
	SERVERGREEN,
	SOCKETRED,
	SOCKETYELLOW,
	SOCKETGREEN,
};


// ������ �ڿ� ����
enum class COLORTHREAD : int
{
	THREADRUN = 0,
	THREADEXIT
};


// ��� ������
enum class PROCESSSTATE : int
{
	STANDBY = 0,
	WAIT_CAM_GRAB,
	INSPECT,
	ABNORMAL,
	PROCESS_END
};


// ������ ����� ����Ʈ ����
typedef struct TempInfo{

	string filename;
	string color;
	string faulty;
	string date;

}TEMPINFO;