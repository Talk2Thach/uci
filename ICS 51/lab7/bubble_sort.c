/*
 * Author      : Edward Xia
 * Description : Lab 7 - Bubble Sort
 * Date        : 05/11/2015
 */

#include <stdio.h>

#define ARRAY_LENGTH 20

int main()
{
    int array[ARRAY_LENGTH];
    int i;
    int swapped;

    printf("Enter the elements one by one \n");
    for (i = 0; i < ARRAY_LENGTH; i++)
    {
        scanf("%d", &array[i]);
    }

    printf("Input array elements \n");
    for (i = 0; i < ARRAY_LENGTH ; i++)
    {
        printf("%d\n", array[i]);
    }

    /*  Bubble sorting begins */
    do
    {
        swapped = 0;
        /*
        for (i = 1; i < ARRAY_LENGTH; i++)
        {
            if (array[i] < array [i-1])
            {
                swapped = 1;
                int temp = array [i-1];
                array [i-1] = array [i];
                array[i] = temp;
            }
        }
        */
        __asm__ __volatile__(
            "lea rcx, [rbx + 4 * rax];"
            "FOR:"
            "add rbx, 4;"
            "cmp rbx, rcx;"
            "jl CONTINUE;"
            "jmp DONE;"
            "CONTINUE:"
            "mov edi, dword ptr [rbx];"
            "mov esi, dword ptr [rbx - 4];"
            "cmp edi, esi;"
            "jl THEN;"
            "jmp FI;"
            "THEN:"
            "mov %0, 1;"
            "mov dword ptr [rbx], esi;"
            "mov dword ptr [rbx - 4], edi;"
            "FI:"
            "jmp FOR;"
            "DONE:"
            :"+r" (swapped)                  //don't touch this line
            :"b" (array), "a" (ARRAY_LENGTH) //don't touch this line
            :"memory"                        //include other clobbered regs
        );

    } while (swapped > 0);

    printf("Sorted array is...\n");
    for (i = 0; i < ARRAY_LENGTH; i++)
    {
        printf("%d\n", array[i]);
    }

    return 0;
}
