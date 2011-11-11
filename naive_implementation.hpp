#ifndef NAIVE_IMPLEMENTATION_HPP_INCLUDED
#define NAIVE_IMPLEMENTATION_HPP_INCLUDED

#include <cassert>
#include <cstddef>
#include <cmath>

namespace naive_implementation
{
	template <typename Real>
	class valarray
	{
		public:

			INLINE valarray(std::size_t size)
			: _size(size)
			, _values(new Real[size])
			{ }

			INLINE valarray(std::size_t size, Real value)
			: _size(size)
			, _values(new Real[size])
			{
				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = value;
			}

			INLINE ~valarray()
			{
				delete[] _values;
			}

			INLINE valarray(const valarray& copy)
				: _size(copy._size)
				, _values(new Real[copy._size])
			{
				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = copy._values[i];
			}

			INLINE valarray& operator= (const valarray& copy)
			{
				assert(_size == copy._size);

				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = copy._values[i];

				return *this;
			}

			INLINE Real operator[] (std::size_t i) const
			{
				assert(i < _size);

				return _values[i];
			}

			INLINE Real& operator[] (std::size_t i)
			{
				assert(i < _size);

				return _values[i];
			}

			INLINE std::size_t size() const
			{
				return _size;
			}

			INLINE valarray operator+ (const valarray& rhs) const
			{
				assert(_size == rhs._size);

				valarray result(_size);

				for (std::size_t i = 0; i < _size; ++i)
					result._values[i] = _values[i] + rhs._values[i];

				return result;
			}

			INLINE valarray operator* (const valarray& rhs) const
			{
				assert(_size == rhs._size);

				valarray result(_size);

				for (std::size_t i = 0; i < _size; ++i)
					result._values[i] = _values[i] * rhs._values[i];

				return result;
			}

		private:

			std::size_t _size;
			Real* _values;

	} ; // end class valarray<Real>

	template <typename Real>
	INLINE valarray<Real> sqrt(const valarray<Real>& value)
	{
		const std::size_t size = value.size();
		valarray<Real> result(size);

		for (std::size_t i = 0; i < size; ++i)
			result[i] = std::sqrt(value[i]);

		return result;
	}

} // end namespace naive_implementation

#endif // end NAIVE_IMPLEMENTATION_HPP_INCLUDED
