#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include "yjcollector.h"
#include "yjutil.h"

namespace yjutil {

MatchPolicy::MatchPolicy(MatchPolicyImpl* impl) : m_impl(impl) {}
MatchPolicy::~MatchPolicy() {
	SAFE_DELETE(m_impl);
}
bool MatchPolicy::match(const std::string& file) {
	return m_impl->match(file);
}

CopyPolicy::CopyPolicy(CopyPolicyImpl* impl) : m_impl(impl) {}
CopyPolicy::~CopyPolicy() {
	SAFE_DELETE(m_impl);
}
bool CopyPolicy::copy(const std::string& src, const std::string& dest) {
	DEBUG_PRINT("copy:%s -> %s", src.c_str(), dest.c_str());
	return m_impl->copy(src, dest);
}

RenamePolicy::RenamePolicy(RenamePolicyImpl* impl) : m_impl(impl) {}
RenamePolicy::~RenamePolicy() {
	SAFE_DELETE(m_impl);
}
std::string RenamePolicy::rename(const std::string& name) {
	return m_impl->rename(name);
}

bool Collector::isDirExist(const std::string& dir) {
	bool ret = false;
	DIR* pDir = opendir(dir.c_str());
	if (pDir) {
		closedir(pDir);
		ret = true;
	}
	return ret;
}

bool Collector::getFileVec(const std::string& dir, std::vector<std::string>& fileVec) {
	if (!isDirExist(dir)) {
		return false;
	}
	getFileVecInner(dir, dir, fileVec);
	return true;
}

bool Collector::getFileVecInner(const std::string& dirRoot, const std::string& curDir, std::vector<std::string>& fileVec) {
	struct dirent *p_entry = NULL;
	DIR* pDir = opendir(curDir.c_str());
	if (!pDir) {
		return false;
	}

	while (NULL != (p_entry = readdir(pDir))) {
		std::string curFilePath;
		curFilePath.append(curDir).append("/").append(p_entry->d_name);
		if (p_entry->d_type == DT_DIR) {
			if (strcmp(".", p_entry->d_name) == 0 || strcmp("..", p_entry->d_name) == 0)
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
	if (!isDirExist(m_srcDir) || !isDirExist(m_destDir)) {
		return false;
	}
	std::vector<std::string> srcFileVec;
	getFileVec(m_srcDir, srcFileVec);

	for (std::vector<std::string>::iterator srcFile = srcFileVec.begin(); srcFile != srcFileVec.end(); ++srcFile) {
		if (!m_matchPolicy.match(*srcFile)) {
			continue;
		}
		std::string destFile = m_renamePolicy.rename(srcFile->substr(m_srcDir.length()));
		destFile = m_destDir + destFile;
		m_copyPolicy.copy(*srcFile, destFile);
	}
}

}