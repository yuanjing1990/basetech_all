#include <algorithm>
#include <iostream>
#include <iterator>
#define H_W 3.14 // Test
template <class T> inline T &max(T &a, T &b) { return a > b ? a : b; }
class Test {
  public:
    static const char *const count;

  private:
    //使用enum定义整型常量
    enum { MAX_COUNT = 5 };

  public:
    int m_mem[MAX_COUNT] = {0};

  public:
    void print() {
        std::copy(m_mem, m_mem + MAX_COUNT,
                  std::ostream_iterator<int>(std::cout, "\t"));
        std::cout << count;
        std::cout << std::endl;
    }
};
const char *const Test::count = "count";
int main(int argc, char *argv[]) {
    char a, b;
    std::cin >> a >> b;
    std::cout << "Max:" << max(a, b) << std::endl;
    Test t;
    t.print();
    std::cout << t.count << std::endl;
    std::cout << H_W << std::endl;
    return 0;
}