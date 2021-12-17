// #include "bitree.h"
// #include "nested.h"
// #include "stack.h"
#include <future>
#include <iostream>
// using namespace yq;
void test();
int main(int argc, char *argv[])
{
    // 1 bitree.h
    // yq::BiTree<int> bt;
    // int a[10] = {1,3,8,5,4,2,6,9,7,10};
    // bt.CreateBiTree(a,10);
    // bt.PrintTree();

    // 2 stack.h
    // try{
    // 	Stack<int> s;
    // 	s.push(10);
    // 	std::cout << s.top() << std::endl;
    // 	s.pop();
    // 	s.pop();
    // 	std::cout << "After Exception!" << std::endl;
    // }catch(std::out_of_range e)
    // {
    // 	std::cerr << e.what() << std::endl;
    // }

    // 3 nested.h
    // Nest<std::vector<int>> n;
    // std::bitset<5> bs;
    // bs.set(4);
    test();
    // PrintBitset(bs);
}

using namespace std;
shared_future<int> g_p;
void Customer()
{
    while (true)
    {
        if (!g_p.valid()) continue;
        g_p.wait();
        cout << "Product " << endl;
    }
}
#include <queue>
void Producer()
{
    std::queue<int> product;
    while (!g_p.valid())
    {
        this_thread::sleep_for(std::chrono::seconds(1));
        product.push(rand());
        promise<int> pro;
        if (!g_p.valid())
        {
            g_p = pro.get_future();
        }
    }
}


#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
        vector<int> ret(s.size(), 1);
        for (int i = 1; i < s.size(); i++)
        {
            if (i - ret[i - 1] > 0 && s[i - ret[i - 1] - 1] == s[i]) {
                ret[i] = ret[i - 1] + 2;
            } else if (ret[i - 1] > 1) {
                ret[i] = findMaxStartWithLast(s.substr(i - ret[i - 1], ret[i - 1] + 1));
            } else if (i - 2 >= 0 && s[i - 2] == s[i]) {
                ret[i] = 3;
            } else if (s[i - 1] == s[i]) {
                ret[i] = 2;
            }
        }
        auto it = max_element(ret.begin(), ret.end());
        int pos = distance(ret.begin(), it);
        return s.substr(pos - *it + 1, *it);
    }
    
    bool isPalindrome(string s) {
        int i = 0;
        while (i * 2 < s.size()) {
            if (s[i] != s[s.size() - i - 1]) {
                return false;
            }
            ++i;
        }
        return true;
    }

    int findMaxStartWithLast(string s) {
        int len = s.size();
        while (len > 1) {
            if (isPalindrome(s.substr(s.size() - len, len))) return len;
            --len;
        }
        return len;
    }
};

void test()
{
    Solution sol;
    cout << sol.longestPalindrome("babad") << endl;
}