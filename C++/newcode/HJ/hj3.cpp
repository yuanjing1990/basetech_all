#include <iostream>
#include <iterator>
#include <set>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<int> vec;
    vec.insert(vec.end(), std::istream_iterator<int>(std::cin), std::istream_iterator<int>());

    std::vector<int> vec_group;
    int num = 0;
    for (auto it = vec.begin(); it != vec.end(); it += num) {
        num = *it++;
        std::set<int> group(it, it + num);
        vec_group.insert(vec_group.end(), group.begin(), group.end());
    }
    std::copy(vec_group.begin(), vec_group.end(), std::ostream_iterator<int>(std::cout, "\n"));
    return 0;
}