#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include <Windows.h>

class timer
{
	public:

		void start();

		void stop();

		double elapsed_time() const;

		static void initialize();

	private:

		LARGE_INTEGER _startTime;
		LARGE_INTEGER _stopTime;

} ; // end class timer

#endif // end TIMER_HPP_INCLUDED
