#include <algorithm>
#include <dirent.h>
#include <functional>
#include <stdio.h>
#include <string.h>

#include "yjcollector.h"
#include "yjcollector_policy.h"
#include "yjutil.h"

namespace yjutil {

Collector::Collector(const std::string &strSrcPath,
                     const std::string &strDestPath,
                     CopyPolicyImpl *copyImpl,
                     FilterPolicyImpl *matchImpl)
    : m_srcDir(strSrcPath), m_destDir(strDestPath), m_copyPolicy(copyImpl,strSrcPath, strDestPath),
      m_filterPolicy(matchImpl){};

Collector::~Collector() {}

bool Collector::isDirExist(const std::string &dir) {
    bool ret = false;
    DIR *pDir = opendir(dir.c_str());
    if (pDir) {
        closedir(pDir);
        ret = true;
    }
    return ret;
}

bool Collector::getFileVec(const std::string &dir,
                           std::vector<std::string> &fileVec) {
    if (!isDirExist(dir)) {
        return false;
    }
    return getFileVecInner(dir, dir, fileVec);
}

bool Collector::getFileVecInner(const std::string &dirRoot,
                                const std::string &curDir,
                                std::vector<std::string> &fileVec) {
    struct dirent *p_entry = NULL;
    DIR *pDir = opendir(curDir.c_str());
    if (!pDir) {
        return false;
    }

    while (NULL != (p_entry = readdir(pDir))) {
        std::string curFilePath;
        curFilePath.append(curDir).append("/").append(p_entry->d_name);
        if (p_entry->d_type == DT_DIR) {
            if (strcmp(".", p_entry->d_name) == 0 ||
                strcmp("..", p_entry->d_name) == 0)
                continue;
            getFileVecInner(dirRoot, curFilePath, fileVec);
        } else {
            fileVec.push_back(curFilePath);
        }
    }
    closedir(pDir);
    sort(fileVec.begin(), fileVec.end());
    return true;
}

bool Collector::doCollect() {
    std::vector<std::string> srcFileVec;
    getFileVec(m_srcDir, srcFileVec);

    std::for_each(srcFileVec.begin(), srcFileVec.end(),
                  std::bind1st(std::mem_fun(&Collector::collectFile), this));
    return true;
}

bool Collector::collectFile(std::string file) {
    if (!m_filterPolicy.filter(file)) {
        return false;
    }
    m_copyPolicy.copy(file);
}

} // namespace yjutil