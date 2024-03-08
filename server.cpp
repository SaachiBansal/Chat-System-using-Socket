#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdlib>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std; 

string getCurrentTime()
{
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    return ctime(&time);
}

class ChatServer
{
public:
    ChatServer(int port);
    void start();

private:
    int serverSocket;
    int clientSocket;
    ofstream chatLog;

    void handleClient();
};

ChatServer::ChatServer(int port)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (::bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }   

    listen(serverSocket, 5);

    chatLog.open("chat_log.txt", ios::app);
}

void ChatServer::start()
{
    cout << "Server listening on port 12345..." << endl;

    while (true)
    {
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
        if (clientSocket == -1)
        {
            perror("Error accepting client connection");
            continue;
        }

        handleClient();
    }
}

void ChatServer::handleClient()
{
    char buffer[1024];
    while (true)
    {
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0)
        {
            break;
        }

        buffer[bytesRead] = '\0';

        string message = "[" + to_string(clientSocket) + "] " + buffer;
        cout << message << endl;

        send(clientSocket, buffer, bytesRead + 1, 0);

        chatLog << "[" << getCurrentTime() << "] " << message << endl;
    }

    close(clientSocket);
}

int main()
{
    ChatServer server(12345);
    server.start();

    return 0;
}
