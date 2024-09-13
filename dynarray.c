#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vector
{
    char *data;
    int size;
    int end;
    int element_width;
};

typedef struct Vector Array;

struct _Iterator
{
    int current;
    Array *arr;
    int max;
};

typedef struct _Iterator Iterator;

Array CreateVector(int n, int width)
{
    char *ptr = NULL;
    ptr = calloc(n, width);

    if (ptr == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }

    Array arr;
    arr.data = ptr;
    arr.size = n;
    arr.end = -1;
    arr.element_width = width;
    return arr;
}

void *ArrayAt(Array *vector, int index)
{
    return vector->data + index * vector->element_width;
}

int Push(const void *item, Array *arr)
{
    arr->end++;
    if (arr->end == arr->size - 1)
    {
        void *ptr = realloc(arr->data, (arr->size + 10) * arr->element_width);
        arr->size += 10;
        if (!ptr)
        {
            printf("realloc failed");
            exit(1);
        }
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
    Iterator it;
    it.arr = array;
    it.current = 0;
    it.max = array->end;
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

int Next(Iterator *it, void *buff)
{
    if (it->current > it->max)
    {
        return 0;
    }

    // *buff= it->data[it->current];
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
    return 0;
}

int main()
{
    Array arr = CreateVector(1, sizeof(int));

    for (int i = 0; i < 20; ++i)
    {
        Push(&i, &arr);
    }

    int g;
    
    ArrayGet(&arr,15,&g);
    printf("%i\n", g);

    Iterator iter;
    // int v;

    // Pop(&arr, NULL);
    //     Pop(&arr, NULL);
    int v;
    // Pop(&arr, NULL);
    // Pop(&arr, NULL);
    Pop(&arr, &v);
    printf("%i\n", v);

    iter = CreateIterator(&arr);
    int buff;

    while (Next(&iter, &buff))
    {
        printf("%d\n", buff);
    }

    Free(&arr);
    return 0;
}