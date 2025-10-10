/* Реализовать приложение, запрашивающее у пользователя три целых неотрицательных
числа и проверяющее, могут ли эти три числа являться: a) сторонами треугольника; b)
сторонами прямоугольного треугольника; c) элементами арифметической прогрессии; d)
элементами геометрической прогрессии; e) элементами последовательности Фибоначчи; f)
подряд идущими элементами последовательности Фибоначчи. */

#pragma warning(disable: 4996)

#include <stdio.h>

int fib(int num)
{
    int a = 0, b = 1;
    while (b < num) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b == num;
}

int main()
{
    int value1, value2, value3;

    printf("Enter 3 integer numbers: ");

    if (scanf("%d%d%d", &value1, &value2, &value3) != 3) {
        printf("\nerror input, try again, 3 integer numbers!");
        return 1;
    }

    if (value1 < 0 || value2 < 0 || value3 < 0) {
        printf("\nsome number is negative, try again.");
        return 1;
    }

    if (value1 + value2 <= value3 ||
        value1 + value3 <= value2 ||
        value2 + value3 <= value1) {
        printf("\nvalues cannot form a triangle.\n");
    }
    else {
        printf("\nvalues form a triangle.\n");
    }

    if (value1 * value1 + value2 * value2 == value3 * value3 ||
        value1 * value1 + value3 * value3 == value2 * value2 ||
        value2 * value2 + value3 * value3 == value1 * value1) {
        printf("values form a right triangle.\n");
    }
    else {
        printf("values cannot form a right triangle.\n");
    }

    if (
        value2 - value1 == value3 - value2 ||
        value3 - value1 == value2 - value3 ||
        value1 - value2 == value3 - value1 ||
        value3 - value2 == value1 - value3 ||
        value1 - value3 == value2 - value1 ||
        value2 - value3 == value1 - value2
        )

    {
        printf("values form an arithmetic progression.\n");
    }
    else {
        printf("values do not form an arithmetic progression.\n");
    }

    if (
        value2 * value2 == value1 * value3 ||
        value3 * value3 == value1 * value2 ||
        value1 * value1 == value2 * value3
        )

    {
        printf("values form an geometric progression.\n");
    }
    else {
        printf("values do not form an geometric progression.\n");
    }

    int result1 = fib(value1);
    int result2 = fib(value2);
    int result3 = fib(value3);

    if (result1 && result2 && result3) {
        printf("values are elements of the Fibonacci sequence.\n");
    }
    else {
        printf("values are not elements of the Fibonacci sequence.\n");
    }

    if (
        value1 + value2 == value3 ||
        value2 + value3 == value1 ||
        value1 + value3 == value2
        )
    {
        printf("values belong to consecutive elements of the Fibonacci sequence.\n");
    }
    else 
    {
        printf("values do not belong to consecutive elements of the Fibonacci sequence.\n");
    }

    return 0;
}