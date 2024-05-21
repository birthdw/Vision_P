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
	string data;
	string url;

}AWSSTRUCT;