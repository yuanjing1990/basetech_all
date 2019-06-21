#ifndef SQRT2_HPP
#define SQRT2_HPP
#include "ifthenelse.hpp"
template <int N, int LO = 1, int HI = N> class Sqrt {
  public:
    enum { mid = (LO + HI + 1) / 2 };
    typedef typename IfThenElse<(N < mid * mid), Sqrt<N, LO, mid - 1>,
                                Sqrt<N, mid, HI>>::ResultT SubT;
    enum { result = SubT::result };
};
template <int N, int S> class Sqrt<N, S, S> {
  public:
    enum { result = S };
};
#endif
