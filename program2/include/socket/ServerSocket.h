#pragma once
#include <ws2/TCPSocket.hpp>

class ServerSocket : public TCPSocket {
private:
	SOCKET server_socket;
	SOCKADDR_IN client_address, server_address;
public:
	void startup_socket() override;
	void wait_connection() override;
	void disconnect() override;
};