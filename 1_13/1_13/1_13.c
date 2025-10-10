#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int convert_to_decimal(char* str, int base) {

	int result = 0;
    char* p = str;

    if (base < 2 || base > 36) {
        return -2;
    }

    while (*p) {
        int digit;
        if (*p >= '0' && *p <= '9') {
            digit = *p - '0';
        }
        else if (*p >= 'A' && *p <= 'Z') {
            digit = *p - 'A' + 10;
        }

        else {
            return -1;
        }

        result = result * base + digit;
        p++;
    }
    return result;
}

int main(void) {
	
	char value[33];
	int base;
	char check;
    int decimal;

	printf("Enter number as a string: ");
	scanf("%s", value);

    printf("Enter base number (int, 2-36): ");
    if (scanf("%d", &base) == 1 && (scanf("%c", &check) == 1 && (check == '\n' || check == ' '))) {
    }
    else {
        printf("Incorrect input.");
        return 1;
    }

    decimal = convert_to_decimal(value, base);

    if (decimal == -2) {
        printf("Incorrect base.");
        return 1;
    }

    if (decimal == -1) {
        printf("Error programm.");
        return 1;
    }

    printf("Your decimal number: %d", decimal);

	return 0;
}