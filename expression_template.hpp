#ifndef EXPRESSION_TEMPLATE_HPP_INCLUDED
#define EXPRESSION_TEMPLATE_HPP_INCLUDED

#include <cassert>
#include <cstddef>

namespace expression_template
{
	template <typename Real>
	class valarray_rep
	{
		public:

			inline valarray_rep(std::size_t size)
				: _size(size)
				, _values(new Real[size])
			{ }

			inline valarray_rep(std::size_t size, Real value)
				: _size(size)
				, _values(new Real[size])
			{
				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = value;
			}

			inline ~valarray_rep()
			{
				delete[] _values;
			}

			inline valarray_rep(const valarray_rep& copy)
				: _size(copy._size)
				, _values(new Real[copy._size])
			{
				swap(copy) 
			}

			inline valarray_rep& operator= (const valarray_rep& copy)
			{
				swap(copy);

				return *this;
			}

			inline std::size_t size() const
			{
				return _size;
			}

			inline Real operator[] (std::size_t i) const
			{
				return _values[i];
			}

			inline Real& operator[] (std::size_t i)
			{
				return _values[i];
			}

			inline void swap(const valarray_rep& copy)
			{
				assert(_size == copy._size);

				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = copy._values[i];
			}

		private:

			std::size_t _size;
			Real* _values;
	} ;


	template <typename Real, typename Rep = valarray_rep<Real> >
	class valarray
	{
		public:

			explicit valarray(std::size_t size)
				: _rep(size)
			{ }

			inline valarray(std::size_t size, Real value)
				: _rep(size, value)
			{ }

			inline valarray(const Rep& rep)
				: _rep(rep)
			{ }

			inline valarray(const valarray& copy)
				: _rep(copy._rep)
			{ }

			template <typename Real, typename Rep2>
			inline valarray& operator= (const valarray<Real, Rep2>& copy)
			{
				assert(size() == copy.size());
				std::size_t count = size();

				for (std::size_t i = 0; i < count; ++i)
					_rep[i] = copy[i];

				return *this;
			}

			inline std::size_t size() const
			{
				return _rep.size();
			}

			inline Real operator[] (std::size_t i) const
			{
				return _rep[i];
			}

			inline Real& operator[] (std::size_t i)
			{
				return _rep[i];
			}

			inline const Rep& rep() const
			{
				return _rep;
			}

		private:

			Rep _rep;

	} ; // end class valarray<Real>

	template <typename Real, typename Op1, typename Op2>
	class valarray_add
	{
		public:

			inline valarray_add(const Op1& a, const Op2& b)
				: _op1(a)
				, _op2(b)
			{ }

			inline Real operator[] (std::size_t i) const
			{
				return _op1[i] + _op2[i];
			}

			inline std::size_t size() const
			{
				return _op1.size();
			}

		private:

			const Op1& _op1;
			const Op2& _op2;

	} ; // end valarray_add<Real, Op1, Op2>

	template <typename Real, typename Op1, typename Op2>
	class valarray_mul
	{
		public:

			inline valarray_mul(const Op1& a, const Op2& b)
				: _op1(a)
				, _op2(b)
			{ }

			inline Real operator[] (std::size_t i) const
			{
				return _op1[i] * _op2[i];
			}

			inline std::size_t size() const
			{
				return _op1.size();
			}

		private:

			const Op1& _op1;
			const Op2& _op2;

	} ; // end valarray_mul<Real, Op1, Op2>

	template <typename Real, typename Lhs, typename Rhs>
	valarray<Real, valarray_add<Real, Lhs, Rhs> > operator+ (const valarray<Real, Lhs>& lhs, const valarray<Real, Rhs>& rhs)
	{
		return valarray<Real, valarray_add<Real, Lhs, Rhs> >(valarray_add<Real, Lhs, Rhs>(lhs.rep(), rhs.rep()));
	}

	template <typename Real, typename Lhs, typename Rhs>
	valarray<Real, valarray_mul<Real, Lhs, Rhs> > operator* (const valarray<Real, Lhs>& lhs, const valarray<Real, Rhs>& rhs)
	{
		return valarray<Real, valarray_mul<Real, Lhs, Rhs> >(valarray_mul<Real, Lhs, Rhs>(lhs.rep(), rhs.rep()));
	}

} // end namespace expression_template

#endif // end EXPRESSION_TEMPLATE_HPP_INCLUDED
