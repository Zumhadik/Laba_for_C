#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

int compar(char* first_str, char* second_str) {

    int result = 0;

    while (*first_str == *second_str && *first_str != '\0') {
        first_str++;
        second_str++;
    }

    if (*first_str == '\0' && *second_str == '\0') {
        return 0;
    }

    if (*first_str > *second_str) {
        return 1;
    }
    else {
        return -1;
    }
}

int main() {

    char str1[BUFSIZ];
    char str2[BUFSIZ];
    int result;

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    result = compar(str1, str2);

    switch (result) {
    case 0:
        printf("Strings are equal.");
        break;
    case 1:
        printf("First string is longer than second string.");
        break;
    case -1:
        printf("Second string is longer than first string.");
        break;
    }

    return 0;
}