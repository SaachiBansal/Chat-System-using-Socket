#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std; 

class ChatClient
{
public:
    ChatClient(const string &serverIP, int serverPort);
    void start();

private:
    int clientSocket;
    bool isRunning;

    void receiveMessages();
};

ChatClient::ChatClient(const string &serverIP, int serverPort) : isRunning(true)
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddr.sin_port = htons(serverPort);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
}

void ChatClient::start()
{
    string message;
    char buf[1024];

    while (isRunning)
    {
        cout << "> " << flush;
        getline(cin, message);

        send(clientSocket, message.c_str(), message.size(), 0);

        memset(buf, 0, 1024);
        int bytesReceived = recv(clientSocket, buf, 1024, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
    }

    close(clientSocket);
}

void ChatClient::receiveMessages()
{
    char buffer[1024];
    while (isRunning)
    {
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0)
        {
            cerr << "Connection closed by server." << endl;
            isRunning = false;
            break;
        }

        buffer[bytesRead] = '\0';
        cout << buffer << endl;
    }
}

int main()
{
    ChatClient client("127.0.0.1", 12345);
    client.start();

    return 0;
}
    