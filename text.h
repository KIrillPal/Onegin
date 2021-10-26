#pragma once
#include <stdio.h>
#include <wchar.h>

int  string_comp (const void * first, const void * second);
int wstring_comp (const void * first, const void * second);

wchar_t utf8_getwc(char ** utf8_text);

int seekFileSize (FILE * file);

wchar_t*  getText  (FILE * file, int * number_of_lines);
wchar_t** getLines (wchar_t* text, int number_of_lines);

int wstring_comp(const void* first, const void* second);