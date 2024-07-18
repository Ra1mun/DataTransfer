#include "ClientSocket.h"


//<summary>
//������������� �������
//<summary>
void ClientSocket::startup_socket()
{
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

//<summary>
//����������� � �������
//<summary>
void ClientSocket::wait_connection()
{
	startup_socket(); // ���������� ������

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip_address);
	serverAddr.sin_port = htons(port);

	connect(client_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
}

//<summary>
//���������� ��������� �1 �� ������
//<summary>
void ClientSocket::disconnect()
{
	closesocket(client_socket);
	WSACleanup();
}
