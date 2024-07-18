#include "ServerSocket.h"

void ServerSocket::startup_socket() {
    WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(12345);

    bind(server_socket, (SOCKADDR*)&server_address, sizeof(server_address));
    listen(server_socket, SOMAXCONN);
}

void ServerSocket::wait_connection() {
    std::cout << "Waiting for connections..." << std::endl;

    int clientAddrSize = sizeof(client_address);
    client_socket = accept(server_socket, (SOCKADDR*)&client_address, &clientAddrSize);

    std::cout << "Connection successful!" << std::endl;
}

void ServerSocket::disconnect() {
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
}