#include "string_service.h"

//<summary>
//Проверка, что строка содержит только цифры
//<summary>
bool string_service::contains_only_digits(std::string str)
{
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]))
            return false;
    }

    return true;
}

//<summary>
//Сортировка Шелла
//<summary>
void string_service::shell_sort(std::string& str)
{
	int length = str.size();
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

//<summary>
//Обработка данных, которая была указана в тз
//<summary>
std::string string_service::processed_data(const std::string str) {
	if (!contains_only_digits(str) || str.size() > 64) {
		return "";
	}

	std::string result = str;
	shell_sort(result);
	int length = result.size();
	int count = 0;
	for (int i = 0; i < length + count; i++) {
		if (result[i] % 2 == 0) {
			result.replace(i, 1, replacement_substring);
			count += strlen(replacement_substring) - 1;
			i += strlen(replacement_substring) - 1;
		}
	}

	return result;
}

//<summary>
//Сумма всех цифр строки
//<summary>
int string_service::sum_digits(std::string str) {
	int result = 0;
	for (int i = 0; i < str.size(); i++) {
		if (isdigit(str[i]))
			result += (int)str[i] - 48;
	}

	return result;
}
