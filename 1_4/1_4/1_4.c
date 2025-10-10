/* –еализовать функцию, мен€ющую местами значени€ двух чисел типа int. ¬ходными
параметрами функции €вл€ютс€ указатели типа int *. ѕродемонстрировать работу
функции. */

#pragma warning(disable: 4996)

#include <stdio.h>

void swap_values(int *firstv, int *secondv) {
	int temp_value = *firstv;
	*firstv = *secondv;
	*secondv = temp_value;
}

int main() {

	int val_1, val_2;
	char check;

	printf("Enter 2 integers values: ");
	if (scanf("%d%d", &val_1, &val_2) != 2 || (check = getchar()) != '\n' && check != ' ') {
		printf("Incorrect input.");
		return 1;
	}

	printf("\nFirst value: %d"
		"\nSecond value: %d", val_1, val_2);

	swap_values(&val_1, &val_2);

	printf("\n\nValues were swapped.\n");

	printf("\nFirst value: %d"
		"\nSecond value: %d", val_1, val_2);
	
	return 0;
}