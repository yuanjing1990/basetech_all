#ifndef ACCUM_HPP
#define ACCUM_HPP
#include "accumtraits1.hpp"
#include "sumpolicy1.hpp"
template <typename T, typename Policy = SumPolicy,
          typename AT = AccumulationTraits<T>>
class Accum {
  public:
    static typename AT::Acct accum(T const *beg, T const *end) {
        typename AT::Acct total = AT::zero;
        while (beg != end) {
            Policy::accumulate(total, *beg);
            ++beg;
        }
        return total;
    }
};
// 以下的两个函数无法编译？？？？？？？？？？？？？？？？？？？
// template <typename T>
// inline
// typename AccumulationTraits<T>::AccT accum(T const* beg,T const* end)
//{
//	return Accum<T>::accum(beg,end);
//}
// template <typename Traits,typename T>
// inline
// typename Traits::Acct accum(T const* beg,T const* end)
//{
//	return Accum<T,Traits>::accum(beg,end);
//}
#endif
