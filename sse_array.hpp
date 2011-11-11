#ifndef SSE_ARRAY_HPP_INCLUDED
#define SSE_ARRAY_HPP_INCLUDED

#ifdef _WIN32
#include <malloc.h>
#endif
#include <cassert>
#include <cstddef>
#include <emmintrin.h>

namespace expression_template_simd
{
	template <typename Real>
	class valarray_rep_sse;

	INLINE __m128 add(const __m128& lhs, const __m128& rhs)
	{
		return _mm_add_ps(lhs, rhs);
	}

	INLINE __m128 mul(const __m128& lhs, const __m128& rhs)
	{
		return _mm_mul_ps(lhs, rhs);
	}

	INLINE __m128 madd(const __m128& a, const __m128& b, const __m128& c)
	{
		return _mm_add_ps(a, _mm_mul_ps(b, c));
	}

	INLINE __m128 square_root(const __m128& v)
	{
		return _mm_sqrt_ps(v);
	}

	INLINE float get(const __m128& value, std::size_t i)
	{
	#ifdef _WIN32
		return value.m128_f32[i];
	#else
		return 0.0f;
	#endif
	}

	template <>
	class valarray_rep_sse<float>
	{
		public:

			typedef float value_type;
			typedef __m128 element_type;

			INLINE valarray_rep_sse(std::size_t size)
				: _size(size)
				, _elements((size / element_size()) + ((size % element_size() == 0) ? 0 : 1))
			{
				 _values = (element_type*)_mm_malloc(_elements * sizeof(element_type), alignment());
			}

			INLINE valarray_rep_sse(std::size_t size, value_type value)
				: _size(size)
				, _elements((size / element_size()) + ((size % element_size() == 0) ? 0 : 1))
			{
				 _values = (element_type*)_mm_malloc(_elements * sizeof(element_type), alignment());

				 const __m128 value_sse = _mm_set1_ps(value);

				 for (std::size_t i = 0; i < _elements; ++i)
					 _values[i] = value_sse;
			}

			INLINE ~valarray_rep_sse()
			{
				_mm_free(_values);
			}

			INLINE valarray_rep_sse(const valarray_rep_sse& copy)
				: _size(copy._size)
				, _elements(copy._elements)
			{
				 _values = (element_type*)_mm_malloc(_elements, alignment());

				 swap(copy);
			}

			INLINE valarray_rep_sse& operator= (const valarray_rep_sse& copy)
			{
				swap(copy);

				return *this;
			}

			INLINE element_type operator() (std::size_t i) const
			{
				assert(i < _elements);

				return _values[i];
			}

			INLINE element_type& operator() (std::size_t i)
			{
				assert(i < _elements);

				return _values[i];
			}

			INLINE float operator[] (std::size_t i) const
			{
				assert(i < _size);

				const std::size_t element = i / element_size();
				const std::size_t index = i % element_size();

				return get(_values[element], index);
			}

			INLINE std::size_t size() const
			{
				return _size;
			}

			INLINE std::size_t elements() const
			{
				return _elements;
			}

			INLINE static std::size_t alignment()
			{
				return sizeof(element_type);
			}

			INLINE static std::size_t element_size()
			{
				return sizeof(element_type) / sizeof(value_type);
			}

			INLINE void swap(const valarray_rep_sse& copy)
			{
				assert(_size == copy._size);

				for (std::size_t i = 0; i < _elements; ++i)
					_values[i] = copy._values[i];
			}

		private:

			std::size_t _size;
			std::size_t _elements;
			element_type* _values;

	} ; // end class valarray_rep_sse<float>

} // end namespace expression_template_simd

#endif // end SSE_ARRAY_HPP_INCLUDED
