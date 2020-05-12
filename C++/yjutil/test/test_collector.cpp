#include <gtest/gtest.h>
#include <fstream>

#include "yjcollector.h"

class TestFilterPolicy : public yjutil::FilterPolicyImpl {
  public:
    virtual bool filter(const std::string &file) { return true; }
};

class TestCopyPolicy : public yjutil::CopyPolicyImpl {
  public:
    virtual bool copy(const std::string &src, const std::string &srcDir,
                      const std::string &destDir) {
        std::string destFile = src;
        destFile.replace(destFile.begin(), destFile.begin() + srcDir.size(),
                         destDir);

        FILE* pipeFile = popen("md5sum " + src, "r");
        if (!pipeFile) {
            return false;
        }

        char temp[1024] = {0};
        while (fgets(temp, sizeof(temp), pipeFile) != NULL) {
            str->add(temp);
        }
        pclose(pipeFile);

        DEBUG_PRINT("copy: %s -> %s", src.c_str(), destFile.c_str());

        char buff[1024] = {0};
        std::ifstream ifs(src, std::ios::binary);
        std::ofstream ofs(destFile, std::ios::binary);

        while (ifs && !ifs.eof()) {
            ifs.read(buff, sizeof(buff));
            ofs.write(buff, ifs.gcount());
        }
        ifs.close();
        ofs.close();

        return true;
    }
};

TEST(TestYjUtil, test_yjcollector) {
    yjutil::Collector collector(".", "obj", new TestCopyPolicy);
    collector.doCollect();
}
