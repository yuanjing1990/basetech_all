#include <dlfcn.h>
#include <vector>
#include <gtest/gtest.h>

#include "yjdef.h"
#include "yjlog.h"
#include "yjalgorithm.h"

void test_yjdef();
void test_yjlog();
void test_ylalg();

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestYjUtil, test_yjdef) {
	int* a = new int;
	SAFE_DELETE(a);
	ASSERT_TRUE(a == NULL);

	int i = 1000 * 1000 * 1000;
	TICK_BEGIN;
	while (i > 0) {
		--i;
	}
	TICK_END;

	TICK_BEGIN_PRINT;
	i = 1000 * 1000 * 1000;
	while (i > 0) {
		--i;
	}
	TICK_END_PRINT;

	DEBUG_PRINT("test_yjdef");
}

TEST(TestYjUtil, test_yjlog) {
	std::vector<int> vec = {1,3,5,8,2,9,7,6,4};
	yjutil::print(vec);
}

TEST(TestYjUtil, test_ylalg) {
	std::vector<int> vec = {1,3,5,8,2,9,7,6,4};
	const int i = 7;
	// std::vector<int>::iterator it = yjutil::seq_search(vec, i);
	DEBUG_PRINT("%d",i);
}