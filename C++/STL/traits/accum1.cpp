#include "accum1.hpp"
#include "multpolicy1.hpp"
#include <iostream>
int main()
{
	int num[] = {1,2,3,4,5};
	//��Ϊ��ʼ����ֵΪ�㣬���������͵Ľ��Ϊ0
	std::cout << "the average value of the inter values is "
		<< accum(&num[0],&num[5]) / 5
		<< '\n';
	char name[] = "templates";
	int length = sizeof(name) - 1;
	std::cout << "the average value of the characters in \""
		<< name << "\" is "
		<< accum(&name[0], &name[length]) / length
		<< '\n';
}