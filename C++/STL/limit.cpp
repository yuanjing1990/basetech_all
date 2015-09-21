#include <limits>
#include <iostream>
int main(int argc,char* argv[])
{
	std::cout << std::numeric_limits<int>::min() << std::endl;
	std::cout << std::numeric_limits<int>::max() << std::endl;
}