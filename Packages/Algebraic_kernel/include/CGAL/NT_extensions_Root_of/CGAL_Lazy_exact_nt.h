// Copyright (c) 2003  INRIA Sophia-Antipolis (France) and
//                     Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// Authors : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//           Sylvain Pion     <Sylvain.Pion@sophia.inria.fr>
//           Athanasios Kakargias <grad0460@di.uoa.gr>
// 
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (CGAL - Effective Computational Geometry for Curves and Surfaces) 

// file : include/CGAL/Root_of/CGAL_Lazy_exact_nt.h

#ifndef CGAL_ROOT_OF_CGAL_LAZY_EXACT_NT_H
#define CGAL_ROOT_OF_CGAL_LAZY_EXACT_NT_H

#include <CGAL/Binary_operator_result.h>
#include <CGAL/Lazy_exact_nt.h>
#include <CGAL/NT_extensions_Root_of/CGAL_Interval_nt.h>

#if 1

CGAL_BEGIN_NAMESPACE

// Specializations for Root_of_2.
// T1 can be different from T2 because of quotient types...
template < typename T1, typename T2 >
struct Binary_operator_result <T1, Root_of_2<T2> > {
    typedef Root_of_2<T2>  type;
};

template < typename T1, typename T2 >
struct Binary_operator_result <Root_of_2<T1>, T2> {
    typedef Root_of_2<T1>  type;
};


// We create a type of new node in Lazy_exact_nt's DAG
// for the make_root_of_2() operation.

template <typename ET>
struct Lazy_exact_ro2
  : public CGAL::Lazy_exact_rep< typename Root_of_traits<ET>::RootOf_2 >
{
    typedef typename Root_of_traits<ET>::RootOf_2   RO2;
    typedef Lazy_exact_rep<RO2>                     Base;

    mutable Lazy_exact_nt<ET> op1, op2, op3;
    bool smaller;

    Lazy_exact_ro2 (const Lazy_exact_nt<ET> &a,
		    const Lazy_exact_nt<ET> &b,
		    const Lazy_exact_nt<ET> &c, bool s)
      : Base(make_root_of_2(a.approx(), b.approx(), c.approx(), s)),
        op1(a), op2(b), op3(c), smaller(s) {}

    void update_exact() const
    {
	this->et = new RO2(make_root_of_2(op1.exact(), op2.exact(),
					  op3.exact(), smaller));
	if (!this->approx().is_point())
            this->in = CGAL::to_interval(*(this->et));
	this->prune_dag();
    }

    void prune_dag() const
    {
	op1 = op2 = op3 = Lazy_exact_nt<ET>::zero();
    }
};

template < typename ET >
inline
Lazy_exact_nt< typename Root_of_traits<ET>::RootOf_2 >
make_root_of_2( const Lazy_exact_nt<ET> &a,
                const Lazy_exact_nt<ET> &b,
                const Lazy_exact_nt<ET> &c, bool d)
{
    return new Lazy_exact_ro2<ET>(a, b, c, d);
}

template <typename NT >
struct Root_of_traits< Lazy_exact_nt < NT > >
{
    typedef Root_of_traits<NT> T;
    typedef Lazy_exact_nt< typename T::RootOf_1 > RootOf_1;
    typedef Lazy_exact_nt< typename T::RootOf_2 > RootOf_2;
    typedef Lazy_exact_nt< typename T::RootOf_3 > RootOf_3;
    typedef Lazy_exact_nt< typename T::RootOf_4 > RootOf_4;
};

CGAL_END_NAMESPACE

#endif

#endif // CGAL_ROOT_OF_CGAL_LAZY_EXACT_NT_H
