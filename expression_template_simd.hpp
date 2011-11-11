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
				assert(elements() == copy.elements());

				for (std::size_t i = 0, count = elements(); i < count; ++i)
					_rep(i) = copy(i);

				return *this;
			}

			INLINE std::size_t size() const
			{
				return _rep.size();
			}

			INLINE std::size_t elements() const
			{
				return _rep.elements();
			}

			INLINE value_type operator[] (std::size_t i) const
			{
				return _rep[i];
			}

			INLINE element_type operator() (std::size_t i) const
			{
				return _rep(i);
			}

			INLINE element_type& operator() (std::size_t i)
			{
				return _rep(i);
			}

			INLINE const Rep& rep() const
			{
				return _rep;
			}

		private:

			Rep _rep;

	} ; // end class valarray<Real, Rep>

	template <typename Real, typename Op1, typename Op2>
	struct valarray_add
	{
		typedef Real value_type;
		typedef typename Op1::element_type element_type;

		INLINE valarray_add(const Op1& a, const Op2& b)
			: _op1(a)
			, _op2(b)
		{ }

		INLINE element_type operator() (std::size_t i) const
		{
			return add(_op1(i), _op2(i));
		}

		INLINE std::size_t size() const
		{
			return _op1.size();
		}

		INLINE std::size_t elements() const
		{
			return _op1.elements();
		}

		const Op1& _op1;
		const Op2& _op2;

	} ; // end valarray_add<Real, Op1, Op2>

	template <typename Real, typename Op1, typename Op2>
	struct valarray_mul
	{
		typedef Real value_type;
		typedef typename Op1::element_type element_type;

		INLINE valarray_mul(const Op1& a, const Op2& b)
			: _op1(a)
			, _op2(b)
		{ }

		INLINE element_type operator() (std::size_t i) const
		{
			return mul(_op1(i), _op2(i));
		}

		INLINE std::size_t size() const
		{
			return _op1.size();
		}

		INLINE std::size_t elements() const
		{
			return _op1.elements();
		}

		const Op1& _op1;
		const Op2& _op2;

	} ; // end valarray_mul<Real, Op1, Op2>

	template <typename Real, typename Op1, typename Op2, typename Op3>
	struct valarray_add<Real, Op1, valarray_mul<Real, Op2, Op3> >
	{
		typedef Real value_type;
		typedef typename Op1::element_type element_type;

		INLINE valarray_add(const Op1& a, const valarray_mul<Real, Op2, Op3>& b)
			: _op1(a)
			, _op2(b._op1)
			, _op3(b._op2)
		{ }

		INLINE element_type operator() (std::size_t i) const
		{
			return madd(_op1(i), _op2(i), _op3(i));
		}

		INLINE std::size_t size() const
		{
			return _op1.size();
		}

		INLINE std::size_t elements() const
		{
			return _op1.elements();
		}

		const Op1& _op1;
		const Op2& _op2;
		const Op3& _op3;
	} ;

	template <typename Real, typename Op>
	struct valarray_sqrt
	{
		typedef Real value_type;
		typedef typename Op::element_type element_type;

		INLINE valarray_sqrt(const Op& a)
			: _op(a)
		{ }

		INLINE element_type operator() (std::size_t i) const
		{
			return square_root(_op(i));
		}

		INLINE std::size_t size() const
		{
			return _op.size();
		}

		INLINE std::size_t elements() const
		{
			return _op.elements();
		}

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

} // end namespace expression_template_simd

#endif // end EXPRESSION_TEMPLATE_SIMD_HPP_INCLUDED
