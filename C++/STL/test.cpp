//#include "mystl/any.h"
#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iterator>
#include <iomanip>

#define BOOST_TEST_MODULE test_module
// 动态链接方式必须定义此宏，否则main函数未定义
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
using namespace boost::unit_test::framework;

#ifndef YJ_STL_VERSION
#define yj boost
#else
#endif

BOOST_AUTO_TEST_CASE(test_any)
{
        using boost::any;
        using boost::any_cast;
        using boost::bad_any_cast;
        using std::string;
        // any可以从任何类型直接构造，any的实际值可以通过any_cast<type>(any)获取得到
        any e1(3);
        any e2(4.5);
        BOOST_TEST(3 == any_cast<int>(e1));
        BOOST_TEST(4.5 == any_cast<double>(e2));

        // any可以直接从其他类型赋值拷贝
        e1 = "abc";
        BOOST_TEST(!strcmp("abc", any_cast<const char *>(e1)));
        e1 = string("abc");
        BOOST_TEST("abc" == any_cast<string>(e1));
        e1 = e2;
        BOOST_TEST(4.5 == any_cast<double>(e1));
        BOOST_TEST(4.5 == any_cast<double>(e2));

        any e3(e1);
        BOOST_TEST(any_cast<double>(e1) == any_cast<double>(e3));

        // any_cast到错误的类型会抛出 bad_any_cast异常
        BOOST_TEST_I_TRY
        {
                BOOST_TEST(any_cast<int>(e1) == 4.5);
        }
        BOOST_TEST_I_CATCH(bad_any_cast, e)
        {
                BOOST_TEST_MESSAGE(e.what());
        }

        // any不能直接比较
        // BOOST_TEST(e1 == e3);
}

// 演示和测试boost::asio的基本用法
BOOST_AUTO_TEST_CASE(test_asio)
{
        using namespace boost::asio;
        using boost::posix_time::seconds;
        using boost::system::error_code;

        io_service io;
        //deadline_timer是一个定时器，wait可以带一个参数接收定时器结果，wait是同步的
        //下面是构造时直接设置的超时时间，也可以使用expires_from_now成员函数设置超时时间
        deadline_timer t(io, seconds(2));
        error_code ec;
        //正常情况wait会阻塞2s，但是也可能会有其他线程取消定时器，ec返回定时器是正常超时（boost::asio::error::operation_success）还是被取消（boost::asio::error::operation_aborted）boost::asio::error::operation_success
        BOOST_TEST_INFO("等待定时器超时");
        t.wait(ec);
        BOOST_TEST_INFO("等待定时器超时完成");
        BOOST_TEST(!ec);

        auto on_timeout = [](const error_code &ec) -> void {
        };
        //expires_from_now可以重新设置超时时间，但是会取消正在等待定时器的异步处理函数，返回值表示被取消的异步处理函数的数量
        t.async_wait(on_timeout);
        size_t sz = t.expires_from_now(seconds(2), ec);
        BOOST_TEST_INFO("重新设置定时器，取消一个异步超时函数完成");
        BOOST_TEST(!ec);
        BOOST_TEST(sz == 1);

        t.async_wait(on_timeout);
        t.async_wait(on_timeout);
        sz =
            t.expires_from_now(seconds(2), ec); //这里取消定时异步函数并没有执行，在这之前等待异步还是也没有执行，为什么？async_wait是异步的函数，不会等待超时
        BOOST_TEST_INFO("重新设置定时器，取消二个异步超时函数完成");
        BOOST_TEST(sz == 2);

        //异步等待时间未到时取消定时器，cancel如果有定时器被取消返回1，否则返回0，有异步等待定时器取消时会导致异步函数立即执行
        t.async_wait(on_timeout);
        ec = error::operation_not_supported;
        sz = t.cancel(ec);
        BOOST_TEST_INFO("直接取消一个异步超时函数完成");
        BOOST_TEST(sz == 1);
        sz = t.cancel(ec);
        BOOST_TEST_INFO("再次取消异步超时函数完成");
        BOOST_TEST(sz == 0);

        //等待上面取消的异步函数调用
        t.expires_from_now(seconds(2));
        BOOST_TEST_INFO("等待定时器超时");
        t.wait();
        BOOST_TEST_INFO("等待定时器超时完成");
}

// 演示boost::gregorian用法
BOOST_AUTO_TEST_CASE(test_gregorian)
{
        using namespace boost::gregorian;
        date today = day_clock::local_day();
        std::cout << today << std::endl;
}
