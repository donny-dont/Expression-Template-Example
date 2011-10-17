#include "timer.hpp"

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#include <sys/timeb.h>
#endif

namespace
{
	double __secondsPerCycle = 0.0;
}

void time::initialize()
{
#ifdef _WIN32
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	__secondsPerCycle = 1.0 / frequency.QuadPart;
#else
	__secondsPerCycle = 1e-9;
#endif
}

std::uint64_t time::get_time()
{
#ifdef _WIN32
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (std::uint64_t)time.QuadPart;
#else
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
    return (std::uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
#endif
}

double timer::elapsed_time() const
{
	return __secondsPerCycle * (_stop_time - _start_time);
}
