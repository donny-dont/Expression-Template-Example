#include "timer.hpp"

#ifdef _WIN32
#include <Windows.h>
#elif __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <sys/timeb.h>
#endif

namespace
{
	double __secondsPerCycle = 0.0;
#ifdef __MACH__
	clock_serv_t __cs;
#endif
}

void system_time::initialize()
{
#ifdef _WIN32
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	__secondsPerCycle = 1.0 / frequency.QuadPart;
#else
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &__cs);
	__secondsPerCycle = 1e-9;
#endif
}

void system_time::terminate()
{
#ifdef __MACH__
	mach_port_deallocate(mach_task_self(), __cs);
#endif
}

uint64_t system_time::get_time()
{
#ifdef _WIN32
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (uint64_t)time.QuadPart;
#elif __MACH__
	mach_timespec_t ts;
	clock_get_time(__cs, &ts);
	return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
#else
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
#endif
}

double timer::elapsed_time() const
{
	return __secondsPerCycle * (_stop_time - _start_time);
}
