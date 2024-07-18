#pragma once
#include "ws2/TCPSocket.hpp"

//<summary>
//Класс для работы с сокетом программе №1
//<summary>
class ClientSocket : public TCPSocket {
private:
	const char* ip_address = "127.0.0.1";
	const int port = 12345;
	SOCKADDR_IN serverAddr;
public:
	void startup_socket() override;
	void wait_connection() override;
	void disconnect() override;
};