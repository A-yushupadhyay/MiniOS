#include "../include/FileManager.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

bool FileManager::createFile(const std::string& fullPath, const std::string& owner) {
    std::ofstream file(fullPath);
    if (!file) return false;
    file.close();

    std::ofstream meta(fullPath + ".meta");
    meta << "owner:" << owner << "\n";
    meta << "permissions:rwx\n";
    meta.close();
    return true;
}

bool FileManager::hasPermission(const std::string& fullPath, const std::string& currentUser, char action) {
    std::ifstream meta(fullPath + ".meta");
    if (!meta) return false;

    std::string line, owner, perms;
    getline(meta, line);
    owner = line.substr(line.find(':') + 1);
    owner.erase(0, owner.find_first_not_of(" \t\n\r")); // Trim whitespace
    getline(meta, line);
    perms = line.substr(line.find(':') + 1);
    perms.erase(0, perms.find_first_not_of(" \t\n\r")); // Trim whitespace

    if (currentUser != owner) return false;

    switch (action) {
        case 'r': return perms.find('r') != std::string::npos;
        case 'w': return perms.find('w') != std::string::npos;
        case 'x': return perms.find('x') != std::string::npos;
    }
    return false;
}


bool FileManager::readFile(const std::string& fullPath, const std::string& currentUser) {
    if (!hasPermission(fullPath, currentUser, 'r')) {
        std::cout << "Permission denied: read\n";
        return false;
    }

    std::ifstream file(fullPath);
    if (!file) return false;

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::cout << content << "\n";
    return true;
}

bool FileManager::writeFile(const std::string& fullPath, const std::string& currentUser, const std::string& content) {
    if (!hasPermission(fullPath, currentUser, 'w')) {
        std::cout << "Permission denied: write\n";
        return false;
    }

    std::ofstream file(fullPath);
    if (!file) return false;

    file << content;
    return true;
}

bool FileManager::executeFile(const std::string& fullPath, const std::string& currentUser) {
    if (!hasPermission(fullPath, currentUser, 'x')) {
        std::cout << "Permission denied: execute\n";
        return false;
    }

    std::cout << "Executing " << fs::path(fullPath).filename().string() << "...\n";
    return true;
}

bool FileManager::changePermissions(const std::string& fullPath, const std::string& newPerms, const std::string& currentUser) {
    std::string metaPath = fullPath + ".meta";

    std::ifstream metaIn(metaPath);
    if (!metaIn) return false;

    std::string ownerLine, permLine;
    getline(metaIn, ownerLine);
    getline(metaIn, permLine);
    metaIn.close();

    std::string owner = ownerLine.substr(ownerLine.find(':') + 1);
    if (owner != currentUser) {
        std::cout << "Only owner can change permissions.\n";
        return false;
    }

    std::ofstream metaOut(metaPath);
    metaOut << "owner:" << owner << "\n";
    metaOut << "permissions:" << newPerms << "\n";
    return true;
}
