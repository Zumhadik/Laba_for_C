/* Реализовать функцию, строящую таблицу степеней (от 1 до 10) натуральных чисел от 1 до
6. При вычислениях запрещается использовать функции для возведения в степень (pow и
др.). Продемонстрировать работу функции. */

#include <stdio.h>

int power_table(int base, int exponent) {

    int result = 1, i;

    for (i = 1; i <= exponent; i++) {
        result *= base;
    }

    return result;
}

int main() {

    int base, exp;

    for (base = 1; base <= 6; base++) {
        for (exp = 1; exp <= 10; exp++) {
            printf("%d ", power_table(base, exp));
        }
        printf("\n");
    }

    return 0;
}