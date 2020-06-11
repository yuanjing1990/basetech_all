#ifndef YJCOLLECTOR_POLICY_H_
#define YJCOLLECTOR_POLICY_H_

#include "yjutil.h"
#include <boost/shared_ptr.hpp>

namespace yjutil {

class CopyPolicyImpl;
class FilterPolicyImpl;
class RenamePolicy;
typedef boost::shared_ptr<CopyPolicyImpl> CopyPolicyImplSp;
typedef boost::shared_ptr<FilterPolicyImpl> FilterPolicyImplSp;
typedef boost::shared_ptr<RenamePolicy> RenamePolicySp;

class RenamePolicy {
  public:
    virtual ~RenamePolicy() {}
    virtual std::string rename(const std::string &src) = 0;
};

class CopyPolicy {
  private:
    CopyPolicyImplSp m_impl;
    RenamePolicySp m_renamePolicy;
    std::string m_srcDir;
    std::string m_destDir;

  public:
    CopyPolicy(CopyPolicyImpl *impl, RenamePolicy *renamePolicy,
               const std::string &srcDir, const std::string &destDir);
    ~CopyPolicy();
    bool copy(const std::string &src);
};

class FilterPolicy {
  private:
    FilterPolicyImplSp m_impl;

  public:
    FilterPolicy(FilterPolicyImpl *impl);
    ~FilterPolicy();
    bool filter(const std::string &file);
};

class CopyPolicyImpl {
  public:
    CopyPolicyImpl();
    virtual ~CopyPolicyImpl();
    virtual bool copy(const std::string &src, const std::string &srcDir,
                      const std::string &destDir,
                      RenamePolicySp renamePolicy = nullptr);
};

class FilterPolicyImpl {
  public:
    FilterPolicyImpl();
    virtual ~FilterPolicyImpl();
    virtual bool filter(const std::string &file);
};

class RenamePolicySame : public RenamePolicy {
  public:
    virtual ~RenamePolicySame() {}
    virtual std::string rename(const std::string &src);
};

} // namespace yjutil

#endif