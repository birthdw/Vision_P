#pragma once

typedef struct RobotInfo {
	int x_limit, y_limit, pos, home;
}RINFO;

enum class AWSINFO :int {
	STAY = 0,
	SEVERSTART,
	AWSSEND,
	AWSCHEAK,
	AWSEXIT,
	AWSLIST,
	AWSTEMPLIST,
	AWSMODIFY
};

typedef struct {
	string id;
	string color;
	string faulty;
	string date;
	string url;

}AWSLIST;

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

enum class COLORTHREAD : int
{
	THREADRUN = 0,
	THREADEXIT
};

enum class PROCESSSTATE : int
{
	STANDBY = 0,
	WAIT_CAM_GRAB,
	INSPECT,
	ABNORMAL,
	PROCESS_END
};


typedef struct TempInfo{

	string filename;
	string color;
	string faulty;
	string date;

}TEMPINFO;