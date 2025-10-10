/* Заполнить массив фиксированного размера BUFSIZ псевдослучайными целыми числами в
диапазоне [-10000..10000]. Реализовать алгоритм поиска максимального и минимального
элементов массива, а также индексов этих элементов, за один проход по массиву. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

	int int_array[BUFSIZ];

	srand(time(NULL));

	int i;
	for (i = 0; i < BUFSIZ; i++)
	{
		int_array[i] = (rand() % 20001) - 10000;
	}

	int min_value = int_array[0];
	int max_value = int_array[0];
	int min_index, max_index;

	for (i = 1; i < BUFSIZ; i++)
	{
		if (int_array[i] < min_value) {
			min_value = int_array[i];
			min_index = i;
		}
		if (int_array[i] > max_value) {
			max_value = int_array[i];
			max_index = i;
		}
	}

	printf("Minimum value of array: %d index: %d", min_value, min_index);
	printf("\nMaximum value of array: %d index: %d", max_value, max_index);

	return 0;
}