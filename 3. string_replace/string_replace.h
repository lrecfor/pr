#ifndef _STRING_REPLACE_H
#define _STRING_REPLACE_H

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 512

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void CheckingArgs(int argc, char** argv);
char* ReadFromFile(char* filename, char* string);
char* CopyString(const char* current);
char* ReplaceString(char* original, const char* _template, const char* replacement);
static char* StringFinding(const char* str, const char* repl);

#endif // _STRING_REPLACE_H