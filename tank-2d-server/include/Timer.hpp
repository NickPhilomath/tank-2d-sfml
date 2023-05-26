#pragma once 

#include <chrono>

class Timer {
public:
	Timer();
	~Timer();

	float getElapsedTime();
	void resetTime();

private:
	std::chrono::steady_clock::time_point time;
};