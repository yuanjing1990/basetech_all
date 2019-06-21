#ifndef SQRT1_HPP
#define SQRT1_HPP
template <int N, int LO = 1, int HI = N> class Sqrt {
  public:
    enum { mid = (LO + HI + 1) / 2 };
    enum {
        result = (N < mid * mid) ? Sqrt<N, LO, mid - 1>::result
                                 : Sqrt<N, mid, HI>::result
    };
};
template <int N, int M> class Sqrt<N, M, M> {
  public:
    enum { result = M };
};
#endif
