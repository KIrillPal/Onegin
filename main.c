#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "sorting.h"
#include "testing.h"
#include "text.h"

#define OK     0;
#define ERROR -1;

struct LinedText {
    wchar_t *  text  = NULL;
    wchar_t ** lines = NULL;
    int nlines = 0;
};

int init_text(LinedText * text)
{
    text->text = getText(stdin, &text->nlines);
    if (!text->text)
        return ERROR;

    text->lines = getLines(text->text, text->nlines);
    if (!text->lines)
        return ERROR;

    return OK;
}

void sort_text(LinedText * text)
{
    qsort_(text->lines, text->nlines, sizeof(wchar_t*), wstring_comp);
}

void print_text(LinedText * text)
{
    for (int i = 0; i < text->nlines; ++i)
        wprintf(L"%ls\n", text->lines[i]);
}

void destroy_text(LinedText * text)
{
    free(text->text);
    free(text->lines);
}

int main()
{
#ifndef TESTING

    setlocale(LC_ALL, "");
    fwide(stdout, 1);

    LinedText text;

    if (init_text(&text))
    {
        wprintf(L"Program failed!\n");
        return 0;
    }
    sort_text    (&text);
    print_text   (&text);
    destroy_text (&text);

#else

    int is_success = qsortTest(0);
    printf("Exit success: %d\n", is_success);

#endif // TESTING
    return 0;
}
