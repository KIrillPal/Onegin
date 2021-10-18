#include <stdio.h>
#include <wchar.h>

//#define ON_DEBUG

int wstring_comp (const void* first, const void* second)
{
    wchar_t* first_  = *(wchar_t**)first;
    wchar_t* second_ = *(wchar_t**)second;

    do
    {
        if (*first_ != *second_)
        {
            int res = 1 - 2 * (*first_ < *second_);

#ifdef ON_DEBUG
            wprintf(L"\"%ls\" %lc \"%ls\"\n", first_, (res < 0 ? '<' : '>'), second_);
#endif

            return res;
        }

    } while (*first_++ && *second_++);

    return 0;
}

int string_comp (const void* first, const void* second)
{
    char* first_  = *(char**)first;
    char* second_ = *(char**)second;

    do
    {
        if (*first_ != *second_)
        {
            int res = 1 - 2 * (*first_ < *second_);

#ifdef ON_DEBUG
            printf("\"%s\" %c \"%s\"\n", first_, (res < 0 ? '<' : '>'), second_);
#endif

            return res;
        }

    } while (*first_++ && *second_++);

    return 0;
}

