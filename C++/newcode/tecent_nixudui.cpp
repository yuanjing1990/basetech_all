#include "stdlib.h"
#include <algorithm>
#include <math.h>
#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

int main(int argc, char *argv[]) {
    int n = 0;
    std::cin >> n;

    int num = std::pow(2, n);
    std::cout << "num:" << num << std::endl;
    std::vector<int> vec(num);
    for (int i = 0; i < num; ++i) {
        std::cin >> vec[i];
    }

    int m = 0;
    std::cin >> m;
    std::vector<int> mVec(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> mVec[i];
    }

    for (int i = 0; i < m; ++i) {
        int groupNum = std::pow(2, mVec[i]);
        for (int i = 0; i <= num - groupNum; i = i + groupNum)
            std::reverse(vec.begin() + i, vec.begin() + i + groupNum);

        std::stack<int> front;
        std::vector<int> ret;
        for (int i = 0; i < num; ++i) {
            ret.push_back(front.size());
            while(!front.empty() && front.top() <= vec[i])
                front.pop();
            front.push(vec[i]);
        }
        // std::cout << std::endl;
    }

    return 0;
}