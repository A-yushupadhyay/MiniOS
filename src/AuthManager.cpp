#include "../include/AuthManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

bool AuthManager::registerUser(const std::string& username, const std::string& password) {
    std::ifstream infile("data/users.txt" , std::ios::in);
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string user, pass;
        getline(ss, user, ':');
        if (user == username) {
            std::cout << "❌ Username already exists.\n";
            return false;
        }
    }
    infile.close();

    std::ofstream outfile("data/users.txt", std::ios::app);
    outfile << username << ":" << password << "\n";
    std::cout << "✅ Registration successful!\n";

    return true;
}

bool AuthManager::loginUser(const std::string& username, const std::string& password) {
    std::ifstream infile("data/users.txt" , std::ios::in);
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string user, pass;
        getline(ss, user, ':');
        getline(ss, pass, ':');
        if (user == username && pass == password) {
            std::cout << "✅ Login successful! Welcome, " << username << "\n";
            return true;
        }
    }

    std::cout << "❌ Invalid credentials. Try again.\n";
    return false;
}
