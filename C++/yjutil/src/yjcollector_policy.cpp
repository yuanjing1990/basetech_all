#include "yjcollector_policy.h"

#include <boost/filesystem.hpp>
#include <fstream>
#include <stdlib.h>
#include <string>

namespace yjutil {
CopyPolicy::CopyPolicy(CopyPolicyImpl *impl, const std::string &srcDir,
                       const std::string &destDir)
    : m_impl(impl), m_srcDir(srcDir), m_destDir(destDir) {}

CopyPolicy::~CopyPolicy() {}

bool CopyPolicy::copy(const std::string &src) {
  return m_impl->copy(src, m_srcDir, m_destDir, true);
}

FilterPolicy::FilterPolicy(FilterPolicyImpl *impl) : m_impl(impl) {}

FilterPolicy::~FilterPolicy() {}

bool FilterPolicy::filter(const std::string &file) {
  return m_impl->filter(file);
}

CopyPolicyImpl::CopyPolicyImpl() {}

CopyPolicyImpl::~CopyPolicyImpl() {}

bool CopyPolicyImpl::copy(const std::string &src, const std::string &srcDir,
                          const std::string &destDir, const bool &isRename) {
  if (src.find(srcDir) != 0) {
    return false;
  }
  std::string relativePath = src.substr(srcDir.size(), src.size());
  if(isRename) {
      std::vector<char> buf(relativePath.begin(), relativePath.end());
      std::replace(buf.begin(), buf.end(), '/', '_');
      relativePath.assign(buf.begin(), buf.end());
  }

  std::string destFile = destDir + relativePath;
  boost::filesystem::path path(destFile.substr(0, destFile.find_last_of("/")));
  boost::filesystem::create_directories(path);

  DEBUG_PRINT("copy: %s -> %s", src.c_str(), destFile.c_str());

  std::ifstream ifs(src, std::ios::binary);
  std::ofstream ofs(destFile, std::ios::binary);
  if(!ifs || !ofs) {
      return false;
  }
  ofs << ifs.rdbuf();
  return true;
}

FilterPolicyImpl::FilterPolicyImpl() {}

FilterPolicyImpl::~FilterPolicyImpl() {}

bool FilterPolicyImpl::filter(const std::string &file) { return false; }

} // namespace yjutil
