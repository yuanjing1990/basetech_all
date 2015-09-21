#include <iostream>
#include "type1.hpp"
#include "type2.hpp"
template <typename T>
void test(T const& t)
{
	if(IsFundaT<T>::Yes){
		std::cout << "T is funda type!\n";
	}
	else{
		std::cout << "T is no funda type!\n";
	}
}

template <typename T>
void test_type(T const& t){
	if(CompoundT<T>::IsPtrT){
		std::cout << "T is Ptr!\n";
	}
	else if(CompoundT<T>::IsRefT){
		std::cout << "T is Ref!\n";
	}
	else if(CompoundT<T>::IsArrayT){
		std::cout << "T is Array!\n";
	}
	else if(CompoundT<T>::IsFuncT){
		std::cout << "T is Func!\n";
	}
	else if(CompoundT<T>::IsPtrMemT){
		std::cout << "T is MemPtr!\n";
	}
	else
		std::cout << "T is not a Ptr,Ref,Array,Func,MemPtr!\n";
}

class MyType{
};
int main()
{
	test(7);
	test(MyType());
	test_type(7);
	test_type(&MyType());
}