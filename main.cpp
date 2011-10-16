#include "config.hpp"
#include <iostream>

//---------------------------------------------------------------------
// valarray implementations
//---------------------------------------------------------------------

double time_naive_array(std::size_t size)
{
	using namespace naive_implementation;

	// Setup the arrays
	valarray<float> v1x(size, 1.0f);
	valarray<float> v1y(size, 2.0f);
	valarray<float> v1z(size, 3.0f);
	valarray<float> v1w(size, 4.0f);

	valarray<float> v2x(size, 5.0f);
	valarray<float> v2y(size, 6.0f);
	valarray<float> v2z(size, 7.0f);
	valarray<float> v2w(size, 8.0f);

	valarray<float> dot_products(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	dot_products =
		v1x * v2x +
		v1y * v2y +
		v1z * v2z +
		v1w * v2w;

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

double time_expr_template_float(std::size_t size)
{
	using namespace expression_template;

	// Setup the arrays
	valarray<float> v1x(size, 1.0f);
	valarray<float> v1y(size, 2.0f);
	valarray<float> v1z(size, 3.0f);
	valarray<float> v1w(size, 4.0f);

	valarray<float> v2x(size, 5.0f);
	valarray<float> v2y(size, 6.0f);
	valarray<float> v2z(size, 7.0f);
	valarray<float> v2w(size, 8.0f);

	valarray<float> dot_products(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	dot_products =
		v1x * v2x +
		v1y * v2y +
		v1z * v2z +
		v1w * v2w;

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

#ifdef USE_SSE

double time_expr_template_sse(std::size_t size)
{
	using namespace expression_template_simd;
	typedef valarray<float> valarray_float;

	// Setup the arrays
	valarray_float v1x(size, 1.0f);
	valarray_float v1y(size, 2.0f);
	valarray_float v1z(size, 3.0f);
	valarray_float v1w(size, 4.0f);

	valarray_float v2x(size, 5.0f);
	valarray_float v2y(size, 6.0f);
	valarray_float v2z(size, 7.0f);
	valarray_float v2w(size, 8.0f);

	valarray_float dot_products(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	dot_products =
		v1x * v2x +
		v1y * v2y +
		v1z * v2z +
		v1w * v2w;

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

#else

double time_expr_template_sse(std::size_t size) { return 0.0; }

#endif

#ifdef USE_AVX

double time_expr_template_avx(std::size_t size)
{
	using namespace expression_template_simd;
	typedef valarray<float, valarray_rep_avx<float> > valarray_float;

	// Setup the arrays
	valarray_float v1x(size, 1.0f);
	valarray_float v1y(size, 2.0f);
	valarray_float v1z(size, 3.0f);
	valarray_float v1w(size, 4.0f);

	valarray_float v2x(size, 5.0f);
	valarray_float v2y(size, 6.0f);
	valarray_float v2z(size, 7.0f);
	valarray_float v2w(size, 8.0f);

	valarray_float dot_products(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	dot_products =
		v1x * v2x +
		v1y * v2y +
		v1z * v2z +
		v1w * v2w;

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

#else

double time_expr_template_avx(std::size_t size) { return 0.0; }

#endif

//---------------------------------------------------------------------
// C array implementations
//---------------------------------------------------------------------

double time_float_arrays(std::size_t size)
{
	// Setup the arrays
	float* v1x = new float[size];
	float* v1y = new float[size];
	float* v1z = new float[size];
	float* v1w = new float[size];

	float* v2x = new float[size];
	float* v2y = new float[size];
	float* v2z = new float[size];
	float* v2w = new float[size];

	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = 1.0f;
		v1y[i] = 2.0f;
		v1z[i] = 3.0f;
		v1w[i] = 4.0f;

		v2x[i] = 5.0f;
		v2y[i] = 6.0f;
		v2z[i] = 7.0f;
		v2w[i] = 8.0f;
	}

	float* dot_products = new float[size];

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	for (std::size_t i = 0; i < size; ++i)
	{
		dot_products[i] = 
			v1x[i] * v2x[i] +
			v1y[i] * v2y[i] +
			v1z[i] * v2z[i] +
			v1w[i] * v2w[i];
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	delete[] dot_products;

	delete[] v1x;
	delete[] v1y;
	delete[] v1z;
	delete[] v1w;

	delete[] v2x;
	delete[] v2y;
	delete[] v2z;
	delete[] v2w;

	return clock.elapsed_time();
}

#ifdef USE_SSE

double time_sse_arrays(std::size_t elements)
{
	const std::size_t size = (elements / 4) + ((elements % 4 == 0) ? 0 : 1);
	const std::size_t alignment  = sizeof(__m128);
	const std::size_t array_size = alignment * size;

	// Setup the arrays
	__m128* v1x = (__m128*)_aligned_malloc(array_size, alignment);
	__m128* v1y = (__m128*)_aligned_malloc(array_size, alignment);
	__m128* v1z = (__m128*)_aligned_malloc(array_size, alignment);
	__m128* v1w = (__m128*)_aligned_malloc(array_size, alignment);

	__m128* v2x = (__m128*)_aligned_malloc(array_size, alignment);
	__m128* v2y = (__m128*)_aligned_malloc(array_size, alignment);
	__m128* v2z = (__m128*)_aligned_malloc(array_size, alignment);
	__m128* v2w = (__m128*)_aligned_malloc(array_size, alignment);
	
	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = _mm_set1_ps(1.0f);
		v1y[i] = _mm_set1_ps(2.0f);
		v1z[i] = _mm_set1_ps(3.0f);
		v1w[i] = _mm_set1_ps(4.0f);

		v2x[i] = _mm_set1_ps(5.0f);
		v2y[i] = _mm_set1_ps(6.0f);
		v2z[i] = _mm_set1_ps(7.0f);
		v2w[i] = _mm_set1_ps(8.0f);
	}
	
	__m128* dot_products = (__m128*)_aligned_malloc(array_size, alignment);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	for (std::size_t i = 0; i < size; ++i)
	{
		dot_products[i] = 
			_mm_add_ps(
				_mm_add_ps(_mm_mul_ps(v1x[i], v2x[i]), _mm_mul_ps(v1y[i], v2y[i])),
				_mm_add_ps(_mm_mul_ps(v1z[i], v2z[i]), _mm_mul_ps(v1w[i], v2w[i])));
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	_aligned_free(dot_products);

	_aligned_free(v1x);
	_aligned_free(v1y);
	_aligned_free(v1z);
	_aligned_free(v1w);

	_aligned_free(v2x);
	_aligned_free(v2y);
	_aligned_free(v2z);
	_aligned_free(v2w);

	return clock.elapsed_time();
}

#else

double time_sse_arrays(std::size_t elements) { return 0.0; }

#endif

#ifdef USE_AVX

double time_avx_arrays(std::size_t elements)
{
	const std::size_t size = (elements / 8) + ((elements % 8 == 0) ? 0 : 1);
	const std::size_t alignment  = sizeof(__m256);
	const std::size_t array_size = alignment * size;

	// Setup the arrays
	__m256* v1x = (__m256*)_aligned_malloc(array_size, alignment);
	__m256* v1y = (__m256*)_aligned_malloc(array_size, alignment);
	__m256* v1z = (__m256*)_aligned_malloc(array_size, alignment);
	__m256* v1w = (__m256*)_aligned_malloc(array_size, alignment);

	__m256* v2x = (__m256*)_aligned_malloc(array_size, alignment);
	__m256* v2y = (__m256*)_aligned_malloc(array_size, alignment);
	__m256* v2z = (__m256*)_aligned_malloc(array_size, alignment);
	__m256* v2w = (__m256*)_aligned_malloc(array_size, alignment);
	
	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = _mm256_set1_ps(1.0f);
		v1y[i] = _mm256_set1_ps(2.0f);
		v1z[i] = _mm256_set1_ps(3.0f);
		v1w[i] = _mm256_set1_ps(4.0f);

		v2x[i] = _mm256_set1_ps(5.0f);
		v2y[i] = _mm256_set1_ps(6.0f);
		v2z[i] = _mm256_set1_ps(7.0f);
		v2w[i] = _mm256_set1_ps(8.0f);
	}
	
	__m256* dot_products = (__m256*)_aligned_malloc(array_size, alignment);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	for (std::size_t i = 0; i < size; ++i)
	{
		dot_products[i] = 
			_mm256_add_ps(
				_mm256_add_ps(_mm256_mul_ps(v1x[i], v2x[i]), _mm256_mul_ps(v1y[i], v2y[i])),
				_mm256_add_ps(_mm256_mul_ps(v1z[i], v2z[i]), _mm256_mul_ps(v1w[i], v2w[i])));
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	_aligned_free(dot_products);

	_aligned_free(v1x);
	_aligned_free(v1y);
	_aligned_free(v1z);
	_aligned_free(v1w);

	_aligned_free(v2x);
	_aligned_free(v2y);
	_aligned_free(v2z);
	_aligned_free(v2w);

	return clock.elapsed_time();
}

#else

double time_avx_arrays(std::size_t elements) { return 0.0; }

#endif

//---------------------------------------------------------------------
// Main
//---------------------------------------------------------------------

int main(int argc, char *argv[])
{
	// Initialize the timer
	timer::initialize();

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
