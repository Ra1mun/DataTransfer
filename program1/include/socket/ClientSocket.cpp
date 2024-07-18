#include "ClientSocket.h"

void ClientSocket::startup_socket()
{
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void ClientSocket::wait_connection()
{
	startup_socket();

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip_address);
	serverAddr.sin_port = htons(port);

	connect(client_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
}

void ClientSocket::disconnect()
{
	closesocket(client_socket);
	WSACleanup();
}
