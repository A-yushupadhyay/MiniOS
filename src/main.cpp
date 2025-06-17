#include <iostream>
#include <limits>  // for std::numeric_limits
#include "../include/AuthManager.hpp"  // ✅ Include this
#include "../include/Shell.hpp"  // ✅ Include Shell class

void showWelcomeScreen() {
    std::cout << "===============================" << std::endl;
    std::cout << "         Welcome to MiniOS      " << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
}

int getUserChoice() {
    int choice;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();  // clear fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard bad input
            std::cout << "❌ Invalid input. Please enter a number: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // flush newline
            return choice;
        }
    }
}

int main() {
    bool running = true;

    while (running) {
        showWelcomeScreen();
        int choice = getUserChoice();

        std::string username, password;

        switch (choice) {
            case 1:
                std::cout << "Username: ";
                getline(std::cin, username);
                std::cout << "Password: ";
                getline(std::cin, password);
                AuthManager::loginUser(username, password);
                if (AuthManager::loginUser(username, password)) {
                    Shell shell(username);
                    shell.start(); // 🎯 Run shell
                }
                
                break;

            case 2:
                std::cout << "Choose Username: ";
                getline(std::cin, username);
                std::cout << "Choose Password: ";
                getline(std::cin, password);
                AuthManager::registerUser(username, password);
                break;

            case 3:
                std::cout << "Exiting MiniOS... Goodbye!\n";
                running = false;
                break;

            default:
                std::cout << "❌ Invalid choice. Please select 1, 2 or 3.\n";
        }

        std::cout << "\n";
    }

    return 0;
}
