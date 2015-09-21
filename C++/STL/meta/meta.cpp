#include <iostream>
#include "pow3.hpp"
#include "sqrt2.hpp"
#include "loop.hpp"
int main(int argc,char* argv[])
{
	std::cout << "Pow3<3>::result = " << Pow3<3>::result << std::endl;
	std::cout << "Sqrt<16>::result = " << Sqrt<16>::result << std::endl;
	std::cout << "Sqrt<25>::result = " << Sqrt<25>::result << std::endl;
	std::cout << "Sqrt<10000>::result = " << Sqrt<10000>::result << std::endl;
	std::cout << "Sqrt<1>::result = " << Sqrt<1>::result << std::endl;
	int a[3] = {1,2,3};
	int b[3] = {4,5,6};
	std::cout << "dot_product<3>(a,b) = " <<
		dot_product<3>(a,b) << std::endl;
	std::cout << "dot_product<3>(a,a) = " <<
		dot_product<3>(a,a) << std::endl;
}