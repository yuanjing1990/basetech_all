#include <dlfcn.h>
#include <vector>
#include <gtest/gtest.h>

#include "yjutil.h"
#include "yjcollector.h"

void test_yjdef();
void test_yjlog();
void test_ylalg();

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

// TEST(TestYjUtil, test_yjdef) {
// 	int* a = new int;
// 	SAFE_DELETE(a);
// 	ASSERT_TRUE(a == NULL);

// 	int i = 1000 * 1000 * 1000;
// 	TICK_BEGIN;
// 	while (i > 0) {
// 		--i;
// 	}
// 	TICK_END;

// 	TICK_BEGIN_PRINT;
// 	i = 1000 * 1000 * 1000;
// 	while (i > 0) {
// 		--i;
// 	}
// 	TICK_END_PRINT;

// 	DEBUG_PRINT("test_yjdef");
// }

// TEST(TestYjUtil, test_yjlog) {
// 	std::vector<int> vec = {1, 3, 5, 8, 2, 9, 7, 6, 4};
// 	yjutil::print(vec);
// }

// TEST(TestYjUtil, test_yjalg) {
// 	std::vector<int> vec = {1, 3, 5, 8, 2, 9, 7, 6, 4};
// 	const int i = 7;
// 	std::vector<int>::iterator it = yjutil::seq_search(vec, i);
// 	ASSERT_EQ(i, *it);
// }

// TEST(TestYjUtil, test_yjbitree) {
// 	std::vector<int> vec = {1, 3, 5, 8, 2, 9, 7, 6, 4};
// 	yjutil::_bitree<int>* tree = yjutil::_bitree<int>::CreateTree(vec, 8, 0);
// 	std::cout << *tree << std::endl;
// }

// int add(int &i) {
// 	++i;
// }

// TEST(TestYjUtil, test_yj) {
// 	int i = 1;
// 	typeof(add(i)) x = 0;
// 	ASSERT_EQ(i, 1);
// }

class TestRenamePolicy : public yjutil::RenamePolicyImpl {
public:
	virtual std::string rename(const std::string& file) {
		std::string retStr = file;
		size_t pos = retStr.find('/', 1);
		while(pos != std::string::npos) {
			retStr.replace(pos, 1, "_");
			pos = retStr.find('/', pos);
		}
		return retStr;
	}
};

class TestMatchPolicy : public yjutil::MatchPolicyImpl {
public:
	virtual bool match(const std::string& file) {
		return true;
	}
};

class TestCopyPolicy : public yjutil::CopyPolicyImpl {
public:
	virtual bool copy(const std::string& src, const std::string& dest) {
		return true;
	}
};

TEST(TestYjUtil, test_yjcollector) {
	yjutil::Collector collector("/usr/local/lib", "/tmp/test_collector", new TestRenamePolicy);
	collector.doCollect();
}
