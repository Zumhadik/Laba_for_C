/* Реализовать функцию быстрого возведения целого числа в целую неотрицательную
степень. Продемонстрировать работу функции. */

#pragma warning(disable: 4996)

#include <stdio.h>

int fast_power(int base, int exponent) {

	int res = 1;

	if (exponent == 0) {
		res = 1;
	}

	while (exponent) {
		if (exponent % 2 == 0) {
			exponent /= 2;
			base *= base;
		}
		else {
			--exponent;
			res *= base;
		}
	}

	return res;
}

int main() {

	int base, exp, result;
	char check;

	printf("Enter integer number: ");
	if (scanf("%d", &base) != 1 || (check = getchar()) != '\n' && check != ' ') {
		printf("Incorrect input.");
		return 1;
	}

	printf("Enter integer power: ");
	if (scanf("%d", &exp) != 1 || (check = getchar()) != '\n' && check != ' ') {
		printf("Incorrect input.");
		return 1;
	}

	else if (exp < 0) {
		printf("Incorrect input. Power is negative.");
	}

	result = fast_power(base, exp);

	printf("\nThe number %d to the power of %d is equal to %d.\n", base, exp, result);

	return 0;
}