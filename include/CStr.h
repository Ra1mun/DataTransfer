#pragma once
#include <iostream>
#include <string>

class String {
private:
	char* str;
	int length;
public:
	String();
	String(const char* object);
	String(int length);
	~String();
	bool is_digits();
	int get_length();
	void Input();
	char& operator[](int index);
	String& operator=(const String& object);
	void replace_at(int index, const char* replace_chars);
	void sort();
	bool is_null();
	const char* c_str();
	friend std::ostream& operator<<(std::ostream& stream, String& object);
};