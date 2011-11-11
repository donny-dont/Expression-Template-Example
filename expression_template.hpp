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

			INLINE valarray_rep(std::size_t size)
				: _size(size)
				, _values(new Real[size])
			{ }

			INLINE valarray_rep(std::size_t size, Real value)
				: _size(size)
				, _values(new Real[size])
			{
				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = value;
			}

			INLINE ~valarray_rep()
			{
				delete[] _values;
			}

			INLINE valarray_rep(const valarray_rep& copy)
				: _size(copy._size)
				, _values(new Real[copy._size])
			{
				swap(copy);
			}

			INLINE valarray_rep& operator= (const valarray_rep& copy)
			{
				swap(copy);

				return *this;
			}

			INLINE std::size_t size() const
			{
				return _size;
			}

			INLINE Real operator[] (std::size_t i) const
			{
				return _values[i];
			}

			INLINE Real& operator[] (std::size_t i)
			{
				return _values[i];
			}

			INLINE void swap(const valarray_rep& copy)
			{
				assert(_size == copy._size);

				for (std::size_t i = 0; i < _size; ++i)
					_values[i] = copy._values[i];
			}

		private:

			std::size_t _size;
			Real* _values;

	} ; // end class valarray_rep<Real>


	template <typename Real, typename Rep = valarray_rep<Real> >
	class valarray
	{
		public:

			explicit valarray(std::size_t size)
				: _rep(size)
			{ }

			INLINE valarray(std::size_t size, Real value)
				: _rep(size, value)
			{ }

			INLINE valarray(const Rep& rep)
				: _rep(rep)
			{ }

			INLINE valarray(const valarray& copy)
				: _rep(copy._rep)
			{ }

			template <typename Rep2>
			INLINE valarray& operator= (const valarray<Real, Rep2>& copy)
			{
				assert(size() == copy.size());
				std::size_t count = size();

				for (std::size_t i = 0; i < count; ++i)
					_rep[i] = copy[i];

				return *this;
			}

			INLINE std::size_t size() const
			{
				return _rep.size();
			}

			INLINE Real operator[] (std::size_t i) const
			{
				return _rep[i];
			}

			INLINE Real& operator[] (std::size_t i)
			{
				return _rep[i];
			}

			INLINE const Rep& rep() const
			{
				return _rep;
			}

		private:

			Rep _rep;

	} ; // end class valarray<Real, Rep>

	template <typename Real, typename Op1, typename Op2>
	class valarray_add
	{
		public:

			INLINE valarray_add(const Op1& a, const Op2& b)
				: _op1(a)
				, _op2(b)
			{ }

			INLINE Real operator[] (std::size_t i) const
			{
				return _op1[i] + _op2[i];
			}

			INLINE std::size_t size() const
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

			INLINE valarray_mul(const Op1& a, const Op2& b)
				: _op1(a)
				, _op2(b)
			{ }

			INLINE Real operator[] (std::size_t i) const
			{
				return _op1[i] * _op2[i];
			}

			INLINE std::size_t size() const
			{
				return _op1.size();
			}

		private:

			const Op1& _op1;
			const Op2& _op2;

	} ; // end valarray_mul<Real, Op1, Op2>

	template <typename Real, typename Op>
	class valarray_sqrt
	{
		public:

			INLINE valarray_sqrt(const Op& a)
				: _op(a)
			{ }

			INLINE Real operator[] (std::size_t i) const
			{
				return std::sqrt(_op[i]);
			}

			INLINE std::size_t size() const
			{
				return _op.size();
			}

		private:

			const Op& _op;

	} ; // end valarray_sqrt<Real, Op>

	template <typename Real, typename Lhs, typename Rhs>
	INLINE valarray<Real, valarray_add<Real, Lhs, Rhs> > operator+ (const valarray<Real, Lhs>& lhs, const valarray<Real, Rhs>& rhs)
	{
		return valarray<Real, valarray_add<Real, Lhs, Rhs> >(valarray_add<Real, Lhs, Rhs>(lhs.rep(), rhs.rep()));
	}

	template <typename Real, typename Lhs, typename Rhs>
	INLINE valarray<Real, valarray_mul<Real, Lhs, Rhs> > operator* (const valarray<Real, Lhs>& lhs, const valarray<Real, Rhs>& rhs)
	{
		return valarray<Real, valarray_mul<Real, Lhs, Rhs> >(valarray_mul<Real, Lhs, Rhs>(lhs.rep(), rhs.rep()));
	}

	template <typename Real, typename Op>
	INLINE valarray<Real, valarray_sqrt<Real, Op> > sqrt(const valarray<Real, Op>& value)
	{
		return valarray<Real, valarray_sqrt<Real, Op> >(valarray_sqrt<Real, Op>(value.rep()));
	}

} // end namespace expression_template

#endif // end EXPRESSION_TEMPLATE_HPP_INCLUDED
