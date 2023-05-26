#include "Timer.hpp"

Timer::Timer() {
	time = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
}

float Timer::getElapsedTime() {
	auto t_end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<float, std::milli>(t_end - time).count();
}

void Timer::resetTime() {
	time = std::chrono::high_resolution_clock::now();
}
