#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "string_list.h"

static bool IsEmptyStringList(StringListEntry* list_entry)
{
    return list_entry->value == NULL;
}

StringListEntry* CreateAndInitNewStringListEntry(StringListEntry* entry, char* str)
{
    entry = (StringListEntry*)InitList(sizeof(StringListEntry));
    
    if (entry == NULL) {
        printf("CreateAndInitNewStringListEntry(): error");
        exit(EXIT_FAILURE);
    }

    entry->value = _strdup(str);

    return entry;
}

void FreeStringListEntry(StringListEntry* entry) 
{
    free(entry->value);
    free(entry);

    return 0;
}

void AddStringTailStringList(StringListEntry** stringList, char* str) 
{
    if ((*stringList) == NULL)
        (*stringList) = CreateAndInitNewStringListEntry(str, (*stringList));
    else {
        StringListEntry* tmp = (StringListEntry*)InsertList((_ListEntry*)(*stringList));

        if (tmp == NULL) {
            printf("AddStringTailStringList(): error");
            exit(EXIT_FAILURE);
        }

        tmp->value = str;
    }
}

void FreeStringList(StringListEntry** stringList)
{
    while (IsEmptyStringList((*stringList)))
        FreeStringListEntry(*stringList);
    free((*stringList));
    (*stringList) = NULL;
}

void GenerateRandomStringList(StringListEntry** stringList, unsigned int max_size)
{
    int size = 1 + rand() / (RAND_MAX / (max_size - 1 + 1) + 1);

    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int sizeAlphabet = (int)(sizeof(alphabet) - 1);

    char* str = (char*)malloc(size * sizeof(char) + 1);

    if (str == NULL)
    {
        printf("GenerateRandomStringList(): error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; ++i)
    {
        str[i] = alphabet[rand() % sizeAlphabet];
    }

    str[size] = 0;

    AddStringTailStringList(stringList, str);
}

void PrintListEntry(StringListEntry* listEntry)
{
    StringListEntry* tmp = listEntry;
    while (tmp) {
        printf("%s\n", tmp->value);
        tmp = (StringListEntry*)tmp->listEntry.next;
    }
}
