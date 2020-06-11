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
