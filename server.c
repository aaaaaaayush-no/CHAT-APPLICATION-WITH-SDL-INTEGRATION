#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <time.h>
#include <conio.h>

#define MAX_CLIENTS 10
#define MAX_MESSAGE_LENGTH 256
#define SERVER_PORT 8080
#define LOG_FILE "chat_history.txt"
#define ADMIN_KEY "admin123" // Server-side admin key

typedef struct {
    SOCKET socket;
    char username[32];
} Client;

Client clients[MAX_CLIENTS];
int clientCount = 0;
FILE *logFile;

// Function to get current timestamp
void getCurrentTimestamp(char *timestamp) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(timestamp, 25, "%Y-%m-%d %H:%M:%S", t);
}

// Function to save message to file
void saveMessageToFile(const char* username, const char* message) {
    char timestamp[25];
    getCurrentTimestamp(timestamp);
    
    logFile = fopen(LOG_FILE, "a");  //opened in a mode to add to the file
    if (logFile != NULL) {
        fprintf(logFile, "[%s] %s: %s\n", timestamp, username, message);
        fclose(logFile);
    }
}

// Function to display chat history on server console
void displayChatHistory() {
    system("cls"); // Clear console
    printf("\n=== Chat History ===\n");
    
    FILE *file = fopen(LOG_FILE, "r"); //open in reading mode
    if (file != NULL) {
        char line[MAX_MESSAGE_LENGTH];
        while (fgets(line, sizeof(line), file)) { //get the strings from the file
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("No chat history available.\n");
    }
    
    printf("\nPress any key to return to server console...");
    _getch();
    system("cls");
    printf("Server running on port %d\n", SERVER_PORT);
    printf("Press 'H' to view chat history\n");
}

// Function to broadcast message
void broadcastMessage(const char* message, int senderIndex) {   //message is received from buffer and sender index is i
    for (int i = 0; i < clientCount; i++) {
        if (i != senderIndex) {
            send(clients[i].socket, message, strlen(message), 0); // send is socket function for sending the data
        }
    }
}

// Function to remove client
void removeClient(int index) {
    closesocket(clients[index].socket);
    for (int i = index; i < clientCount - 1; i++) {
        clients[i] = clients[i + 1]; //reduce the index by 1
    }
    clientCount--;
}

// Function to handle server console input
DWORD WINAPI consoleInputThread(LPVOID lpParam) { //dword is 32 bit unsigned long 
    //lpparam to provide context to the thread here it isnot used  and lpvoid is pointer
    //winapi to use the functions like createthread
    char key;
    printf("Press 'H' to view chat history\n");
    
    while (1) {
        if (_kbhit()) {
            key = _getch();
            if (toupper(key) == 'H') {
                // Prompt for admin key
                char input[32];
                printf("\nEnter admin key: ");
                scanf("%s", input);
                
                if (strcmp(input, ADMIN_KEY) == 0) {
                    displayChatHistory();
                } else {
                    printf("\nInvalid key! Access denied.\n");
                    Sleep(2000);
                    system("cls");
                    printf("Server running on port %d\n", SERVER_PORT);
                    printf("Press 'H' to view chat history\n");
                }
            }
        }
        Sleep(100);
    }
    return 0;
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
    
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    if (listen(serverSocket, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    printf("Server started on port %d\n", SERVER_PORT);
    
    // Create console input thread
    CreateThread(NULL, 0, consoleInputThread, NULL, 0, NULL);
    
    fd_set readfds;  //creats a set of sockets
    
    while (1) {
        FD_ZERO(&readfds); //empties the set
        FD_SET(serverSocket, &readfds); //adds a socket to the set
        
        for (int i = 0; i < clientCount; i++) {
            FD_SET(clients[i].socket, &readfds); //checks if any client has sent data
        }
        
        if (select(0, &readfds, NULL, NULL, NULL) == SOCKET_ERROR) {
            printf("Select failed\n");
            break;
        }
        
        if (FD_ISSET(serverSocket, &readfds)) {
            struct sockaddr_in clientAddr;
            int addrLen = sizeof(clientAddr);
            SOCKET newSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen); //waits for incoming connection request and accepts
            
            if (newSocket != INVALID_SOCKET) {
                if (clientCount < MAX_CLIENTS) {
                    char username[32];
                    int bytesReceived = recv(newSocket, username, sizeof(username), 0);
                    if (bytesReceived > 0) {
                        username[bytesReceived] = '\0';
                        
                        clients[clientCount].socket = newSocket;
                        strcpy(clients[clientCount].username, username);
                        
                        char announcement[MAX_MESSAGE_LENGTH];
                        snprintf(announcement, MAX_MESSAGE_LENGTH, "%s has joined the chat", username);
                        broadcastMessage(announcement, clientCount);
                        saveMessageToFile("SERVER", announcement);
                        
                        clientCount++;
                        printf("New client connected: %s\n", username);
                    }
                } else {
                    const char* msg = "Server is full";
                    send(newSocket, msg, strlen(msg), 0);
                    closesocket(newSocket);
                }
            }
        }
        
        for (int i = 0; i < clientCount; i++) {
            if (FD_ISSET(clients[i].socket, &readfds)) {
                char buffer[MAX_MESSAGE_LENGTH];
                int bytesReceived = recv(clients[i].socket, buffer, sizeof(buffer), 0);
                
                if (bytesReceived > 0) {
                    buffer[bytesReceived] = '\0';
                    broadcastMessage(buffer, i);
                    saveMessageToFile(clients[i].username, buffer);
                    printf("Message from %s: %s\n", clients[i].username, buffer);
                }
                else {
                    char announcement[MAX_MESSAGE_LENGTH];
                    snprintf(announcement, MAX_MESSAGE_LENGTH, "%s has left the chat", clients[i].username);
                    removeClient(i);
                    broadcastMessage(announcement, -1);
                    saveMessageToFile("SERVER", announcement);
                    printf("Client disconnected: %s\n", announcement);
                    i--;
                }
            }
        }
    }
    
    closesocket(serverSocket);
    for (int i = 0; i < clientCount; i++) {
        closesocket(clients[i].socket);
    }
    WSACleanup();
    
    return 0;
}