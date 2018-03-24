#include <limits>
#include <iostream>
//limits文件定义了一些系统限制，这里展示了一些使用方法和限制值
int main(int argc,char* argv[])
{
	std::cout << std::numeric_limits<int>::min() << std::endl;
	std::cout << std::numeric_limits<int>::max() << std::endl;
}
