#ifndef YJCOLLECTOR_POLICY_H_
#define YJCOLLECTOR_POLICY_H_

#include "yjcollector_policy_impl.h"
#include "yjutil.h"

namespace yjutil {

class CopyPolicyImpl;
class FilterPolicyImpl;

class CopyPolicy {
  private:
    CopyPolicyImpl *m_impl;
    std::string m_srcDir;
    std::string m_destDir;

  public:
    CopyPolicy(CopyPolicyImpl *impl, const std::string& srcDir, const std::string& destDir);
    ~CopyPolicy();
    bool copy(const std::string &src);
};


class FilterPolicy {
  private:
    FilterPolicyImpl *m_impl;

  public:
    FilterPolicy(FilterPolicyImpl *impl);
    ~FilterPolicy();
    bool filter(const std::string &file);
};

} // namespace yjutil

#endif