#ifndef YJCOLLECTOR_H_
#define YJCOLLECTOR_H_

#include <string>
#include <vector>

namespace yjutil {
class Collector;
class RenamePolicy;
class RenamePolicyImpl;
class CopyPolicy;
class CopyPolicyImpl;
class MatchPolicy;
class MatchPolicyImpl;

class RenamePolicyImpl {
  public:
	RenamePolicyImpl();
	virtual ~RenamePolicyImpl();
	virtual std::string rename(const std::string& name) {
		return name;
	}
};

RenamePolicyImpl::RenamePolicyImpl() {
}

RenamePolicyImpl::~RenamePolicyImpl() {
}

class RenamePolicy {
  private:
	RenamePolicyImpl* m_impl;
  public:
	RenamePolicy(RenamePolicyImpl* impl);
	~RenamePolicy();
	std::string rename(const std::string& name);
};

class CopyPolicyImpl {
  public:
	CopyPolicyImpl();
	virtual ~CopyPolicyImpl();
	virtual bool copy(const std::string& src, const std::string& dest) {
		return true;
	}
};

CopyPolicyImpl::CopyPolicyImpl() {
}

CopyPolicyImpl::~CopyPolicyImpl() {
}


class CopyPolicy {
  private:
	CopyPolicyImpl* m_impl;
  public:
	CopyPolicy(CopyPolicyImpl* impl);
	~CopyPolicy();
	bool copy(const std::string& src, const std::string& dest);
};

class MatchPolicyImpl {
  public:
	MatchPolicyImpl();
	virtual ~MatchPolicyImpl();
	virtual bool match(const std::string& file) {
		return true;
	}
};

MatchPolicyImpl::MatchPolicyImpl() {
}

MatchPolicyImpl::~MatchPolicyImpl() {
}

class MatchPolicy {
  private:
	MatchPolicyImpl* m_impl;
  public:
	MatchPolicy(MatchPolicyImpl* impl);
	~MatchPolicy();
	bool match(const std::string& file);
};

class Collector {
  public:
	Collector(const std::string& strSrcPath, const std::string& strDestPath,
	          RenamePolicyImpl* renameImpl = new RenamePolicyImpl,
	          CopyPolicyImpl* copyImpl = new CopyPolicyImpl,
	          MatchPolicyImpl* matchImpl = new MatchPolicyImpl)
		: m_srcDir(strSrcPath), m_destDir(strDestPath),
		  m_renamePolicy(renameImpl), m_copyPolicy(copyImpl), m_matchPolicy(matchImpl) {};
	~Collector() {};
  public:
	bool doCollect();

  private:
	bool isDirExist(const std::string& dir);
	bool getFileVec(const std::string& dir, std::vector<std::string>& fileVec);
	bool getFileVecInner(const std::string& dirRoot, const std::string& curDir, std::vector<std::string>& fileVec);

  private:
	std::string  m_srcDir;
	std::string  m_destDir;
	RenamePolicy m_renamePolicy;
	CopyPolicy   m_copyPolicy;
	MatchPolicy  m_matchPolicy;
};

}  // namespace yjutil

#endif