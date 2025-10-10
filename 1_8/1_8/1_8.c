/* Реализовать функцию, которая принимает в качестве параметра строку и “переворачивает” 
(reverse) входную строку в той же области памяти. Продемонстрировать работу функции. */

#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {

	int lenght = strlen(str);
	int start = 0;
	int end = lenght - 1;
	char temp_ch;

	while (start < end) {
		temp_ch = str[start];
		str[start] = str[end];
		str[end] = temp_ch;            // стыбзил свой же код из задания 4.. )9)

		start++;
		end--;
	}
}

int main() {

	char str[BUFSIZ];

	printf("Enter your string: ");
	scanf("%s", str);

	printf("\nOriginal string: %s", str);

	reverse_string(str);

    printf("\nReversed string: %s\n", str);

	return 0;
}

