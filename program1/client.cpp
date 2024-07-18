#include "client.h"

ClientSocket client;
string_service data_service;
std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;
std::string shared_data;


void producer() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	{
		std::lock_guard<std::mutex> lock(mtx);

		std::string request;
		std::cin >> request;

		request = data_service.processed_data(request);
		
		shared_data = request;
		data_ready = true;
	}
	cv.notify_one();
}

void consumer() {
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock, [] { return data_ready; });

	char message[3] = { 0 };
	std::snprintf(message, 3, "%d", data_service.sum_digits(shared_data));
	data_ready = false;
	shared_data = "";

	if (!client.try_send_message(message)) {
		std::cout << "Bad data entered!" << std::endl;
		return;
	}

	char buffer[1024] = { 0 };
	if (!client.try_recieve_message(buffer, 1024)) {
		std::cout << "Lost connection!" << std::endl;
		client.wait_connection();
		return;
	}

	std::cout << "Data successfully sent: " << message << std::endl;
}

int main(int argc, char* argv[])
{
	client.wait_connection();

	while (true){
		std::thread producerThread(producer);
		std::thread consumerThread(consumer);

		producerThread.join();
		consumerThread.join();
	}

	client.disconnect();

	return 0;
}
