#include "CStr.h"

String::String()
{
	str = new char[1];
	str[0] = '\0';
	length = 0;
}

String::String(const char* object)
{
	length = strlen(object) + 1;
	str = new char[length + 1];
	for (int i = 0; i < length; i++) {
		str[i] = object[i];
	}

	str[length] = '\0';
}

String::String(int length) {
	str = new char[length];
	this->length = length;
}

String::~String()
{
	delete[] str;
}

bool String::is_digits()
{
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] < '0' || str[i] > '9')
			return false;

		i++;
	}

	return true;
}

int String::get_length()
{
	return length;
}

void String::Input()
{
	std::string object;
	std::cin >> object;

	length = object.length();
	str = new char[length + 1];
	for (int i = 0; i < length; i++) {
		str[i] = object[i];
	}
	str[length] = '\0';
}

char& String::operator[](int index)
{
	if (index < 0) {
		return str[0];
	}

	if (index > length) {
		return str[length];
	}

	return str[index];
}

String& String::operator=(const String& object)
{
	if (this == &object)
		return *this;

	delete[] str;
	length = object.length;
	str = new char[length + 1];
	for (int i = 0; i < length; i++) {
		str[i] = object.str[i];
	}
	str[length] = '/0';
	return *this;
}

void String::replace_at(int index, const char* replace_chars)
{
	if (index > length || index < 0) {
		return;
	}

	int replacement_length = strlen(replace_chars);
	char* new_str = new char[length + replacement_length];

	for (int i = 0; i < index; i++) {
		new_str[i] = str[i];
	}

	for (int i = 0; i < replacement_length; i++) {
		new_str[index + i] = replace_chars[i];
	}

	for (int i = index + 1; i < length; i++) {
		new_str[i + strlen(replace_chars) - 1] = str[i];
	}

	new_str[length + replacement_length - 1] = '\0';

	delete[] str;

	str = new_str;
	length = length + strlen(replace_chars);
}

void String::sort()
{
	for (int gap = length / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < length; i++) {
			int temp = str[i];
			int j;

			for (j = i; j >= gap && str[j - gap] > temp; j -= gap) {
				str[j] = str[j - gap];
			}

			str[j] = temp;
		}
	}
}

bool String::is_null()
{
	return length == 0;
}

const char* String::c_str() {
	return str;
}

std::ostream& operator<<(std::ostream& stream, String& object)
{
	for (int i = 0; i < object.get_length(); i++) {
		stream << object.str[i];
	}

	return stream;
}
