#ifndef ACCUM_HPP
#define ACCUM_HPP
#include "accumtraits1.hpp"
#include <iterator>

// 函数不能使用默认的模版参数，只有类可以
// template <typename T/*,typename traits = AccumulationTraits<T>*/ >
// inline
// typename AccumulationTraits<T>::Acct accum(T const* beg,T const* end)
//{
//	typedef typename AccumulationTraits<T>::Acct Acct;
//	Acct total = AccumulationTraits<T>::zero;
//	while(beg != end){
//		total += *beg;
//		++beg;
//	}
//	return total;
//};

// 修改后使用迭代器的traits
template <typename Iter>
inline typename std::iterator_traits<Iter>::value_type accum(Iter start,
                                                             Iter end) {
    typedef typename std::iterator_traits<Iter>::value_type VT;
    VT total = VT();
    while (start != end) {
        total += *start;
        ++start;
    }
    return total;
}

#endif
