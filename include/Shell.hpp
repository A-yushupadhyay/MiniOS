#ifndef SHELL_HPP
#define SHELL_HPP

#include <string>
#include "../include/FileManager.hpp"  // Include the FileManager class

class Shell {
public:
    explicit Shell(const std::string& user);
    void start();

private:
    std::string username;           // Logged-in username
    std::string currentPath;        // Current directory path (within virtual FS)
    FileManager fileManager;        // Manages file operations (create, read, etc.)

    void executeCommand(const std::string& input);
    void makeDirectory(const std::string& folderName);
    void changeDirectory(const std::string& folderName);
    void listDirectory();
    void editFile(const std::string& filename);
    void viewFile(const std::string& filename);
     void deleteFile(const std::string& filename); // ✅ <-- Added
};

#endif // SHELL_HPP
