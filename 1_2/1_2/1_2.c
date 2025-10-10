/* Реализовать приложение, запрашивающее у пользователя натуральное число, и
проверяющее, является ли это число простым; является ли оно составным. */

#pragma warning(disable: 4996)

#include <stdio.h>

int main()
{
    int value;
    char c;

    printf("Enter integer number: ");

    if (scanf("%d", &value) == 1 && (scanf("%c", &c) == 1 && (c == '\n' || c == ' '))) {
    }

    else {
        printf("error input");
        return 1;
    }

    if (value < 0) {
        printf("input value is not integer.");
        return 1;
    }

    if (value == 1 || value == 0)
    {
        printf("input value is not prime nor composite.");
        return 1;
    }

    else {
        int i, is_prime = 1;
        for (i = 2; i * i <= value; i += 1)
        {
            if (value % i == 0)
            {
                is_prime = 0;
                break;
            }
        }
        printf("value is %s", value == 1
            ? "composite"
            : "prime");

    }

    return 0;
}