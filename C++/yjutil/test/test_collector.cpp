#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <gtest/gtest.h>
#include <queue>
#include <stack>

#include "yjcollector.h"
#include "yjcollector_mgr.h"
#include "yjcollector_policy.h"

using namespace yjutil;
using namespace boost::filesystem;

TEST(TestYjUtil, test_yjcollector_policy) {
    std::string path("/tmp/test_yjcollector_policy");
    std::string destFile("/tmp/tmp/test_yjcollector_policy");

    CopyPolicyImpl copyPolicyImpl;
    ASSERT_FALSE(copyPolicyImpl.copy(path, "/tmp_no/", "", RenamePolicy(nullptr)));

    ASSERT_FALSE(exists(path));
    ASSERT_FALSE(copyPolicyImpl.copy(path, "/tmp/", "/tmp/tmp/", RenamePolicy(nullptr)));

    CopyPolicy copyPolicy(new CopyPolicyImpl, new RenamePolicyImpl, "/tmp/", "/tmp/tmp/");
    ASSERT_FALSE(copyPolicy.copy(path));

    std::ofstream of(path);
    of << "test";
    of.close();

    ASSERT_TRUE(exists(path));
    ASSERT_TRUE(copyPolicyImpl.copy(path, "/tmp/", "/tmp/tmp/", RenamePolicy(nullptr)));
    ASSERT_TRUE(exists(destFile));
    ASSERT_TRUE(boost::filesystem::remove(destFile));
    ASSERT_TRUE(copyPolicy.copy(path));

    ASSERT_TRUE(boost::filesystem::remove(path));
    ASSERT_TRUE(boost::filesystem::remove(destFile));
}

TEST(TestYjUtil, test_yjcollector) {

    yjutil::FileCollector collector("./", "obj/");
    collector.doCollect();
}

/*
输入第一行包含一个字符串s，代表压缩后的字符串。
S的长度<=1000;
S仅包含大写字母、[、]、|;
解压后的字符串长度不超过100000;
压缩递归层数不超过10层;
*/
TEST(TestYjUtil, test_mytest1) {

    std::string inStr;
    std::cin >> inStr;

    std::string lastMod;
    std::string unpackStr;
    std::stack<std::string> unpackStack;
    int pos = 0;
    for (int i = 0; i < inStr.length(); ++i) {
        if ((inStr.at(i) == '[' || inStr.at(i) == '|')) {
            // std::cout << inStr.substr(pos, i - pos) << std::endl;
            unpackStack.push(inStr.substr(pos, i - pos));
            pos = i + 1;
        } else if (inStr.at(i) == ']') {
            std::string mod = inStr.substr(pos, i - pos);
            if (mod.empty()) {
                lastMod = unpackStack.top();
                unpackStack.pop();
            } else {
                lastMod = mod;
            }

            int num = 0;

            while ((num = atoi(unpackStack.top().c_str())) == 0) {
                lastMod = unpackStack.top() + lastMod;
                unpackStack.pop();
            }
            while (num = atoi(unpackStack.top().c_str())) {
                unpackStack.pop();
                std::string buf;
                for (int j = 0; j < num; ++j) {
                    buf.append(lastMod);
                }
                lastMod = buf;
                // std::cout << "lastMod:" << lastMod << std::endl;
            }
            lastMod = unpackStack.top() + lastMod;
            // std::cout << "out lastMod:" << lastMod << std::endl;
            unpackStack.pop();
            unpackStack.push(lastMod);
            pos = i + 1;
        }
    }
    unpackStack.push(inStr.substr(pos, inStr.length() - pos));
    while (!unpackStack.empty()) {
        unpackStr = unpackStack.top() + unpackStr;
        unpackStack.pop();
    }

    std::cout << unpackStr << std::endl;
}

int find_max_from_begin(std::vector<int> &vec, int b, int e) {
    int max = vec.at(b);
    size_t i, index = b;
    for (i = b + 1; i <= e; i++) {
        if (vec.at(i) > max) {
            max = vec.at(i);
            index = i;
        }
    }
    return index;
}

int find_max_from_end(std::vector<int> &vec, int b, int e) {
    int max = vec.at(e);
    size_t i, index = e;
    for (i = e - 1; i >= b; i++) {
        if (vec.at(i) > max) {
            max = vec.at(i);
            index = i;
        }
    }
    return index;
}

int get_result(std::vector<int> &vec, std::vector<int> &result) {
    for (size_t i = 0; i < vec.size(); i++) {
        int r = vec.size() - 1;
        int cnt_after = 0;
        do {
            if (i + 1 >= vec.size() -1 )
                break;
            r = find_max_from_begin(vec, i, r) - 1;
            ++cnt_after;
        } while (r != i + 1);

        std::cout << "i=" << i << ":cnt_after=" << cnt_after << std::endl;

        int cnt_before = 0;
        r = 0;
        do {
            if (i <= 0 )
                break;
            r = find_max_from_end(vec, r, i) + 1;
            ++cnt_before;
        } while (r != i - 1);
        std::cout << "i=" << i << ":cnt_before=" << cnt_before << std::endl;

        result.push_back(cnt_after + cnt_before + 1);
        break;
    }
}

TEST(TestYjUtil, test_mytest2) {

    std::vector<int> vec;
    int n = 0;
    std::cin >> n;
    int high = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> high;
        vec.push_back(high);
    }

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ","));
    std::cout << std::endl;

    std::vector<int> result;
    std::cout << find_max_from_begin(vec, 0, vec.size() - 1) << std::endl;
    get_result(vec, result);

    std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, ","));
}