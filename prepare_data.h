#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

int safeFileSize (FILE * file);
int fastFileSize (FILE * file);

wchar_t*  getText  (FILE * file, int * number_of_lines);
wchar_t** getLines (wchar_t* text, int number_of_lines);

int wstring_comp(const void* first, const void* second);

