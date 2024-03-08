Overview
This is a simple chat application consisting of a client (`ChatClient`) and a server (`ChatServer`). The application allows clients to connect to the server and exchange messages in real-time.

ChatServer Class
 Constructor
-  Constructs a `ChatServer` object, initializing the server socket and binding it to the specified port.

Member Functions
- void start():
  - Listens for incoming client connections.
  - Accepts connections one at a time.
  - Creates a new thread for each connected client (currently handled sequentially without threading, couldn't implement threading due to time constraints).
  - Handles incoming messages from clients, broadcasts them to other connected clients, and logs messages to a file.

- void handleClient():
  - Receives messages from a connected client.
  - Broadcasts the received message to all other connected clients.
  - Logs the received message along with a timestamp to a file.

ChatClient Class
Constructor
- Constructs a `ChatClient` object, initializing the client socket and connecting to the specified server IP and port.

Member Functions
- void start():
  - Takes user input and sends messages to the server.
  - Receives responses from the server and prints them to the console.

- void receiveMessages():
  - Listens for incoming messages from the server.
  - Prints received messages to the console.

Usage
Start the server using the `chat_server` executable and the client using the `chat_client` executable.
The server will logs all incoming messages along with timestamps to the "chat_log.txt" file.