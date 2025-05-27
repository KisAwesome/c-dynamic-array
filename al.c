#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *data;
    int capacity;
    int end;
    int element_width;
} Array;



Array CreateArray(int n, int width)
{
    char *ptr = NULL;
    ptr = calloc(n, width);

    if (ptr == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }

    Array arr = {ptr, n, -1, width};
    return &arr;
}



int main(){
}