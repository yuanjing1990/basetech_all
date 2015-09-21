#pragma once 
#include <bitset>
#include <iostream>
template <class T>
class Nest
{
	typedef typename T::iterator* ptr;
};
template <int N>
void PrintBitset(std::bitset<N> const& bs)
{
	std::cout << bs.template to_string<std::string::value_type,std::string::traits_type,std::string::allocator_type >() << std::endl;
}