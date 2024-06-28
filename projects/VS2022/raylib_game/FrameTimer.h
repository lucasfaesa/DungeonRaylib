#pragma once
#include <chrono>

class FrameTimer {
public:
	FrameTimer();
	const float GetFrameDuration();
private:
	std::chrono::steady_clock::time_point currentFrameTime;

};