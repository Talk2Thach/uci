/*
 * Author      : Edward Xia
 * Description : Lab 5 - Selection Sort
 * Date        : 04/27/2015
 */

#include <stdio.h>

#define n 20
int findmin(int b[n], int i, int j);

int main() {
    int array[n];
    int i;

    printf("Enter the elements one by one \n");
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }

    printf("Input array elements \n");
    for (i = 0; i < n ; i++) {
        printf("%d\n", array[i]);
    }

    /*  Selection sorting begins */
    int a, min;
    for (a = 0; a < n; a++) {
        min = findmin(array, a, n-1);

        __asm__ __volatile__(
            "xor %0, %1;"
            "xor %1, %0;"
            "xor %0, %1;"
            :"+r" (array[a]), "+r" (array[min])
        );
    }

    printf("Sorted array is...\n");
    for (i = 0; i < n; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
/*  function to find the index to the minimum value */
int findmin(int b[n], int i, int j) {
    int min = i, k;
    for (k = i; k <= j; k++) {
        if (b[min] > b[k]) {
            min = k;
        }
    }
    return min;
}
