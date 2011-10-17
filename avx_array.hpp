#ifndef AVX_ARRAY_HPP_INCLUDED
#define AVX_ARRAY_HPP_INCLUDED

#include <malloc.h>
#include <cassert>
#include <cstddef>
#include <immintrin.h>

namespace expression_template_simd
{
	template <typename Real>
	class valarray_rep_avx;

	inline __m256 add(const __m256& lhs, const __m256& rhs)
	{
		return _mm256_add_ps(lhs, rhs);
	}

	inline __m256 mul(const __m256& lhs, const __m256& rhs)
	{
		return _mm256_mul_ps(lhs, rhs);
	}

	inline __m256 sqrt(const __m256& v)
	{
		return _mm256_sqrt_ps(v);
	}

	inline float get(const __m256& value, std::size_t i)
	{
		return value.m256_f32[i];
	}

	template <>
	class valarray_rep_avx<float>
	{
		public:

			typedef float value_type;
			typedef __m256 element_type;

			inline valarray_rep_avx(std::size_t size)
				: _size(size)
				, _elements((size / element_size()) + ((size % element_size() == 0) ? 0 : 1))
			{
				 _values = (element_type*)_mm_malloc(_elements * sizeof(element_type), alignment());
			}

			inline valarray_rep_avx(std::size_t size, value_type value)
				: _size(size)
				, _elements((size / element_size()) + ((size % element_size() == 0) ? 0 : 1))
			{
				 _values = (element_type*)_mm_malloc(_elements * sizeof(element_type), alignment());

				 const __m256 value_sse = _mm256_set1_ps(value);

				 for (std::size_t i = 0; i < _elements; ++i)
					 _values[i] = value_sse;
			}

			inline ~valarray_rep_avx()
			{
				_mm_free(_values);
			}

			inline valarray_rep_avx(const valarray_rep_avx& copy)
				: _size(copy._size)
				, _elements(copy._elements)
			{
				 _values = (element_type*)_mm_malloc(_elements, alignment());

				 swap(copy);
			}

			inline valarray_rep_avx& operator= (const valarray_rep_avx& copy)
			{
				swap(copy);

				return *this;
			}

			inline element_type operator() (std::size_t i) const
			{
				assert(i < _elements);

				return _values[i];
			}

			inline element_type& operator() (std::size_t i)
			{
				assert(i < _elements);

				return _values[i];
			}

			inline float operator[] (std::size_t i) const
			{
				assert(i < _size);

				const std::size_t element = i / element_size();
				const std::size_t index = i % element_size();

				return get(_values[element], index);
			}

			inline std::size_t size() const
			{
				return _size;
			}

			inline std::size_t elements() const
			{
				return _elements;
			}

			inline static std::size_t alignment()
			{
				return sizeof(element_type);
			}

			inline static std::size_t element_size()
			{
				return sizeof(element_type) / sizeof(value_type);
			}

			inline void swap(const valarray_rep_avx& copy)
			{
				assert(_size == copy._size);

				for (std::size_t i = 0; i < _elements; ++i)
					_values[i] = copy._values[i];
			}

		private:

			std::size_t _size;
			std::size_t _elements;
			element_type* _values;

	} ; // end class valarray_rep_avx<float>

} // end namespace expression_template_simd

#endif // end AVX_ARRAY_HPP_INCLUDED
