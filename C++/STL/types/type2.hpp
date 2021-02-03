#ifndef TYPE2_HPP
#define TYPE2_HPP
#include <stddef.h>
//判断类型是否是指针，引用，数组，函数，成员指针
//基础模版
template <typename T> class CompoundT {
  public:
    enum { IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0 };
    typedef T BaseT;
    typedef T BottomT;
    typedef CompoundT<void> ClassT;
};

//判断是引用的偏特化
template <typename T> class CompoundT<T &> {
  public:
    enum { IsPtrT = 0, IsRefT = 1, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0 };
    typedef T BaseT;
    typedef typename CompoundT<T>::BottomT BottomT;
    typedef CompoundT<void> ClassT;
};

//判断是指针的偏特化
template <typename T> class CompoundT<T *> {
  public:
    enum { IsPtrT = 1, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0 };
    typedef T BaseT;
    typedef typename CompoundT<T>::BottomT BottomT;
    typedef CompoundT<void> ClassT;
};

//判断是数组的偏特化
template <typename T, size_t N> class CompoundT<T[N]> {
  public:
    enum { IsPtrT = 0, IsRefT = 0, IsArrayT = 1, IsFuncT = 0, IsPtrMemT = 0 };
    typedef T BaseT;
    typedef typename CompoundT<T>::BottomT BottomT;
    typedef CompoundT<void> ClassT;
};

//判断是数组的偏特化
template <typename T> class CompoundT<T[]> {
  public:
    enum { IsPtrT = 1, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0 };
    typedef T BaseT;
    typedef typename CompoundT<T>::BottomT BottomT;
    typedef CompoundT<void> ClassT;
};

//判断是成员指针的偏特化
template <typename T, typename C> class CompoundT<T C::*> {
  public:
    enum { IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 1 };
    typedef T BaseT;
    typedef typename CompoundT<T>::BottomT BottomT;
    typedef C ClassT;
};
#endif