#include "stdlib.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

std::stack<int> from_begin;
std::stack<int> from_end;
std::vector<int> ret_begin;
std::vector<int> ret_end;

int main(int argc, char *argv[]) {
    int n = 0;
    std::cin >> n;

    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    for (int i = 0, j = n - 1; i < n , j >= 0; ++i, --j) {
        ret_begin.push_back(from_begin.size());
        ret_end.push_back(from_end.size());
        while (!from_begin.empty() && from_begin.top() <= vec[i])
            from_begin.pop();
        while (!from_end.empty() && from_end.top() <= vec[j])
            from_end.pop();
        from_begin.push(vec[i]);
        from_end.push(vec[j]);
    }
    std::reverse(ret_end.begin(), ret_end.end());

    for (int i = 0; i < n; i++) {
        std::cout << ret_begin[i] + ret_end[i] + 1 << " ";
    }
    std::cout << std::endl;

    return 0;
}