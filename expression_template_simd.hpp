#ifndef EXPRESSION_TEMPLATE_SIMD_HPP_INCLUDED
#define EXPRESSION_TEMPLATE_SIMD_HPP_INCLUDED

#include <cassert>
#include <cstddef>

namespace expression_template_simd
{
	template <typename Real>
	class valarray_rep_sse;

	template <typename Real, typename Rep = valarray_rep_sse<Real> >
	class valarray
	{
		public:

			typedef Real value_type;
			typedef typename Rep::element_type element_type;

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
				assert(elements() == copy.elements());

				for (std::size_t i = 0, count = elements(); i < count; ++i)
					_rep(i) = copy(i);

				return *this;
			}

			inline std::size_t size() const
			{
				return _rep.size();
			}

			inline std::size_t elements() const
			{
				return _rep.elements();
			}

			inline value_type operator[] (std::size_t i) const
			{
				return _rep[i];
			}

			inline element_type operator() (std::size_t i) const
			{
				return _rep(i);
			}

			inline element_type& operator() (std::size_t i)
			{
				return _rep(i);
			}

			inline const Rep& rep() const
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

			typedef Real value_type;
			typedef typename Op1::element_type element_type;

			inline valarray_add(const Op1& a, const Op2& b)
				: _op1(a)
				, _op2(b)
			{ }

			inline element_type operator() (std::size_t i) const
			{
				return add(_op1(i), _op2(i));
			}

			inline std::size_t size() const
			{
				return _op1.size();
			}

			inline std::size_t elements() const
			{
				return _op1.elements();
			}

		private:

			const Op1& _op1;
			const Op2& _op2;

	} ; // end valarray_add<Real, Op1, Op2>

	template <typename Real, typename Op1, typename Op2>
	class valarray_mul
	{
		public:

			typedef Real value_type;
			typedef typename Op1::element_type element_type;

			inline valarray_mul(const Op1& a, const Op2& b)
				: _op1(a)
				, _op2(b)
			{ }

			inline element_type operator() (std::size_t i) const
			{
				return mul(_op1(i), _op2(i));
			}

			inline std::size_t size() const
			{
				return _op1.size();
			}

			inline std::size_t elements() const
			{
				return _op1.elements();
			}

		private:

			const Op1& _op1;
			const Op2& _op2;

	} ; // end valarray_mul<Real, Op1, Op2>

	template <typename Real, typename Op>
	class valarray_sqrt
	{
		public:

			typedef Real value_type;
			typedef typename Op::element_type element_type;

			inline valarray_sqrt(const Op& a)
				: _op(a)
			{ }

			inline element_type operator() (std::size_t i) const
			{
				return sqrt(_op(i));
			}

			inline std::size_t size() const
			{
				return _op.size();
			}

			inline std::size_t elements() const
			{
				return _op.elements();
			}

		private:

			const Op& _op;

	} ; // end valarray_sqrt<Real, Op>

	template <typename Real, typename Lhs, typename Rhs>
	inline valarray<Real, valarray_add<Real, Lhs, Rhs> > operator+ (const valarray<Real, Lhs>& lhs, const valarray<Real, Rhs>& rhs)
	{
		return valarray<Real, valarray_add<Real, Lhs, Rhs> >(valarray_add<Real, Lhs, Rhs>(lhs.rep(), rhs.rep()));
	}

	template <typename Real, typename Lhs, typename Rhs>
	inline valarray<Real, valarray_mul<Real, Lhs, Rhs> > operator* (const valarray<Real, Lhs>& lhs, const valarray<Real, Rhs>& rhs)
	{
		return valarray<Real, valarray_mul<Real, Lhs, Rhs> >(valarray_mul<Real, Lhs, Rhs>(lhs.rep(), rhs.rep()));
	}

	template <typename Real, typename Op>
	inline valarray<Real, valarray_sqrt<Real, Op> > sqrt(const valarray<Real, Op>& value)
	{
		return valarray<Real, valarray_sqrt<Real, Op> >(valarray_sqrt<Real, Op>(value.rep()));
	}

} // end namespace expression_template_simd

#endif // end EXPRESSION_TEMPLATE_SIMD_HPP_INCLUDED
