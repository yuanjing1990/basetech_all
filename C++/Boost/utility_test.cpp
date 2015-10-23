#include <boost/utility.hpp>
#include <iostream>
#include <cstdlib>
class base_class1
{
public:
    base_class1(int i):_member(i){
        std::cout << "base_class1::base_class1()\n";
    }
public:
    int _member;
};

class base_class2
{
public:
    base_class2(base_class1& val):_member(val._member){
        std::cout << "base_class2::base_class2(base_class1&)\n";
    }
public:
    int _member;
};

class user_class:private boost::base_from_member<base_class1>,public base_class2
{
    typedef boost::base_from_member<base_class1> _base;
public:
    user_class():_base(30),base_class2(_base::member){
        std::cout << "user_class::user_class()\n";
    }
public:
};
void test_base_from_member_class()
{
    user_class uc;
    std::cout << "member=" << uc._member << std::endl;
}
class Undefined;
void test_checked_delete()
{
    Undefined* p1 = NULL;
    //boost::checked_delete(p1);
    //boost::checked_deleter<Undefined> t;
    //t(p1);
    user_class* p2 = NULL;
    boost::checked_delete(p2);
    boost::checked_deleter<user_class> t2;
    t2(p2);

    Undefined* _tmp1 = NULL;
    //boost::checked_array_delete(_tmp1);
    //boost::checked_array_deleter<Undefined> _tmp2;
    //_tmp2(_tmp1);

    user_class* t_array = new user_class[3];
    //boost::checked_array_delete(t_array);
    boost::checked_array_deleter<user_class> t3;
    t3(t_array);
}

class A : public boost::noncopyable
{
    public:
        A(){}
};
void test_noncopyable_class()
{
    A a,b;
    //a = b;
}

void test_next_prior_func()
{
    int* p = new int[10];
    for(int i = 0; i < 10; ++i)
        p[i] = std::rand()%10;
    for(int i = 0; i < 10; ++i)
        std::cout << p[i] << ",";
    std::cout.write("\n",2);
    int* tmp = p;
    std::cout << "boost::next(p):";
    for(int i = 0; i < 10; ++i)
    {
        std::cout << *tmp << ",";
        tmp = boost::next(tmp);
    }
    std::cout.write("\n",2);
    std::cout << "boost::next(p,i):";
    for(int i = 0; i < 10; ++i)
    {
        std::cout << *boost::next(p,i) << ",";
    }
    std::cout.write("\n",2);
    tmp = &p[9];
    std::cout << "boost::prior(p):";
    for(int i = 0; i < 10; ++i)
    {
        std::cout << *tmp << ",";
        tmp = boost::prior(tmp);
    }
    std::cout.write("\n",2);
    tmp = &p[9];
    std::cout << "boost::prior(p,i):";
    for(int i = 0; i < 10; ++i)
    {
        std::cout << *boost::prior(tmp,i) << ",";
    }
    std::cout.write("\n",2);
}
void test_addressof_func()
{
    int i = 0;
    std::cout << boost::addressof(i) << std::endl;
}

int main(int argc,char* argv[])
{
    test_base_from_member_class();
    test_checked_delete();
    test_noncopyable_class();
    test_next_prior_func();
    test_addressof_func();
    return 0;
}
