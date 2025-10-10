/* Реализовать функцию, которая принимает в качестве параметра строку и поднимает 
регистр всех гласных букв, находящихся на чётных позициях, а также опускает регистр 
всех согласных букв, находящихся на позициях, номера которых являются простыми 
числами (используйте функционал из задания 2). Продемонстрировать работу функции.*/

#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

int ToUpperCase(char uLetter) {

	if (uLetter >= 'a' && uLetter <= 'z') {
		uLetter -= 32;
	}

	return uLetter;
}

int ToLowerCase(char lLetter) {
	if (lLetter >= 'A' && lLetter <= 'Z') {
		lLetter += 32;
	}

	return lLetter;
}

int is_vowel(char req_let) {

	int j;
	char vowels[12] = { 'A', 'U', 'E', 'Y', 'I', 'O', 'a', 'u', 'e', 'y', 'i', 'o' };

	for (j = 0; j < 12; j++) {
		if (vowels[j] == req_let) {
			return 1;
		}
	}
	return 0;
}

int is_prime(int num) {

	int k;

	if (num <= 1) {
		return 0;
	}

	for (k = 2; k * k <= num; k += 1) {
		if (num % k == 0) {
			return 0;
		}
	}

	return 1;
}

int main() {

	char str[BUFSIZ] = { 0 };
	int sizeArr, i;

	printf("Enter your string: ");
	scanf("%s", str);

	sizeArr = strlen(str);

	for (i = 0; i < sizeArr; i++) {

		if (is_vowel(str[i]) == 1 && i % 2 == 0) {
			str[i] = ToUpperCase(str[i]);
		} 
		else if (is_vowel(str[i]) == 0 && is_prime(i) == 1) {
			str[i] = ToLowerCase(str[i]);
		}

	}

	printf("\nNew string: %s", str);

	return 0;
}