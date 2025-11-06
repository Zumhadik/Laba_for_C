#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-10

void bubble_sort(double arr[], const size_t n) {
    size_t i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                double t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

void calc_numb(
    double* arithmetic,
    double* geometric,
    double* harmonic,
    double* median,
    size_t count, ...) {

    if (count == 0) {
        printf("[ERROR] - Count must be greater than zero.");
        return;
    }

    size_t i;
    double sum = 0.0;
    double product = 1.0;
    double harmon = 0.0;
    const double one = 1.0;

    va_list args;
    va_start(args, count);

    double* values = (double*)malloc(sizeof(double) * count);
    if (values == NULL) {
        printf("[ERROR] - Memory allocation failed.");
        va_end(args);
        return;
    }

    for (i = 0; i < count; i++) {
        values[i] = va_arg(args, double);

        if (fabs(values[i]) < EPSILON) {
            printf("[ERROR] - Some value is zero.");
            free(values);
            va_end(args);
            return;
        }
        
        sum += values[i];
        product *= values[i];
        harmon += one / values[i];
    }

    va_end(args);

    *arithmetic = sum / count;
    *geometric = pow(product, 1.0 / (double)count);
    *harmonic = (double)count / harmon;

    bubble_sort(values, count);
    if (count % 2 == 0) {
        *median = (values[count / 2 - 1] + values[count / 2]) / 2.0;
    }
    else {
        *median = values[count / 2];
    }

    free(values);
}

int main()
{
    double arithmetic, geometric, harmonic, median;

    calc_numb(&arithmetic, &geometric, &harmonic, &median, 4, 1.0, 16.0, 81.0, 256.0);

    printf("\n[Results]\n\n"
        "Arithemic mean     : %lf\n"
        "Geometric mean     : %lf\n"
        "Harmonic mean      : %lf\n"
        "Median             : %lf\n",
        arithmetic, geometric, harmonic, median);
    return 0;
}