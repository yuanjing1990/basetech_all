#include <iostream>
class Empty{
	typedef int Type;
};
class EmptyTwo : public Empty{
};
class EmptyThree : public Empty, public EmptyTwo{
};

int main(int argc,char* argv[])
{
	std::cout << sizeof(Empty) << std::endl;
	std::cout << sizeof(EmptyTwo) << std::endl;
	std::cout << sizeof(EmptyThree) << std::endl;
	return 0;
}