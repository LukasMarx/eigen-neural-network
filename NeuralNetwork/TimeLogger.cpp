#include "TimeLogger.h"

TimeLogger::TimeLogger(const char *name)
{
	this->name = name;
}

void TimeLogger::start()
{
	this->tlStart = std::chrono::high_resolution_clock::now();
}

void TimeLogger::stopWatchAndLog()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->tlStart);

	std::cout
		<< "Duration '" << this->name << "': " << diff.count() / 1000 << " seconds, " << diff.count() % 1000 << " milliseconds" << std::endl;
}