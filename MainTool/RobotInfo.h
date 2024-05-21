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