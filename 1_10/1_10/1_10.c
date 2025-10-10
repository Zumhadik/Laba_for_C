#pragma warning(disable: 4996)

#include <stdio.h>
#include <string.h>

void concat(char* first_str, char* second_str) {

    int len_str1 = strlen(first_str);
    int len_str2 = strlen(second_str);
    int i;

    for (i = 0; i < len_str2; i++) {
        first_str[len_str1 + i] = second_str[i];
    }

    first_str[len_str1 + len_str2] = '\0';

}

int main() {

    char str1[BUFSIZ];
    char str2[BUFSIZ];

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    concat(str1, str2);

    printf("String after concatenation: %s", str1);

    return 0;
}