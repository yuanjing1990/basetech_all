#ifndef YJ_FILE_H_
#define YJ_FILE_H_
#include <string>

namespace yjutil {

std::string getFileName(const std::string& filePath);
std::string getFileDirectory(const std::string& filePath);
bool isDirectory(const std::string& filePath);
bool isFile(const std::string& filePath);

bool isFileExist(const std::string& filePath);
bool createFile(const std::string& filePath);
bool removeFile(const std::string& filePath);
bool createDir(const std::string& dirPath, bool bCreateParent = false);
bool removeDir(const std::string& dirPath, bool bRecursion = false);

}
#endif