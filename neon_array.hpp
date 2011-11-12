#ifndef NEON_ARRAY_HPP_INCLUDED
#define NEON_ARRAY_HPP_INCLUDED

#ifdef _WIN32
#include <malloc.h>
#endif
#include <cassert>
#include <cstddef>
#include <arm_neon.h>

namespace expression_template_simd
{
	template <typename Real>
	class valarray_rep_neon;

	INLINE float32x4_t add(const float32x4_t& lhs, const float32x4_t& rhs)
	{
		return vaddq_f32(lhs, rhs);
	}

	INLINE float32x4_t mul(const float32x4_t& lhs, const float32x4_t& rhs)
	{
		return vmulq_f32(lhs, rhs);
	}

	INLINE float32x4_t madd(const float32x4_t& a, const float32x4_t& b, const float32x4_t& c)
	{
		return vmlaq_f32(a, b, c);
	}

	INLINE float32x4_t square_root(const float32x4_t& v)
	{
		return vmulq_f32(v, vrsqrteq_f32(v));
	}

	INLINE float get(const float32x4_t& value, std::size_t i)
	{
	#ifdef _WIN32
		return value.n128_f32[i];
	#else
		return 0.0f;
	#endif
	}

	template <>
	class valarray_rep_neon<float>
	{
		public:

			typedef float value_type;
			typedef float32x4_t element_type;

			INLINE valarray_rep_neon(std::size_t size)
				: _size(size)
				, _elements((size / element_size()) + ((size % element_size() == 0) ? 0 : 1))
			{
				 _values = (element_type*)_mm_malloc(_elements * sizeof(element_type), alignment());
			}

			INLINE valarray_rep_neon(std::size_t size, value_type value)
				: _size(size)
				, _elements((size / element_size()) + ((size % element_size() == 0) ? 0 : 1))
			{
				 _values = (element_type*)_mm_malloc(_elements * sizeof(element_type), alignment());

				 const float32x4_t value_sse = vdupq_n_f32(value);

				 for (std::size_t i = 0; i < _elements; ++i)
					 _values[i] = value_sse;
			}

			INLINE ~valarray_rep_neon()
			{
				_mm_free(_values);
			}

			INLINE valarray_rep_neon(const valarray_rep_neon& copy)
				: _size(copy._size)
				, _elements(copy._elements)
			{
				 _values = (element_type*)_mm_malloc(_elements, alignment());

				 swap(copy);
			}

			INLINE valarray_rep_neon& operator= (const valarray_rep_neon& copy)
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

			INLINE void swap(const valarray_rep_neon& copy)
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

#endif // end NEON_ARRAY_HPP_INCLUDED
