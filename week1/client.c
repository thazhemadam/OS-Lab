#include "header.h"

int main(void)
{
        int len, *array;        
        printf("\nEnter size of the array: ");
        scanf("%d", &len);        
        read_array(array, len);
        print_array(array, len);
        reverse_array(array, len);
        print_array(array, len);
        return 0;
}