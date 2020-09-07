#include "header.h"

void element_swap(int *first, int *second)
{
        int temp = *first;
        *first = *second;
        *second = temp;
}

void read_array (int *array, int len)
{
        printf("\nEnter elements of the array. \n");
        for(int i = 0; i < len; i++) {
                scanf("%d", (array+i));
        }
}

void reverse_array (int *array, int len)
{
        for(int i = 0; i < (len/2); i++){
                element_swap(array+i, array+(len-i-1));
        }     
}

void print_array (int *array, int len)
{
        printf("\n");
        for(int i = 0; i < len; i++) {
                printf("%d\t", array[i]);
        }
        printf("\n");
}