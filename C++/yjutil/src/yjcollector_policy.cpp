#include "yjcollector_policy.h"

namespace yjutil {
CopyPolicy::CopyPolicy(CopyPolicyImpl *impl, const std::string &srcDir,
                       const std::string &destDir)
    : m_impl(impl), m_srcDir(srcDir), m_destDir(destDir) {}
CopyPolicy::~CopyPolicy() { SAFE_DELETE(m_impl); }
bool CopyPolicy::copy(const std::string &src) {
    return m_impl->copy(src, m_srcDir, m_destDir);
}

FilterPolicy::FilterPolicy(FilterPolicyImpl *impl) : m_impl(impl) {}
FilterPolicy::~FilterPolicy() { SAFE_DELETE(m_impl); }
bool FilterPolicy::filter(const std::string &file) {
    return m_impl->filter(file);
}

CopyPolicyImpl::CopyPolicyImpl() {}
CopyPolicyImpl::~CopyPolicyImpl() {}
bool CopyPolicyImpl::copy(const std::string &src, const std::string &srcDir,
                          const std::string &destDir) {
    return true;
}

FilterPolicyImpl::FilterPolicyImpl() {}
FilterPolicyImpl::~FilterPolicyImpl() {}
bool FilterPolicyImpl::filter(const std::string &file) { return true; }

} // namespace yjutil
