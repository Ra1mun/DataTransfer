#pragma once
#include <ws2/TCPSocket.hpp>

//<summary>
//����� ��� ������ � ������� ��������� �2
//<summary>
class ServerSocket : public TCPSocket {
private:
	//<summary>
	//����� ��������� �2
	//<summary>
	SOCKET server_socket;
	//<summary>
	//����� ������� � ��������� �2
	//<summary>
	SOCKADDR_IN client_address, server_address;
public:
	void startup_socket() override;
	void wait_connection() override;
	void disconnect() override;
};