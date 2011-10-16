#ifndef NAIVE_IMPLEMENTATION_HPP_INCLUDED
#define NAIVE_IMPLEMENTATION_HPP_INCLUDED

#include <cassert>
#include <cstddef>

namespace naive_implementation
{
	template <typename Real>
	class valarray
	{
		public:

			inline valarray(std::size_t size)
			: _size(size)
			, _values(new Real[size])
			{ }

			inline valarray(std::size_t size, Real value)
			: _size(size)
			, _values(new Real[size])
			{
				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = value;
			}

			inline ~valarray()
			{
				delete[] _values;
			}

			inline valarray(const valarray& copy)
				: _size(copy._size)
				, _values(new Real[copy._size])
			{
				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = copy._values[i];
			}

			inline valarray& operator= (const valarray& copy)
			{
				assert(_size == copy._size);

				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = copy._values[i];

				return *this;
			}

			inline Real operator[] (std::size_t i) const
			{
				assert(i < _size);

				return _values[i];
			}

			inline valarray operator+ (const valarray& rhs) const
			{
				assert(_size == rhs._size);

				valarray result(_size);

				for (std::size_t i = 0; i < _size; ++i)
					result._values[i] = _values[i] + rhs._values[i];

				return result;
			}

			inline valarray operator* (const valarray& rhs) const
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

} // end namespace naive_implementation

#endif // end NAIVE_IMPLEMENTATION_HPP_INCLUDED
