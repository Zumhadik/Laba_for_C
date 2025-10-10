/* Реализовать функцию которая принимает в качестве параметра строку и проверяет, 
является ли заданная строка палиндромом. Продемонстрировать работу функции. */

#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int is_palindrome(char* str) {

	int lenght = strlen(str);
	int start = 0;
	int end = lenght - 1;

	while (start < end) {

		while (!isalnum(str[start])) {
			start++;
		}

		while (!isalnum(str[end])) {
			end--;
		}
		if (tolower(str[start]) != tolower(str[end])) {
			return 0;
		}

		start++;
		end--;
	}
	return 1;
}

int main() {
	setlocale(LC_ALL, "ru");

	char str[BUFSIZ];

	printf("Enter your string: ");
	scanf("%s", str);

	printf("String is %s", is_palindrome(str)
		? "palindrome"
		: "not palindrome");

	return 0;
}
