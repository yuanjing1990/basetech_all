//#include "mystl/any.h"
#include <boost/any.hpp>
#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <functional>

#define BOOST_TEST_MODULE test_module
//动态链接方式必须定义此宏，否则main函数未定义
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test::framework;

#ifndef YJ_STL_VERSION
#define yj boost
#else
#endif

BOOST_AUTO_TEST_CASE(test_any)
{
	yj::any e1(3);
	yj::any e2(4.5);
	BOOST_TEST(3==yj::any_cast<int>(e1));
	BOOST_TEST(4.5==yj::any_cast<double>(e2));

	e1 = e2;
	BOOST_TEST(4.5==yj::any_cast<double>(e1));
	BOOST_TEST(4.5==yj::any_cast<double>(e2));
}

static bool flag = false;
void on_timeout(const boost::system::error_code& ec)
{
	BOOST_TEST(ec == boost::asio::error::operation_aborted);
	std::cout << "error_code=" << ec << std::endl;
	flag = true;
}

BOOST_AUTO_TEST_CASE(test_asio)
{
	using namespace boost::asio;
	io_service io;
	//deadline_timer是一个定时器，wait可以带一个异步函数到时间执行
	//下面是构造时直接设置的超时时间，也可以使用expires_from_now成员函数设置超时时间
	deadline_timer t(io,boost::posix_time::seconds(2));
	boost::system::error_code ec;
	//同步等待时间到达，wait返回boost::asio::error::operation_success
	t.wait(ec);
	BOOST_TEST(!ec);

	//expires_from_now可以取消正在等待的定时器异步处理，有定时器被取消返回1，否则返回0
	size_t sz = t.expires_from_now(boost::posix_time::seconds(2),ec);
	t.async_wait(on_timeout);
	BOOST_TEST(!ec);
	BOOST_TEST(sz == 0);

	//前一个超时时间没有到达就被expires_from_now取消，expires_from_now返回1
	//t.async_wait(std::bind2nd(std::mem_fun((void(deadline_timer::*)(boost::system::error_code&))&deadline_timer::cancel),t));
	sz = t.expires_from_now(boost::posix_time::seconds(2),ec);//这里取消定时异步函数并没有执行，在这之前等待异步还是也没有执行，为什么？
	BOOST_TEST(sz == 1);

	//异步等待时间未到时取消定时器，cancel如果有定时器被取消返回1，否则返回0，有异步等待定时器取消时会导致异步函数立即执行
	t.async_wait(on_timeout);
	ec = error::operation_aborted;
	sz = t.cancel(ec);
	BOOST_TEST(sz == 1);
	sz = t.cancel(ec);
	BOOST_TEST(sz == 0);

	//等待上面取消的异步函数调用
	t.expires_from_now(boost::posix_time::seconds(2));
	t.wait();
}

BOOST_AUTO_TEST_CASE(test_gregorian)
{
	using namespace boost::gregorian;
	date today = day_clock::local_day();
	std::cout << today << std::endl;
}

