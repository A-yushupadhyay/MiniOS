# 💻 MiniOS – A Minimal Operating System Simulator in C++


> 🔧 Built using Object-Oriented C++ | 🔐 Auth System | 📁 File Manager | 🧠 Round Robin Scheduler  
> 🚀 Designed to showcase system-level skills and impress top-tier recruiters (Google, Uber, Flipkart, etc.)


![Screenshot (311)](https://github.com/user-attachments/assets/15ce7e2b-eefa-48da-857c-b066d5eb9eee)



![Screenshot (312)](https://github.com/user-attachments/assets/022aea19-aac6-45b8-91c4-185fc7010f6c)





---

## 📌 Project Overview

**MiniOS** is a command-line simulation of a mini operating system that supports:

- Secure user authentication with hashed passwords
- File creation, listing, and permission control
- Round-robin process scheduling (like modern CPUs!)
- Modular and extensible system built using modern C++

---

## 🛠️ Tech Stack

| Layer         | Technology         |
|---------------|--------------------|
| Language      | C++17              |
| Build System  | Makefile / g++     |
| Structure     | OOP + Modular C++  |
| Optional GUI  | ncurses (planned)  |

---

## 🔒 Features

### ✅ Authentication Manager
- Register/login system with in-memory password protection
- (Planned: bcrypt/SHA256 hash support)

### 📁 File Manager
- Simulates basic file operations (create/list/delete)
- (Planned: Unix-style permission flags)

### 🧠 CPU Scheduler
- Round Robin Scheduling with Gantt Chart CLI output
- Turnaround and waiting time calculation

---

## 🚀 How to Run

```bash
# Compile using Makefile (on Linux/macOS)
make run

# OR manually on Windows:
g++ -std=c++17 -Wall -Iinclude -o build/minios.exe src/*.cpp
./build/minios.exe


```


📦 Folder Structure
makefile
Copy
Edit
MiniOS/
├── build/              # Compiled binaries
├── include/            # Header files
├── src/                # Source files
├── Makefile
├── .gitignore
└── README.md


📈 Future Enhancements
🔐 Encrypted password storage with SHA256/bcrypt

🧾 File permission system (r/w/x per user)

🖼️ Terminal GUI with ncurses

🌐 Multi-user session simulation


👨‍💻 Author
Ayush Upadhyay
Email - puskaru202@gmail.com




