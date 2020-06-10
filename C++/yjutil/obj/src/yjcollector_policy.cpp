#include "yjcollector_policy.h"

#include <boost/filesystem.hpp>
#include <fstream>
#include <stdlib.h>
#include <string>

namespace yjutil {
CopyPolicy::CopyPolicy(CopyPolicyImpl *impl, RenamePolicy *renamePolicy,
                       const std::string &srcDir, const std::string &destDir)
    : m_impl(impl), m_renamePolicy(renamePolicy), m_srcDir(srcDir),
      m_destDir(destDir) {}

CopyPolicy::~CopyPolicy() {}

bool CopyPolicy::copy(const std::string &src) {
    return m_impl->copy(src, m_srcDir, m_destDir, m_renamePolicy);
}

FilterPolicy::FilterPolicy(FilterPolicyImpl *impl) : m_impl(impl) {}

FilterPolicy::~FilterPolicy() {}

bool FilterPolicy::filter(const std::string &file) {
    return m_impl->filter(file);
}

CopyPolicyImpl::CopyPolicyImpl() {}

CopyPolicyImpl::~CopyPolicyImpl() {}

bool CopyPolicyImpl::copy(const std::string &src, const std::string &srcDir,
                          const std::string &destDir,
                          RenamePolicySp renamePolicy) {
    if (src.find(srcDir) != 0) {
        return false;
    }
    std::string relativePath = src.substr(srcDir.size(), src.size());
    if (renamePolicy) {
        relativePath = renamePolicy->rename(relativePath);
    }

    std::string destFile = destDir + relativePath;
    boost::filesystem::path path(destFile.substr(0, destFile.find_last_of("/")));
    boost::filesystem::create_directories(path);

    DEBUG_PRINT("copy: %s -> %s", src.c_str(), destFile.c_str());

    std::ifstream ifs(src, std::ios::binary);
    std::ofstream ofs(destFile, std::ios::binary);
    if (!ifs || !ofs) {
        return false;
    }
    ofs << ifs.rdbuf();
    return true;
}

FilterPolicyImpl::FilterPolicyImpl() {}

FilterPolicyImpl::~FilterPolicyImpl() {}

bool FilterPolicyImpl::filter(const std::string &file) { return false; }

std::string RenamePolicySame::rename(const std::string &src) {
    return src;
}

} // namespace yjutil
