#include "server.h"

WSADATA wsaData;
SOCKET serverSocket, clientSocket;
SOCKADDR_IN serverAddr, clientAddr;

void create_server() {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Принимаем подключения от любого адреса
    serverAddr.sin_port = htons(12345); // Порт сервера

    bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);
}

void wait_connection() {
    std::cout << "Waiting for connections..." << std::endl;

    int clientAddrSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);

    std::cout << "Connection successful!" << std::endl;
}

bool is_empty(const char* message, int size) {
    return message[0] == '\0';
}

String recieve_message() {
    char buffer[1024] = { 0 };
    recv(clientSocket, buffer, 1024, 0);
    if (is_empty(buffer, 1024)) {
        std::cout << "Failed connection." << std::endl;
        wait_connection();
        return String();
    }

    return String(buffer);
}

void disconnect() {
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

int main(int argc, char* argv[])
{
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    create_server();

    wait_connection();

    String message;

    while (true) {
        message = recieve_message();
        if (message.is_null()) {
            continue;
        }

        std::string response = "Success";
        send(clientSocket, response.c_str(), response.size(), 0);

        if (message.get_length() % 32 != 0 || message.get_length() < 2) {
            std::cout << "Failed data recieved." << message << std::endl;
            continue;
        }

        std::cout << "Received message: " << message << std::endl;
    }

    disconnect();

	return 0;
}