#include "stdlib.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

// (b, e]
inline int find_from_begin(std::vector<int> &vec, int b, int e) {
    if (b == e)
        return 0;
    int max = 0;
    int cnt = 0;
    for (int i = b + 1; i <= e; ++i) {
        if (vec[i] > max) {
            max = vec[i];
            ++cnt;
        }
    }
    return cnt;
}

// [b, e)
inline int find_from_end(std::vector<int> &vec, int b, int e) {
    if (b == e)
        return 0;
    int max = 0;
    int cnt = 0;
    for (int i = e - 1; i >= b; --i) {
        if (vec[i] > max) {
            max = vec[i];
            ++cnt;
        }
    }
    return cnt;
}

int get_result(std::vector<int> &vec, std::vector<int> &result) {
    std::stack<int> from_begin;
    std::stack<int> from_end;
    std::vector<int> ret_begin;
    std::vector<int> ret_end;
    for (size_t i = 0; i < vec.size(); i++) {
        ret_begin.push_back(from_begin.size());
        while (!from_begin.empty() && from_begin.top() < vec[i])
            from_begin.pop();
        from_begin.push(vec[i]);
    }
    for (size_t i = vec.size() - 1; i >= 0; i--) {
        ret_end.push_back(from_end.size());
        while (!from_end.empty() && from_end.top() < vec[i])
            from_end.pop();
        from_end.push(vec[i]);
    }
    std::reverse(ret_end.begin(), ret_end.end());
    for (size_t i = 0; i < vec.size(); i++) {
        result[i] = ret_begin[i] + ret_end[i] + 1;
    }
}

int main(int argc, char *argv[]) {
    int n = 0;
    scanf("%d", &n);
    // n = 100000;

    std::vector<int> vec(n);
    int high = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &high);
        vec[i] = high;
    }

    std::vector<int> result(n);

    get_result(vec, result);

    for (auto &&i : result) {
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}