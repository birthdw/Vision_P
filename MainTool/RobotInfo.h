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
	AWSLIST
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