# 💬 CHAT APPLICATION WITH SDL INTEGRATION  

![Platform](https://img.shields.io/badge/platform-Windows-blue)  
![Language](https://img.shields.io/badge/language-C-brightgreen)  
![SDL2](https://img.shields.io/badge/SDL2-2.0.22-orange)  

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

## 🛠 Compile & Run (Server + Client)

```powershell
# ---------------------------
# 1. Compile & Run the Server
# ---------------------------
gcc server.c -o server -lws2_32
server.exe

# ---------------------------
# 2. Compile & Run the Client
# ---------------------------
gcc -g -c client.c -Isrc/Include -Lsrc/lib `
-lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL_mixer -lSDL2

gcc -g -o client.exe client.o -Isrc/Include -Lsrc/lib `
-lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -lws2_32

client.exe

