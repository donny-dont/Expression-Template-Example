#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include <cstdint>

namespace time
{
	void initialize();

	std::uint64_t get_time();
}

class timer
{
	public:

		inline timer()
		: _start_time(0)
		, _stop_time(0)
		{ }

		inline void start()
		{
			_start_time = time::get_time();
		}

		inline void stop()
		{
			_stop_time = time::get_time();
		}

		double elapsed_time() const;

	private:

		std::uint64_t _start_time;
		std::uint64_t _stop_time;

} ; // end class timer

#endif // end TIMER_HPP_INCLUDED
