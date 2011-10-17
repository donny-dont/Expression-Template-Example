#include "performance_test.hpp"
#include <iostream>

//---------------------------------------------------------------------
// Main
//---------------------------------------------------------------------

int main(int argc, char *argv[])
{
	// Initialize the timer
	time::initialize();

	// Initialize the total times
	double accum_float_arrays_time        = 0.0;
	double accum_sse_arrays_time          = 0.0;
	double accum_avx_arrays_time          = 0.0;
	double accum_naive_array_time         = 0.0;
	double accum_expr_template_float_time = 0.0;
	double accum_expr_template_sse_time   = 0.0;
	double accum_expr_template_avx_time   = 0.0;

	// Get the size of the arrays and the
	// number of repetitions
	std::size_t size = 1000000;
	std::size_t repeat = 100;

	if (argc >= 3)
	{
		size = atoi(argv[1]);
		repeat = atoi(argv[2]);
	}
	else if (argc == 2)
	{
		size = atoi(argv[0]);
	}

	// Run the tests
	for (std::size_t i = 0; i < repeat; ++i)
	{
		// C array implementations
		accum_float_arrays_time     += time_float_arrays(size);
		accum_sse_arrays_time       += time_sse_arrays(size);
		accum_avx_arrays_time       += time_avx_arrays(size);

		// valarray implementations
		accum_naive_array_time          += time_naive_array(size);
		accum_expr_template_float_time  += time_expr_template_float(size);
		accum_expr_template_sse_time    += time_expr_template_sse(size);
		accum_expr_template_avx_time    += time_expr_template_avx(size);
	}

	// Print out results
	std::cout << "Results for " << size << " elements computed " << repeat << " times\n";
	std::cout.precision(12);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);

	// Print out total times
	std::cout << "\nTotal times\n";
	std::cout << "------------------------\n";
	std::cout << "   Float array time: " << accum_float_arrays_time        << " secs\n";
	std::cout << "     SSE array time: " << accum_sse_arrays_time          << " secs\n";
	std::cout << "     AVX array time: " << accum_avx_arrays_time          << " secs\n";
	std::cout << "Naive valarray time: " << accum_naive_array_time         << " secs\n";
	std::cout << "Float valarray time: " << accum_expr_template_float_time << " secs\n";
	std::cout << "  SSE valarray time: " << accum_expr_template_sse_time   << " secs\n";
	std::cout << "  AVX valarray time: " << accum_expr_template_avx_time   << " secs\n";

	// Print out average times
	std::cout << "\nAverage times\n";
	std::cout << "------------------------\n";
	std::cout << "   Float array time: " << accum_float_arrays_time        / repeat << " secs\n";
	std::cout << "     SSE array time: " << accum_sse_arrays_time          / repeat << " secs\n";
	std::cout << "     AVX array time: " << accum_avx_arrays_time          / repeat << " secs\n";
	std::cout << "Naive valarray time: " << accum_naive_array_time         / repeat << " secs\n";
	std::cout << "Float valarray time: " << accum_expr_template_float_time / repeat << " secs\n";
	std::cout << "  SSE valarray time: " << accum_expr_template_sse_time   / repeat << " secs\n";
	std::cout << "  AVX valarray time: " << accum_expr_template_avx_time   / repeat << " secs\n";
}
