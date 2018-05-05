//istream_iterator和ostream_iterator在头文件<iterator>里面定义
//istream_iteratro从输入流中提取数据，提取失败则返回一个默认构造函数构造出的迭代器istream_iterator<type>()
//ostream_iterator输出数据到输出流，如果给构造函数提供了第二个参数，表示输出分割符，赋值操作就表示向输出流输出元素
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <string>
using namespace std;
int main(int argc,char* argv[])
{
	//如果两个参数不用括号包起来的话，st会被认为是一个函数指针类型定义
	//错认的函数原型：std::set<int>(std::istream_iterator<int>, std::istream_iterator<int> (*)())
	set<int> st((istream_iterator<int>(cin)),(istream_iterator<int>()));
	cin.clear();
	//ostream_iterator构造函数第二个参数是输出分割符
	//假设st内容为12345，输出则为1525354555
	copy(st.begin(),st.end(),ostream_iterator<int>(cout,"5"));	
	return 0;
}