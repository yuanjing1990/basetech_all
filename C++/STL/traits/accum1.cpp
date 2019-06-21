#include "accum1.hpp"
#include "multpolicy1.hpp"
#include <iostream>
int main() {
    int num[] = {1, 2, 3, 4, 5};
    // 因为初始化的值为零，所以相乘求和的结果为0
    std::cout << "the average value of the inter values is "
              << accum(&num[0], &num[5]) / 5 << '\n';
    char name[] = "templates";
    int length = sizeof(name) - 1;
    std::cout << "the average value of the characters in \"" << name << "\" is "
              << accum(&name[0], &name[length]) / length << '\n';
}