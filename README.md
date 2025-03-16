# CHAT-APPLICATION-WITH-SDL-INTEGRATION

Overview

This is a simple chat application implemented in C using Winsock for networking and SDL2 for the graphical client interface. The application consists of a server that manages multiple clients and a client that provides a GUI for chatting.

Features
Server:

Handles multiple clients simultaneously.
Broadcasts messages to all connected clients.
Logs chat history to a file (chat_history.txt).
Allows administrators to view chat history with an access key.


Client:
Provides a graphical chat interface using SDL2.
Supports real-time message updates and scrolling.
Allows username input before joining the chat.
Plays a sound effect when a message is sent.

Setup Instructions

Ensure all the files in this repository are in the same folder.
Use VSCode for ease

2. Compile and Run

Server:

Compile the server:
gcc server.c -o server -lws2_32

Run the server:
./server.exe


Client:

Compile the client:
gcc -g -c client.c -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL_mixer -lSDL2  
gcc -g -o client.exe client.o -Isrc/Include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -lws2_32

Run the client:
./client.exe

How It Works
Server (server.c):
Starts a TCP server on port 8080.
Accepts new client connections.
Assigns usernames to clients and announces their entry.
Relays messages between clients.
Logs chat messages to chat_history.txt.
Removes disconnected clients.

Client (client.c):
Connects to the server IP and port.
Asks for a username.
Allows users to type and send messages.
Displays chat messages with a scrolling mechanism.
Plays a notification sound when sending messages.
Listens for new messages from the server in a separate thread.

Controls
Mouse Scroll Wheel: Scroll chat messages up/down.
Enter Key: Send a message.
Backspace: Delete the last character in the input field.
PageUp / PageDown: Scroll up/down an entire page of messages.
Close Window: Exit the client.

Admin Commands (Server-Side)
Press 'H': View chat history (requires entering an admin key).

Configuration
Server IP: Change the IP address in client.c (default: 192.168.18.192).
Port: Modify SERVER_PORT in both client.c and server.c.
Admin Key: Set a custom key in server.c (#define ADMIN_KEY "admin123").

Future Improvements
Implement private messaging.
Add encryption for message security.
Improve the UI with more styling and animations.
Create a Linux-compatible version.
