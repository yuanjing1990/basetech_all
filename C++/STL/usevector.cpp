#include <iostream>
#include <vector>

using namespace std;
int main(int argc, char *argv[]) {
    vector<int> vec;
    vector<int>::allocator_type allocator = vec.get_allocator();
    return 0;
}