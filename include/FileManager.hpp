#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <string>

class FileManager {
public:
    bool createFile(const std::string& fullPath, const std::string& owner);
    bool readFile(const std::string& fullPath, const std::string& currentUser);
    bool writeFile(const std::string& fullPath, const std::string& currentUser, const std::string& content);
    bool executeFile(const std::string& fullPath, const std::string& currentUser);
    bool changePermissions(const std::string& fullPath, const std::string& newPerms, const std::string& currentUser);
    bool hasPermission(const std::string& fullPath, const std::string& currentUser, char action);
};

#endif
