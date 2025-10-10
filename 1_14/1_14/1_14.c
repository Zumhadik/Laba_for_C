#pragma warning(disable: 4996)

#include <stdio.h>

int main(void) {

    FILE* input;

    char const* const filePath = "C:\\Users\\Zumhad\\Desktop\\kaka.txt";

    input = fopen(filePath, "r");

    if (input == NULL)
    {
        printf("File is not opened!");
        return -1;
    }

    fclose(input);
    
    return 0;
}