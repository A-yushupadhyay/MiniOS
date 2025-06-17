#ifndef AUTHMANAGER_HPP
#define AUTHMANAGER_HPP

#include <string>

class AuthManager {
public:
    static bool registerUser(const std::string& username, const std::string& password);
    static bool loginUser(const std::string& username, const std::string& password);
private:
    std::string hashPassword(const std::string& password);
};
#endif
