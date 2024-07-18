#include "server.h"

ServerSocket server;

int main(int argc, char* argv[])
{
    server.startup_socket();

    server.wait_connection();

    while (true) {
        char recieve_message[1024] = { 0 };
        if (!server.try_recieve_message(recieve_message, 1024)) {
            std::cout << "Failed connection!" << std::endl;
            server.wait_connection();
            continue;
        }
        std::string request = recieve_message;

        std::string response = "Success";
        server.try_send_message(response);

        if (std::atoi(request.c_str()) % 32 != 0 || request.size() < 2) {
            std::cout << "Data error." << std::endl;
            continue;
        }

        std::cout << "Success data" << std::endl;
    }

    server.disconnect();

	return 0;
}