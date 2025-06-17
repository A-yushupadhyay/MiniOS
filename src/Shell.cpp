#include "../include/Shell.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "../include/AuthManager.hpp"
#include "../include/Scheduler.hpp"
#include "../include/FileManager.hpp"

namespace fs = std::filesystem;

Shell::Shell(const std::string& user)
    : username(user),
      currentPath("data/virtual_fs/" + user),
      fileManager() // ✅ Default constructor
{
    fs::create_directories(currentPath); // Ensure base user folder exists
}

void Shell::start() {
    std::string input;

    while (true) {
        std::cout << "MiniOS" << currentPath.substr(currentPath.find(username) + username.length()) << "> ";

        getline(std::cin, input);

        if (input == "logout") {
            std::cout << "Logging out...\n";
            break;
        }

        executeCommand(input);
    }
}

void Shell::executeCommand(const std::string& input) {
    std::istringstream iss(input);
    std::string command, argument;
    iss >> command >> std::ws;
    getline(iss, argument);

    std::string fullPath = currentPath + "/" + argument;

    if (command == "mkdir") {
        makeDirectory(argument);

    } else if (command == "cd") {
        changeDirectory(argument);

    } else if (command == "ls") {
        listDirectory();

    } else if (command == "edit") {
        editFile(argument);

    } 
    else if (command == "rm") {
        deleteFile(argument);
    }else if (command == "cat") {
        viewFile(argument);

    } else if (command == "scheduler") {
        int n;
        std::cout << "How many processes? ";
        std::cin >> n;
        std::cin.ignore();

        Scheduler scheduler;
        for (int i = 0; i < n; ++i) {
            std::string name;
            int burst;
            std::cout << "Enter process name: ";
            getline(std::cin, name);
            std::cout << "Enter burst time: ";
            std::cin >> burst;
            std::cin.ignore();
            scheduler.addProcess(name, burst);
        }

        scheduler.runRoundRobin();

    } else if (command == "create") {
        fileManager.createFile(fullPath, username);

    } else if (command == "read") {
        fileManager.readFile(fullPath, username);

    } else if (command == "write") {
        std::string content;
        std::cout << "Enter content (end with ':wq'):\n";
        std::ostringstream oss;
        std::string line;
        while (getline(std::cin, line)) {
            if (line == ":wq") break;
            oss << line << "\n";
        }
        fileManager.writeFile(fullPath, username, oss.str());

    } else if (command == "execute") {
        fileManager.executeFile(fullPath, username);

    } 
     else if (command == "chmod") {
        std::string permissions;
        std::cout << "Enter permissions (e.g., rwx): ";
        std::cin >> permissions;
        std::cin.ignore();
        fileManager.changePermissions(fullPath, permissions, username);

    } else {
        std::cout << "❌ Unknown command: " << command << "\n";
    }
}

void Shell::makeDirectory(const std::string& folderName) {
    fs::path dirPath = fs::path(currentPath) / folderName;
    if (!fs::exists(dirPath)) {
        fs::create_directory(dirPath);
        std::cout << "✅ Folder created.\n";
    } else {
        std::cout << "⚠️ Folder already exists.\n";
    }
}

void Shell::changeDirectory(const std::string& folderName) {
    fs::path newPath;
    if (folderName == "..") {
        newPath = fs::path(currentPath).parent_path();
        if (newPath.string().find("data/virtual_fs/" + username) != 0) {
            std::cout << "⚠️ Access denied.\n";
            return;
        }
    } else {
        newPath = fs::path(currentPath) / folderName;
    }

    if (fs::exists(newPath) && fs::is_directory(newPath)) {
        currentPath = newPath.string();
    } else {
        std::cout << "❌ Directory not found.\n";
    }
}

void Shell::deleteFile(const std::string& filename) {
    std::string fullPath = currentPath + "/" + filename;
    std::string metaPath = fullPath + ".meta";

    // Prompt for confirmation
    std::string response;
    std::cout << "⚠️ Are you sure you want to delete '" << filename << "'? (y/n): ";
    std::getline(std::cin, response);

    if (response == "y" || response == "Y") {
        // Ensure files are closed before deleting
        std::ifstream fileCheck(fullPath);
        std::ifstream metaCheck(metaPath);
        fileCheck.close();
        metaCheck.close();

        try {
            if (fs::exists(fullPath)) fs::remove(fullPath);
            if (fs::exists(metaPath)) fs::remove(metaPath);
            std::cout << "✅ File and metadata deleted successfully.\n";
        } catch (const fs::filesystem_error& e) {
            std::cout << "❌ Error deleting file: " << e.what() << "\n";
        }
    } else {
        std::cout << "🟡 Deletion canceled.\n";
    }
}


void Shell::listDirectory() {
    std::cout << "📁 Contents:\n";
    for (const auto& entry : fs::directory_iterator(currentPath)) {
        std::cout << "  - " << entry.path().filename().string();
        if (fs::is_directory(entry)) std::cout << "/";
        std::cout << "\n";
    }
}

void Shell::editFile(const std::string& filename) {
    fs::path filePath = fs::path(currentPath) / filename;

    // ✅ Check write permission first
    if (!fileManager.hasPermission(filePath.string(), username, 'w')) {
        std::cout << "❌ Permission denied: You don't have write access.\n";
        return;
    }

    std::ofstream file(filePath);
    if (!file) {
        std::cout << "❌ Could not open file for writing.\n";
        return;
    }

    std::string line;
    std::cout << "Enter content (type ':wq' to save):\n";

    while (true) {
        getline(std::cin, line);
        if (line == ":wq") break;
        file << line << "\n";
    }

    std::cout << "✅ File saved.\n";
}


void Shell::viewFile(const std::string& filename) {
    fs::path filePath = fs::path(currentPath) / filename;
    std::ifstream file(filePath);

    if (!file) {
        std::cout << "❌ File not found.\n";
        return;
    }

    std::cout << "📄 File contents:\n";
    std::string line;
    while (getline(file, line)) {
        std::cout << line << "\n";
    }
}
