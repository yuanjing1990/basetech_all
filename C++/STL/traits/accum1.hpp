#ifndef ACCUM_HPP
#define ACCUM_HPP
#include "accumtraits1.hpp"
#include <iterator>

//��������ʹ��Ĭ�ϵ�ģ�������ֻ�������
//template <typename T/*,typename traits = AccumulationTraits<T>*/ >
//inline
//typename AccumulationTraits<T>::Acct accum(T const* beg,T const* end)
//{
//	typedef typename AccumulationTraits<T>::Acct Acct;
//	Acct total = AccumulationTraits<T>::zero;
//	while(beg != end){
//		total += *beg;
//		++beg;
//	}
//	return total;
//};

//�޸ĺ�ʹ�õ�������traits
template <typename Iter>
inline
typename std::iterator_traits<Iter>::value_type accum(Iter start,Iter end)
{
	typedef typename std::iterator_traits<Iter>::value_type VT;
	VT total = VT();
	while(start != end)
	{
		total += *start;
		++start;
	}
	return total;
}

#endif