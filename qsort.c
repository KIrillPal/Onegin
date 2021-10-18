#include "qsort.h"

//#define ON_DEBUG

#define MOVE(data, index, size) data = (char*)data + size * index;

#define SWAP(first, second, size)      \
{                                      \
    char* first_byte =  (char*)first;  \
    char* second_byte = (char*)second; \
                                       \
    int i;                             \
    for (i = 0; i < size; i++)         \
    {                                  \
        char temp = *first_byte;       \
        *first_byte = *second_byte;    \
        *second_byte = temp;           \
                                       \
        first_byte++;                  \
        second_byte++;                 \
    }                                    \
}

#define RELAX(first, second, size) if (comparator(first, second) > 0) SWAP(first, second, size)

void qsort_ (void* data, size_t number, size_t size, int(*comparator)(const void*, const void*))
{
    if (number <= 1)
        return;

    void* lhs = data;
    void* mid = (char*)data + size * (number / 2);
    void* rhs = (char*)data + size * (number - 1);


    RELAX(lhs, mid, size);
    RELAX(mid, rhs, size);
    RELAX(lhs, mid, size);



#ifdef ON_DEBUG
    printf("Mid: %s\n", *(char**)mid);
#endif

    while (lhs <= rhs)
    {
        while (comparator(lhs, mid) < 0)
            MOVE(lhs, 1, size);

        while (comparator(rhs, mid) > 0)
            MOVE(rhs, -1, size);

        if (lhs < rhs)
        {
            SWAP(lhs, rhs, size);

            if (mid == lhs)
                mid = rhs;
            else if (mid == rhs)
                mid = lhs;

            MOVE(lhs, 1, size);
            MOVE(rhs, -1, size);
        }
        else if (lhs == rhs)
            break;
    }

#ifdef ON_DEBUG
    printf("After sort [%d, %d]:\n", data, number);

    void * pp = data;
    int i;
    for (i = 0; i < number; ++i)
    {
        printf("%d. \"%s\"\n", i, *(char**)pp);
        MOVE(pp, 1, size);
    }

    printf("lhs: %d rhs: %d\n", ((char*)lhs - (char*)data) / size, ((char*)rhs - (char*)data) / size);
#endif

    size_t left_number = ((char*)lhs - (char*)data) / size;
    qsort_(data, left_number, size, comparator);
    qsort_(lhs, number - left_number, size, comparator);
}
/*
5
fpn
j
scp
hki
wui
*/


