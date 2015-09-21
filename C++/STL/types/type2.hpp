#ifndef TYPE2_HPP
#define TYPE2_HPP
//�ж������Ƿ���ָ�룬���ã����飬��������Աָ��
//����ģ��
template <typename T>
class CompoundT{
	public:
		enum{IsPtrT = 0,IsRefT = 0,IsArrayT = 0,IsFuncT = 0,IsPtrMemT = 0};
		typedef T BaseT;
		typedef T BottomT;
		typedef CompoundT<void> ClassT;
};

//�ж������õ�ƫ�ػ�
template<typename T>
class CompoundT<T&>{
	public:
		enum{IsPtrT = 0,IsRefT = 1,IsArrayT = 0,IsFuncT = 0,IsPtrMemT = 0};
		typedef T BaseT;
		typedef typename CompoundT<T>::BottomT BottomT;
		typedef CompoundT<void> ClassT;
};

//�ж���ָ���ƫ�ػ�
template<typename T>
class CompoundT<T*>{
	public:
		enum{IsPtrT = 1,IsRefT = 0,IsArrayT = 0,IsFuncT = 0,IsPtrMemT = 0};
		typedef T BaseT;
		typedef typename CompoundT<T>::BottomT BottomT;
		typedef CompoundT<void> ClassT;
};

//�ж��������ƫ�ػ�
template<typename T,size_t N>
class CompoundT<T[N]>{
	public:
		enum{IsPtrT = 0,IsRefT = 0,IsArrayT = 1,IsFuncT = 0,IsPtrMemT = 0};
		typedef T BaseT;
		typedef typename CompoundT<T>::BottomT BottomT;
		typedef CompoundT<void> ClassT;
};

//�ж��������ƫ�ػ�
template<typename T>
class CompoundT<T[]>{
	public:
		enum{IsPtrT = 1,IsRefT = 0,IsArrayT = 0,IsFuncT = 0,IsPtrMemT = 0};
		typedef T BaseT;
		typedef typename CompoundT<T>::BottomT BottomT;
		typedef CompoundT<void> ClassT;
};

//�ж��ǳ�Աָ���ƫ�ػ�
template<typename T,typename C>
class CompoundT<T C::*>{
	public:
		enum{IsPtrT = 0,IsRefT = 0,IsArrayT = 0,IsFuncT = 0,IsPtrMemT = 1};
		typedef T BaseT;
		typedef typename CompoundT<T>::BottomT BottomT;
		typedef C ClassT;
};
#endif