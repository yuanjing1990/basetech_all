#include <algorithm>
#include <boost/filesystem.hpp>
#include <dirent.h>
#include <functional>
#include <stdio.h>
#include <string.h>

#include "yjcollector.h"
#include "yjcollector_policy.h"
#include "yjutil.h"

namespace yjutil {

FileCollector::FileCollector(const std::string &strSrcPath,
                             const std::string &strDestPath,
                             CopyPolicyImpl *copyImpl,
                             FilterPolicyImpl *filterImpl,
                             RenamePolicyImpl *renameImpl)
    : m_srcDir(strSrcPath), m_destDir(strDestPath),
      m_copyPolicy(copyImpl, renameImpl, strSrcPath, strDestPath),
      m_filterPolicy(filterImpl){};

FileCollector::~FileCollector() {}

bool FileCollector::isDirExist(const std::string &dir) {
    boost::filesystem::path path(dir);
    if (boost::filesystem::is_directory(path)) {
        return true;
    }
    return false;
}

bool FileCollector::getFileVec(const std::string &dir,
                               std::vector<std::string> &fileVec) {
    if (!isDirExist(dir)) {
        return false;
    }
    return getFileVecInner(dir, dir, fileVec);
}

bool FileCollector::getFileVecInner(const std::string &dirRoot,
                                    const std::string &curDir,
                                    std::vector<std::string> &fileVec) {
    boost::filesystem::directory_iterator cur(curDir);
    boost::filesystem::directory_iterator end;

    while (cur != end) {
        boost::filesystem::path path(*cur);
        if (boost::filesystem::is_directory(path)) {
            getFileVecInner(dirRoot, path.string(), fileVec);
        } else if (boost::filesystem::is_regular(path)) {
            fileVec.push_back(path.string());
        }
        ++cur;
    }
    sort(fileVec.begin(), fileVec.end());
    return true;
}

bool FileCollector::doCollect() {
    std::vector<std::string> srcFileVec;
    if (!getFileVec(m_srcDir, srcFileVec) || !isDirExist(m_destDir)) {
        return false;
    }

    std::for_each(srcFileVec.begin(), srcFileVec.end(),
                  std::bind1st(std::mem_fun(&FileCollector::collectFile), this));
    return true;
}

bool FileCollector::collectFile(std::string file) {
    if (m_filterPolicy.filter(file)) {
        return false;
    }
    m_copyPolicy.copy(file);
    return true;
}

} // namespace yjutil