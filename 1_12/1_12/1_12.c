#pragma warning(disable: 4996)

#include <stdio.h>

char* convert_num(int decimal, int base) {

    static char bit[33];
    char* p = bit + 33 - 1;
    int remainder;
    *p-- = 0;
    while (decimal) {
        remainder = decimal % base;
        *p-- = (remainder > 9) ? remainder - 10 + 'A' : remainder + '0';
        decimal /= base;
    }
    return p + 1;
}

int main(void) {
    int value, base;
    char check;
    char* bitnumber;

    printf("Enter integer number: ");
    if (scanf("%d", &value) == 1 && (scanf("%c", &check) == 1 && (check == '\n' || check == ' '))) {
    }

    else {
        printf("Incorrect input.");
        return 1;
    }

    printf("Enter base number(int): ");
    if (scanf("%d", &base) == 1 && (scanf("%c", &check) == 1 && (check == '\n' || check == ' '))) {
    }

    else {
        printf("Incorrect input.");
        return 1;
    }

    bitnumber = convert_num(value, base);

    printf("The integer is: %s\n", bitnumber);
}