#include <boost/format.hpp>
#include <iostream>
int main(int argc, char *argv[]) {
    std::cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" %
                     40.23 % 50
              << std::endl;
    boost::format ft("%d%, %d%");
    ft % "hello" % "world";
    std::cout << ft.str() << std::endl;
    std::cout << boost::str(ft) << std::endl;
    return 0;
}
