//#include "mystl/any.h"
#include <boost/any.hpp>
#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

#ifndef YJ_STL_VERSION
#define yj boost
#else
#define boost yj
#endif

int main(int argc,char** argv)
{
	yj::any e1(3);
	yj::any e2(4.5);
	//printf("The e1 is:%d\n",yj::any_cast<int>(e1));	
	//printf("The e2 is:%f\n",yj::any_cast<double>(e2));	
	
	e1 = e2;
	//printf("The e1 is:%f\n",yj::any_cast<double>(e1));	
	//printf("The e2 is:%f\n",yj::any_cast<double>(e2));	

	//boost::asio::io_service io;
	//boost::asio::deadline_timer t(io,boost::posix_time::seconds(5));
	//t.wait();
	std::cout << "Hello World!\n";
	
	//using namespace boost::gregorian;
	//date today = day_clock::local_day();
	//std::cout << today << std::endl;
	return 0;
}
