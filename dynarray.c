#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *data;
    int capacity;
    int end;
    int element_width;
} Array;

typedef struct
{
    Array *arr;
    int current;
    int max;
} Iterator;

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
    return arr;
}

void *ArrayAt(Array *arr, int index)
{
    return arr->data + index * arr->element_width;
}

int Push(Array *arr, const void *item)
{
    arr->end++;
    if (arr->end == arr->capacity - 1)
    {
        arr->capacity *= 1.5;
        char *ptr = realloc(arr->data, (arr->capacity) * arr->element_width);
        if (!ptr)
        {
            printf("realloc failed");
            exit(1);
        }
        arr->data = ptr;
    }

    void *p = memcpy(ArrayAt(arr, arr->end),
                     item,
                     arr->element_width);

    if (p == NULL)
    {
        printf("memcpy failed");
        exit(1);
    }
    return 0;
}

Iterator CreateIterator(Array *array)
{
    Iterator it = {array, 0, array->end};
    return it;
}

int ArrayGet(Array *arr, int index, void *buff)
{
    if (index > arr->end)
    {
        return -1;
    }
    memcpy(buff, ArrayAt(arr, index), arr->element_width);
    return 0;
}

int ArraySet(Array *arr, int index, void *item)
{
    if (index > arr->end)
    {
        return -1;
    }
    void *p = memcpy(ArrayAt(arr, index),
                     item,
                     arr->element_width);

    if (p == NULL)
    {
        printf("memcpy failed");
        exit(1);
    }
    return 0;
}

int Next(Iterator *it, void *buff)
{
    if (it->max != it->arr->end)
    {
        printf("ERROR: Array length changed during iteration\n");
        exit(1);
    }
    if (it->current > it->max)
    {
        return 0;
    }
    int stat = ArrayGet(it->arr, it->current, buff);
    if (stat)
    {
        printf("Unable to get data from array");
        return 0;
    }
    it->current++;
    return 1;
}

int Pop(Array *arr, void *buff)
{

    if (arr->end == -1)
    {
        return -1;
    }
    if (buff)
    {
        int stat = ArrayGet(arr, arr->end, buff);
        if (stat)
        {
            printf("Unable to get data from array");
            return 0;
        }
    }
    arr->end--;
    return 0;
}
int Free(Array *arr)
{
    free(arr->data);
    arr->data = NULL;
    return 0;
}

int main()
{
    Array ar = CreateArray(10, sizeof(int));

    Array *arr = &ar;
    for (int i = 0; i < 10; ++i)
    {
        Push(arr, &i);
    }

    int g = 90;

    int ds = 1023;
    ArraySet(arr, 15, &ds);

    ArrayGet(arr, 15, &g);
    printf("%i\n", g);
    Iterator iter = CreateIterator(arr);
    Pop(arr, &g);
    int buff;
    printf("\n\n");
    while (Next(&iter, &buff))
    {
        printf("%d\n", buff);
    }
    Free(arr);
    return 0;
}