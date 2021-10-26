#include <stdlib.h>
#include "text.h"

int wstring_comp (const void* first, const void* second)
{
    wchar_t* first_  = *(wchar_t**)first;
    wchar_t* second_ = *(wchar_t**)second;

    do
    {
        if (*first_ != *second_)
        {
            int res = 1 - 2 * (*first_ < *second_);
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
            return res;
        }

    } while (*first_++ && *second_++);

    return 0;
}

int seekFileSize (FILE * file)
{
    fseek(file, 1L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return length - 1;
}

wchar_t utf8_getwc(char ** utf8_text)
{
    const char BYTE2_MASK = 0xC0;
    const char BYTE3_MASK = 0xE0;
    const char BYTE4_MASK = 0xF0;
    const char NEXTB_MASK = 0x3F;

    char * text = *utf8_text;
    int byte_len = 1;

    wchar_t res = 0;

    if ((*text & BYTE4_MASK) == BYTE4_MASK)
    {
        byte_len = 4;
        res += *text++ & (~BYTE4_MASK);
    }
    else if ((*text & BYTE3_MASK) == BYTE3_MASK)
    {
        byte_len = 3;
        res += *text++ & (~BYTE3_MASK);
    }
    else if ((*text & BYTE2_MASK) == BYTE2_MASK)
    {
        byte_len = 2;
        res += *text++ & (~BYTE2_MASK);
    }
    else
    {
        res = *text++;
        *utf8_text = text;
        return res;
    }

    while (byte_len > 1)
    {
        res = 64 * res + (*text & NEXTB_MASK);
        text++, byte_len--;
    }

    *utf8_text = text;
    return res;
}

wchar_t* getText (FILE * file, int * nlines)
{

    if (file == NULL)
        return NULL;

    int size, lines = 0;

    size = seekFileSize(file);

    char    * raw_text = (char*)calloc(size, 1);
    wchar_t * wch_text = (wchar_t*)calloc(size, sizeof(wchar_t));
    if (!raw_text || !wch_text)
    {
        wprintf(L"Reading error: couldn't allocate memory\n");
        free(raw_text);
        free(wch_text);
        return NULL;
    }

    if (fread(raw_text, 1, size, stdin) != size)
    {
        wprintf(L"Reading error: couldn't read input\n");
        free(raw_text);
        free(wch_text);
        return NULL;
    }

    char * raw_p = raw_text;
    for (int i = 0; raw_p != (raw_text + size); i++)
    {
        wch_text[i] = utf8_getwc(&raw_p);
        if (wch_text[i] == L'\n')
            lines++;
    }

    *nlines = lines + 1;

    free(raw_text);
    return wch_text;
}

wchar_t** getLines (wchar_t* text, int nlines)
{
    wchar_t ** lines = (wchar_t**)calloc(nlines, sizeof(wchar_t*));

    if (!lines)
    {
        wprintf(L"Lining error: couldn't allocate memory\n");
        return NULL;
    }

    wchar_t ** lines_p = lines;
    *lines_p++ = text;

    for (; *text != L'\0'; text++)
    {
        if (*text == L'\n')
        {
            *text = L'\0';
            *lines_p++ = text + 1;
        }
    }

    return lines;
}
