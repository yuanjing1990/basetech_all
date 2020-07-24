#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <vector>

void huawei_2016_1() {
    int m = 0, n = 0;
    std::cin >> n >> m;

    int grade[n] = {0};
    for (size_t i = 0; i < n; i++) {
        std::cin >> grade[i];
    }

    char op;
    int first = 0, second = 0;

    std::vector<int> result;
    for (size_t i = 0; i < m; i++) {
        std::cin >> op >> first >> second;
        if (op == 'U') {
            grade[first - 1] = second;
        } else if (op == 'Q') {
            if (first > second)
                std::swap(first, second);
            result.push_back(std::accumulate(grade + first - 1, grade + second, 0, std::ptr_fun<const int &, const int &, const int &>(std::max<int>)));
        }
    }
    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, "\n"));
}

void huawei_2016_2() {
    std::ifstream ifs("file.txt");
    if (!ifs.is_open())
        return;

    while (!ifs.eof()) {
        std::string filename;
        int linenum;
        ifs >> filename >> linenum;
        if (!filename.empty() && linenum > 0) {
        }
    }

    ifs.close();
}

int solve(std::string s) {
    // write code here
    std::string max;
    int start = 0, end = 1;
    try {
        while (end < s.length()) {
            char cur = s.at(end);
            if (!std::isdigit(cur) && (cur < 'A' || cur > 'F')) {
                max = std::max(max, s.substr(start, end - start));
                start = end + 1;
            }
            ++end;
        }
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << max;
}

int main(int argc, char *argv[]) {
    solve("012345BZ16");
    return 0;
}
