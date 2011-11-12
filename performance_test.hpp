#ifndef PERFORMANCE_TEST_HPP_INCLUDED
#define PERFORMANCE_TEST_HPP_INCLUDED

#include "config.hpp"

//---------------------------------------------------------------------
// valarray implementations
//---------------------------------------------------------------------

double time_naive_array(std::size_t size);
double time_expr_template_float(std::size_t size);
double time_expr_template_sse(std::size_t size);
double time_expr_template_avx(std::size_t size);
double time_expr_template_neon(std::size_t size);

//---------------------------------------------------------------------
// C array implementations
//---------------------------------------------------------------------

double time_float_arrays(std::size_t size);
double time_sse_arrays(std::size_t elements);
double time_avx_arrays(std::size_t elements);
double time_neon_arrays(std::size_t elements);

#endif // end PERFORMANCE_TEST_HPP_INCLUDED
