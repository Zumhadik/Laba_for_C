#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void bubble_sort(void* base, size_t length, size_t sizebyte, int (*comparator)(const void*, const void*)) {

    size_t i, j, k;
    char* array = (char*)base;

    if (length <= 1) {
        return;
    }

    for (i = 0; i < length - 1; i++) {
        int swapped = 0;
        for (j = 0; j < length - i - 1; j++) {
            void* a = (void*)(array + j * sizebyte);
            void* b = (void*)(array + (j + 1) * sizebyte);

            if (comparator(a, b) > 0) {
                char temp;
                for (k = 0; k < sizebyte; k++) {
                    temp = ((char*)a)[k];
                    ((char*)a)[k] = ((char*)b)[k];
                    ((char*)b)[k] = temp;
                }
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}

void selection_sort(void* base, size_t length, size_t sizebyte, int (*comparator)(const void*, const void*)) {

    size_t i, j, k;
    char* array = (char*)base;

    if (length <= 1) {
        return;
    }

    for (i = 0; i < length - 1; i++) {
        size_t min_idx = i;

        for (j = i + 1; j < length; j++) {
            void* current = (void*)(array + j * sizebyte);
            void* min_ptr = (void*)(array + min_idx * sizebyte);
            if (comparator(min_ptr, current) > 0) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            void* a = (void*)(array + i * sizebyte);
            void* b = (void*)(array + min_idx * sizebyte);
            char temp;
            for (k = 0; k < sizebyte; k++) {
                temp = ((char*)a)[k];
                ((char*)a)[k] = ((char*)b)[k];
                ((char*)b)[k] = temp;
            }
        }
    }
}

void insertion_sort(void* base, size_t length, size_t sizebyte, int (*comparator)(const void*, const void*)) {

    size_t i, j, k;
    char* array = (char*)base;

    if (length <= 1) {
        return;
    }

    for (i = 1; i < length; i++) {
        void* key_ptr = (void*)(array + i * sizebyte);
        for (j = i; j > 0; j--) {
            void* prev_ptr = (void*)(array + (j - 1) * sizebyte);
            if (comparator(prev_ptr, key_ptr) <= 0) {
                break;
            }
            void* a = (void*)(array + (j - 1) * sizebyte);
            void* b = (void*)(array + j * sizebyte);
            char temp;
            for (k = 0; k < sizebyte; k++) {
                temp = ((char*)a)[k];
                ((char*)a)[k] = ((char*)b)[k];
                ((char*)b)[k] = temp;
            }
        }
    }
}

int main(void) {

    int values[SIZE], i;

    srand(time(NULL));

    for (i = 0; i < SIZE; i++) {
        values[i] = rand() % 101;
    }

    size_t length = sizeof(values) / sizeof(values[0]);

    printf("Array without sorted values: ");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", values[i]);
    }

    bubble_sort(values, length, sizeof(int), cmp);

    printf("\n\nArray with sorted values(bubble sort): ");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", values[i]);
    }

    selection_sort(values, length, sizeof(int), cmp);

    printf("\n\nArray with sorted values(selection sort): ");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", values[i]);
    }

    insertion_sort(values, length, sizeof(int), cmp);

    printf("\n\nArray with sorted values(insertion sort): ");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", values[i]);
    }

    return 0;
}