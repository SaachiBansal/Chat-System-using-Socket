# Chat Application

This simple chat application comprises a server (`ChatServer`) and a client (`ChatClient`). Users can connect to the server to exchange real-time messages.

## `ChatServer` Class

### Constructor

- Constructs a `ChatServer` object, initializing the server socket and binding it to the specified port.

### Member Functions

- **void start():**
  - Listens for incoming client connections.
  - Accepts connections one at a time.
  - Creates a new thread for each connected client (currently handled sequentially without threading due to time constraints).
  - Handles incoming messages from clients, broadcasts them to other connected clients, and logs messages to a file.

- **void handleClient():**
  - Receives messages from a connected client.
  - Broadcasts the received message to all other connected clients.
  - Logs the received message along with a timestamp to a file.

## `ChatClient` Class

### Constructor

- Constructs a `ChatClient` object, initializing the client socket and connecting to the specified server IP and port.

### Member Functions

- **void start():**
  - Takes user input and sends messages to the server.
  - Receives responses from the server and prints them to the console.

- **void receiveMessages():**
  - Listens for incoming messages from the server.
  - Prints received messages to the console.

## Usage

1. Start the server using the `chat_server` executable.
2. Start the client using the `chat_client` executable.
3. The server logs all incoming messages, along with timestamps, to the "chat_log.txt" file.
