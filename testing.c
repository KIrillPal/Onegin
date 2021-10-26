#include <stdlib.h>
#include "sorting.h"
#include "text.h"
#include "testing.h"

static int test(int count, int minline, int maxline, int show_log)
{
	char** lines     = (char**)calloc(count, sizeof(char*));
	char** lines_ref = (char**)calloc(count, sizeof(char*));
	
    if (show_log == SHOW_LOG)
        printf("Input %d values:\n", count);

	int i, j;
	for (i = 0; i < count; ++i)
	{
		int length = rand() % (maxline - minline + 1) + minline;
		lines[i]     = (char*)calloc(length + 1, sizeof(char));
		lines_ref[i] = (char*)calloc(length + 1, sizeof(char));

		for (j = 0; j < length; ++j)
		{
			lines[i][j] = rand() % 27 + 'a';
			lines_ref[i][j] = lines[i][j];
		}
        if (show_log == SHOW_LOG)
            printf("%d. \"%s\"\n", i, lines[i]);
	}

	printf("Sorting %d items with length [%d, %d]: ", count, minline, maxline);

    if (show_log != SKIP)
    {
        qsort_(lines, count, sizeof(char*), string_comp);
        qsort(lines_ref, count, sizeof(char*), string_comp);
    }

    if (show_log == SHOW_LOG)
    {
        printf("Output %d values:\n", count);

        for (i = 0; i < count; ++i)
            printf("%d. \"%s\"\n", i, lines[i]);
    }

	for (i = 0; i < count; ++i)
	{
		if (string_comp(&lines[i], &lines_ref[i]) != 0)
		{
			printf("Error %d item: \"%s\" ref: \"%s\"\n", i, lines[i], lines_ref[i]);
			return 0;
		}
		free(lines[i]);
		free(lines_ref[i]);
	}
	printf(show_log == SKIP ? "SKIP\n" : "OK\n");

	free(lines);
	free(lines_ref);

	return 1;
}

int qsortTest(int seed)
{
	srand(seed);
	int is_correct = 1;

	int i;
    for (i = 0; i < 20; ++i)
        is_correct &= test(5, 0, 3, HIDE_LOG);

    for (i = 0; i < 10; ++i)
        is_correct &= test(10, 0, 10, HIDE_LOG);


    for (i = 0; i < 10; ++i)
        is_correct &= test(30, 0, 100, HIDE_LOG);

    for (i = 0; i < 100; ++i)
        is_correct &= test(1000, 0, 10, HIDE_LOG);

    for (i = 0; i < 100; ++i)
        is_correct &= test(1000, 0, 1000, HIDE_LOG);

    for (i = 0; i < 100; ++i)
        is_correct &= test(10000, 0, 30, HIDE_LOG);

	return is_correct;
}
