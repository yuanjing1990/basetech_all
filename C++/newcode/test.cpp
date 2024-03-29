#include <algorithm>
#include <condition_variable>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <numeric>
#include <thread>
#include <unistd.h>
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
            result.push_back(std::accumulate(
                grade + first - 1, grade + second, 0,
                std::ptr_fun<const int &, const int &, const int &>(
                    std::max<int>)));
        }
    }
    std::copy(result.begin(), result.end(),
              std::ostream_iterator<int>(std::cout, "\n"));
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

void testThread() {
    std::vector<std::thread::id> product;
    std::mutex mtx;
    std::condition_variable cv;
    auto consumer_thread = [&mtx, &cv, &product]() {
        try {
            int cnt = 0;
            while (cnt < 10) {
                std::unique_lock<std::mutex> lck(mtx);
                if (!product.empty()) {
                    product.pop_back();
                    std::cout << std::this_thread::get_id()
                              << " consumer one:" << product.size()
                              << std::endl;
                    ++cnt;
                    cv.notify_all();
                } else {
                    cv.wait(lck);
                }
            }
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    };
    auto productor_thread = [&mtx, &cv, &product]() {
        try {
            static int cnt = 0;
            while (cnt < 30) {
                std::unique_lock<std::mutex> lck(mtx);
                if (product.size() < 10) {
                    product.push_back(std::this_thread::get_id());
                    std::cout << std::this_thread::get_id()
                              << " produce one:" << product.size() << std::endl;
                    ++cnt;
                    cv.notify_all();
                } else {
                    cv.wait(lck);
                }
            }
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    };
    std::thread t1(consumer_thread), t2(consumer_thread), t3(consumer_thread);
    std::thread t4(productor_thread), t5(productor_thread);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

int *testStatic() {
    static int a;
    std::cout << a << std::endl;
    return &a;
}

struct ObjB;
struct ObjA {
    std::shared_ptr<ObjB> _b;
    ~ObjA() { std::cout << "destruct OjbA" << std::endl; }
};
struct ObjB {
    std::shared_ptr<ObjA> _a;
    ~ObjB() { std::cout << "destruct OjbB" << std::endl; }
};

void testSharePtr() {
    std::shared_ptr<ObjA> a(new ObjA);
    std::shared_ptr<ObjB> b(new ObjB);
    // a->_b = b;
    // b->_a = a;
}

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        for (int i = 0; i < nums.size(); ++i) {
            int x = target - nums[i];
            auto pos = std::find(nums.begin(), nums.end(), x);
            if (pos != nums.end() && pos - nums.begin() != i) {
                return vector<int>{i, pos};
            }
        }
    }
};

int main(int argc, char *argv[]) {
    testSharePtr();
    return 0;
}
