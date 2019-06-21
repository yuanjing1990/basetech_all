#include "namedtmp1.hpp"
int main(int argc, char *argv[]) {
    BreadSlicer<> ac;
    ac.print();
    std::cout << "======================================\n";
    BreadSlicer<Policy3_is<CustomPolicy1>> bc;
    bc.print();
    std::cout << "======================================\n";
    BreadSlicer<Policy1_is<CustomPolicy1>, Policy3_is<CustomPolicy2>> tc;
    tc.print();
    std::cout << "======================================\n";
}