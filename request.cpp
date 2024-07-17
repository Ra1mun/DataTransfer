#include "request.h"

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;
String shared_data;

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

	std::cout << "Получено: " << shared_data << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	std::thread producerThread(producer);
	std::thread consumerThread(consumer);

	producerThread.join();
	consumerThread.join();

	return 0;
}
