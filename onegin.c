#include <string.h>
#include <locale.h>
#include "comparators.h"
#include "qsort.h"
#include "testing.h"
#include "prepare_data.h"

//#define TESTING

int main()
{
#ifndef TESTING

    setlocale(LC_ALL, "");
    fwide(stdout, 1);

    int nlines = 0;
    wchar_t * file_text = getText(stdin, &nlines);

    if (!file_text)
    {
        wprintf(L"Cannot read input stream!\n");
        return 0;
    }

    wchar_t ** lines = getLines(file_text, nlines);

    qsort_(lines, nlines, sizeof(wchar_t*), wstring_comp);

    int i;
    for (i = 0; i < nlines; ++i)
        wprintf(L"%ls\n", lines[i]);

    free(file_text);
    free(lines);

#else

    int is_success = qsortTest(0);
    printf("Exit success: %d\n", is_success);

#endif // TESTING
}
