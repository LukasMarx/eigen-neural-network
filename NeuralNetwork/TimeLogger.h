#pragma once
#include <string>
#include <chrono>
#include <iostream>

class TimeLogger
{
public:
	TimeLogger(const char *name);
	void start();
	void stopWatchAndLog();

private:
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> tlStart;
};
