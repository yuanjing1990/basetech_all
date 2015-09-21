#include "boost/any.hpp"
#include <list>
#include <iostream>
using boost::any_cast;
typedef std::list<boost::any> many;
void append_any(many& values,boost::any value)
{
	values.push_back(value);
}
std::ostream& operator<<(std::ostream& os,boost::any value)
{
	if(value.type() == typeid(int))
		os << any_cast<int>(value);
	else if(value.type() == typeid(double))
		os << any_cast<double>(value);
	else if(value.type() == typeid(float))
		os << any_cast<float>(value);
	else if(value.type() == typeid(char*))
		os << any_cast<char*>(value);
	return os;
}
void print_any(boost::any value)
{
	std::cout << value << std::endl;
}
int main(int argc,char* argv[])
{
	many values;
	append_any(values,12.3);
	append_any(values,123);
	std::for_each(values.begin(),values.end(),print_any);
	return 0;
}
