#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

// Uncomment/comment to enable/disable SSE computations
#define USE_SSE
// Uncomment/comment to enable/disable AVX computations
//#define USE_AVX
// Uncomment/comment to enable/disable NEON computations
//#define USE_NEON

#ifdef _WIN32
#define INLINE __forceinline
#else
#define INLINE inline __attribute__((always_inline))
#endif

#include "timer.hpp"
#include "naive_implementation.hpp"
#include "expression_template.hpp"
#include "expression_template_simd.hpp"
#ifdef USE_SSE
	#include "sse_array.hpp"
#endif
#ifdef USE_AVX
	#include "avx_array.hpp"
#endif
#ifdef USE_NEON
	#include "neon_array.hpp"
#endif

#endif
