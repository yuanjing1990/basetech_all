#ifndef YJCOLLECTOR_POLICY_IMPL_H_
#define YJCOLLECTOR_POLICY_IMPL_H_

#include <string>

namespace yjutil {

class CopyPolicyImpl {
  public:
    CopyPolicyImpl();
    virtual ~CopyPolicyImpl();
    virtual bool copy(const std::string &src, const std::string &srcDir,
                      const std::string &destDir);
};

class FilterPolicyImpl {
  public:
    FilterPolicyImpl();
    virtual ~FilterPolicyImpl();
    virtual bool filter(const std::string &file);
};

} // namespace yjutil

#endif
