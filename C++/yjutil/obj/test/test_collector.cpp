#include <gtest/gtest.h>
#include <fstream>
#include <boost/filesystem.hpp>

#include "yjcollector.h"
#include "yjcollector_mgr.h"
#include "yjcollector_policy.h"

using namespace yjutil;
using namespace boost::filesystem;

TEST(TestYjUtil, test_yjcollector_policy) {
    std::string path("/tmp/test_yjcollector_policy");
    CopyPolicyImpl copyPolicyImpl;
    ASSERT_FALSE(copyPolicyImpl.copy(path, "/tmp_no/", ""));
    
    ASSERT_FALSE(exists(path));
    ASSERT_FALSE(copyPolicyImpl.copy(path, "/tmp/", "/tmp/tmp/"));

    std::ofstream of(path);
    of << "test";
    of.close();

    ASSERT_TRUE(exists(path));
    ASSERT_TRUE(copyPolicyImpl.copy(path, "/tmp/", "/tmp/tmp/"));
    ASSERT_TRUE(exists("/tmp/tmp/test_yjcollector_policy"));

    ASSERT_TRUE(boost::filesystem::remove(path));
    ASSERT_TRUE(boost::filesystem::remove("/tmp/tmp/test_yjcollector_policy"));
}

TEST(TestYjUtil, test_yjcollector) {

    yjutil::FileCollector collector("./", "obj/");
    collector.doCollect();
}
