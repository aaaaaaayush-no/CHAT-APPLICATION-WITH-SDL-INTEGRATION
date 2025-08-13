# 💬 CHAT APPLICATION WITH SDL INTEGRATION  

> A modern, simple, and fun chat app built in **C**, featuring:
> - ⚡ **Winsock** for networking (Windows)
> - 🎨 **SDL2** for a smooth graphical interface

---

## ✨ Features

### 🖥 Server
- 📡 Handles **multiple clients** simultaneously  
- 📢 Broadcasts messages to all connected users  
- 🗂 Logs chat history to `chat_history.txt`  
- 🔑 Admin mode with secure access to history  

### 💻 Client
- 🖼 **SDL2-powered GUI** for a modern chat look  
- ⏳ Real-time message updates with smooth scrolling  
- 📝 Username input before joining  
- 🔊 Fun notification sound when sending messages  

---

## 🛠 Installation & Setup

> ⚠ Make sure **all source files are in the same folder**  
> Recommended IDE: **VSCode**

---

### 1️⃣ Server
```bash
# Compile
gcc server.c -o server -lws2_32

# Run
./server.exe

2️⃣ Client
bash
Copy
Edit
# Compile object file
gcc -g -c client.c -Isrc/Include -Lsrc/lib \
-lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL_mixer -lSDL2

# Link executable
gcc -g -o client.exe client.o -Isrc/Include -Lsrc/lib \
-lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -lws2_32

# Run
./client.exe


