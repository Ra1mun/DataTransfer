#include "client.h"


const char* ip_address = "127.0.0.1";
const int port = 12345;

SOCKET clientSocket;
std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;
String shared_data;

void startup_connection() {
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void wait_connection() {
	SOCKADDR_IN serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip_address);
	serverAddr.sin_port = htons(port);

	connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
}

void disconnect() {
	closesocket(clientSocket);
	WSACleanup();
}

bool is_empty(const char* message, int size) {
	return message[0] == '\0';
}

void producer() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	{
		std::lock_guard<std::mutex> lock(mtx);

		String request;
		request.Input();
		const char* replacement_substring = "KB";

		if (request.is_digits() && request.get_length() < 64) {
			request.sort();
			int length = request.get_length();
			int count = 0;
			for (int i = 0; i < length + count; i++) {
				if (request[i] % 2 == 0) {
					request.replace_at(i, replacement_substring);
					count += strlen(replacement_substring) - 1;
					i += strlen(replacement_substring) - 1;
				}
			}
		}

		shared_data = request;

		data_ready = !shared_data.is_null();
	}
	cv.notify_one();
}

void consumer() {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [] { return data_ready; });

	send(clientSocket, shared_data.c_str(), shared_data.get_length(), 0);

	char buffer[1024] = { 0 };
	recv(clientSocket, buffer, 1024, 0);
	if (!is_empty(buffer, 1024)) {
		std::cout << "Response from server: " << buffer << std::endl;
	}
	else {
		startup_connection();
		wait_connection();
		std::cout << "Lost connection" << std::endl;
	}
		

	data_ready = false;
	shared_data = String();
}

int main()
{
	startup_connection();

	wait_connection();

	while (true){
		std::thread producerThread(producer);
		std::thread consumerThread(consumer);

		producerThread.join();
		consumerThread.join();
	}

	disconnect();

	return 0;
}
