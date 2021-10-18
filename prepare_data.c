#include "prepare_data.h"

//#define ON_DEBUG

int fastFileSize (FILE * file)
{
    fseek(file, 1L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return length;
}

wchar_t* getText (FILE * file, int * nlines)
{

    if (file == NULL)
        return NULL;

    int size, lines = 0;

    size = fastFileSize(file);

#ifdef ON_DEBUG
    wprintf(L"File size < %d\n", size);
#endif

    wchar_t * text = (wchar_t*)calloc(size, sizeof(wchar_t));
    wchar_t * text_p = text;

    while ((*text_p = fgetwc(file)) != WEOF)
    {
#ifdef ON_DEBUG
        wprintf(L"Raw: %d\n", *text_p);
#endif
        if (*text_p == L'\n')
            lines++;
        text_p++;
    }

    *text_p = L'\0';
    *nlines = lines + 1;

    return text;
}

wchar_t** getLines (wchar_t* text, int nlines)
{
    wchar_t ** lines = (wchar_t**)calloc(nlines, sizeof(wchar_t*));
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
