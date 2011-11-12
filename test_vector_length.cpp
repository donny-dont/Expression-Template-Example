#include "performance_test.hpp"

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

	valarray<float> lengths(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	lengths =
		sqrt(
			v1x * v1x +
			v1y * v1y +
			v1z * v1z +
			v1w * v1w
		);

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

	valarray<float> lengths(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	lengths =
		sqrt(
			v1x * v1x +
			v1y * v1y +
			v1z * v1z +
			v1w * v1w
		);

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

	valarray_float lengths(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	lengths =
		sqrt(
			v1x * v1x +
			v1y * v1y +
			v1z * v1z +
			v1w * v1w
		);

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

#else

double time_expr_template_sse(std::size_t) { return 0.0; }

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

	valarray_float lengths(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	lengths =
		sqrt(
			v1x * v1x +
			v1y * v1y +
			v1z * v1z +
			v1w * v1w
		);

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

#else

double time_expr_template_avx(std::size_t) { return 0.0; }

#endif

#ifdef USE_NEON

double time_expr_template_neon(std::size_t size)
{
	using namespace expression_template_simd;
	typedef valarray<float, valarray_rep_neon<float> > valarray_float;

	// Setup the arrays
	valarray_float v1x(size, 1.0f);
	valarray_float v1y(size, 2.0f);
	valarray_float v1z(size, 3.0f);
	valarray_float v1w(size, 4.0f);

	valarray_float lengths(size);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	lengths =
		sqrt(
			v1x * v1x +
			v1y * v1y +
			v1z * v1z +
			v1w * v1w
		);

	// Stop the timer
	clock.stop();

	return clock.elapsed_time();
}

#else

double time_expr_template_neon(std::size_t) { return 0.0; }

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

	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = 1.0f;
		v1y[i] = 2.0f;
		v1z[i] = 3.0f;
		v1w[i] = 4.0f;
	}

	float* lengths = new float[size];

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	for (std::size_t i = 0; i < size; ++i)
	{
		lengths[i] =
			std::sqrt(
				v1x[i] * v1x[i] +
				v1y[i] * v1y[i] +
				v1z[i] * v1z[i] +
				v1w[i] * v1w[i]
			);
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	delete[] lengths;

	delete[] v1x;
	delete[] v1y;
	delete[] v1z;
	delete[] v1w;

	return clock.elapsed_time();
}

#ifdef USE_SSE

double time_sse_arrays(std::size_t elements)
{
	const std::size_t size = (elements / 4) + ((elements % 4 == 0) ? 0 : 1);
	const std::size_t alignment  = sizeof(__m128);
	const std::size_t array_size = alignment * size;

	// Setup the arrays
	__m128* v1x = (__m128*)_mm_malloc(array_size, alignment);
	__m128* v1y = (__m128*)_mm_malloc(array_size, alignment);
	__m128* v1z = (__m128*)_mm_malloc(array_size, alignment);
	__m128* v1w = (__m128*)_mm_malloc(array_size, alignment);
	
	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = _mm_set1_ps(1.0f);
		v1y[i] = _mm_set1_ps(2.0f);
		v1z[i] = _mm_set1_ps(3.0f);
		v1w[i] = _mm_set1_ps(4.0f);
	}
	
	__m128* lengths = (__m128*)_mm_malloc(array_size, alignment);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	for (std::size_t i = 0; i < size; ++i)
	{
		lengths[i] = 
			_mm_sqrt_ps(
				_mm_add_ps(
					_mm_add_ps(_mm_mul_ps(v1x[i], v1x[i]), _mm_mul_ps(v1y[i], v1y[i])),
					_mm_add_ps(_mm_mul_ps(v1z[i], v1z[i]), _mm_mul_ps(v1w[i], v1w[i]))));
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	_mm_free(lengths);

	_mm_free(v1x);
	_mm_free(v1y);
	_mm_free(v1z);
	_mm_free(v1w);

	return clock.elapsed_time();
}

#else

double time_sse_arrays(std::size_t) { return 0.0; }

#endif

#ifdef USE_AVX

double time_avx_arrays(std::size_t elements)
{
	const std::size_t size = (elements / 8) + ((elements % 8 == 0) ? 0 : 1);
	const std::size_t alignment  = sizeof(__m256);
	const std::size_t array_size = alignment * size;

	// Setup the arrays
	__m256* v1x = (__m256*)_mm_malloc(array_size, alignment);
	__m256* v1y = (__m256*)_mm_malloc(array_size, alignment);
	__m256* v1z = (__m256*)_mm_malloc(array_size, alignment);
	__m256* v1w = (__m256*)_mm_malloc(array_size, alignment);
	
	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = _mm256_set1_ps(1.0f);
		v1y[i] = _mm256_set1_ps(2.0f);
		v1z[i] = _mm256_set1_ps(3.0f);
		v1w[i] = _mm256_set1_ps(4.0f);
	}
	
	__m256* lengths = (__m256*)_mm_malloc(array_size, alignment);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the length
	for (std::size_t i = 0; i < size; ++i)
	{
		lengths[i] = 
			_mm256_sqrt_ps(
				_mm256_add_ps(
					_mm256_add_ps(_mm256_mul_ps(v1x[i], v1x[i]), _mm256_mul_ps(v1y[i], v1y[i])),
					_mm256_add_ps(_mm256_mul_ps(v1z[i], v1z[i]), _mm256_mul_ps(v1w[i], v1w[i]))));
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	_mm_free(lengths);

	_mm_free(v1x);
	_mm_free(v1y);
	_mm_free(v1z);
	_mm_free(v1w);

	return clock.elapsed_time();
}

#else

double time_avx_arrays(std::size_t) { return 0.0; }

#endif

#ifdef USE_NEON

double time_neon_arrays(std::size_t elements)
{
	const std::size_t size = (elements / 4) + ((elements % 4 == 0) ? 0 : 1);
	const std::size_t alignment  = sizeof(float32x4_t);
	const std::size_t array_size = alignment * size;

	// Setup the arrays
	float32x4_t* v1x = (float32x4_t*)_mm_malloc(array_size, alignment);
	float32x4_t* v1y = (float32x4_t*)_mm_malloc(array_size, alignment);
	float32x4_t* v1z = (float32x4_t*)_mm_malloc(array_size, alignment);
	float32x4_t* v1w = (float32x4_t*)_mm_malloc(array_size, alignment);

	float32x4_t* v2x = (float32x4_t*)_mm_malloc(array_size, alignment);
	float32x4_t* v2y = (float32x4_t*)_mm_malloc(array_size, alignment);
	float32x4_t* v2z = (float32x4_t*)_mm_malloc(array_size, alignment);
	float32x4_t* v2w = (float32x4_t*)_mm_malloc(array_size, alignment);
	
	for (std::size_t i = 0; i < size; ++i)
	{
		v1x[i] = vdupq_n_f32(1.0f);
		v1y[i] = vdupq_n_f32(2.0f);
		v1z[i] = vdupq_n_f32(3.0f);
		v1w[i] = vdupq_n_f32(4.0f);

		v2x[i] = vdupq_n_f32(5.0f);
		v2y[i] = vdupq_n_f32(6.0f);
		v2z[i] = vdupq_n_f32(7.0f);
		v2w[i] = vdupq_n_f32(8.0f);
	}
	
	float32x4_t* lengths = (float32x4_t*)_mm_malloc(array_size, alignment);

	// Begin the timer
	timer clock;
	clock.start();

	// Compute the dot product
	for (std::size_t i = 0; i < size; ++i)
	{
		const float32x4_t length_squared = 
			vmlaq_f32(
				vmlaq_f32(
					vmlaq_f32(
						vmulq_f32(v1x[i], v2x[i]), v1y[i], v2y[i]), v1z[i], v2z[i]), v1w[i], v2w[i]);

		lengths[i] = vmulq_f32(length_squared, vrsqrteq_f32(length_squared));
	}

	// Stop the timer
	clock.stop();

	// Cleanup the arrays
	_mm_free(lengths);

	_mm_free(v1x);
	_mm_free(v1y);
	_mm_free(v1z);
	_mm_free(v1w);

	_mm_free(v2x);
	_mm_free(v2y);
	_mm_free(v2z);
	_mm_free(v2w);

	return clock.elapsed_time();
}

#else

double time_neon_arrays(std::size_t) { return 0.0; }

#endif
