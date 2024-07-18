#pragma once
#include <string>
#include <WinSock2.h>

class TCPSocket {
protected:
	const int shared_flag = 0;
	SOCKET client_socket;
public:
	virtual void startup_socket() = 0;
	virtual void wait_connection() = 0;

	bool try_send_message(std::string message) {
		if (message.empty()) {
			return false;
		}

		send(client_socket, message.c_str(), message.size(), shared_flag);
		return true;
	}

	bool try_recieve_message(char* recieve_message, int size) {
		recv(client_socket, recieve_message, size, shared_flag);

		return recieve_message[0] != '\0';
	}

	virtual void disconnect() = 0;
};