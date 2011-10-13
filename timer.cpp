#include "timer.hpp"
#include <Windows.h>

namespace
{
	double __secondsPerCycle = 0.0;
}

void timer::start()
{
	QueryPerformanceCounter(&_startTime);
}

void timer::stop()
{
	QueryPerformanceCounter(&_stopTime);
}

double timer::elapsed_time() const
{
	return __secondsPerCycle * (_stopTime.QuadPart - _startTime.QuadPart);
}

void timer::initialize()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	__secondsPerCycle = 1.0 / frequency.QuadPart;
}
