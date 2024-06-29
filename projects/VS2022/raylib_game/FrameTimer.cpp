#include "FrameTimer.h"



FrameTimer::FrameTimer()
{
    currentFrameTime = std::chrono::steady_clock::now();
}

const float FrameTimer::GetFrameDuration()
{
    const auto oldFrameTime = currentFrameTime;

    currentFrameTime = std::chrono::steady_clock::now();

    const std::chrono::duration<float> frameTime = currentFrameTime - oldFrameTime;

    return frameTime.count();
}
