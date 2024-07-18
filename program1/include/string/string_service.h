#pragma once
#include <string>
#include <cstdlib>

class string_service {
private:
	const char* replacement_substring = "KB";
	bool contains_only_digits(std::string str);
	void shell_sort(std::string& str);
public:
	std::string processed_data(const std::string str);
	int sum_digits(std::string str);
};