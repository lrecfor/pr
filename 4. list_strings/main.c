#define MAX_STRING_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "string_list.h"
#include "sort_entry.h"

int CompareByLength(const void* node_1, const void* node_2)
{
    StringListEntry* first = (StringListEntry*)node_1;
    StringListEntry* second = (StringListEntry*)node_2;

    unsigned long left = strlen(first->value);
    unsigned long right = strlen(second->value);

    if (left > right)
        return 1;
    else if (right > left)
        return -1;
    else
        return 0;
}

int compareByAlphabetDescendingNoReg(const void* node_1, const void* node_2)
{
    StringListEntry* first = (StringListEntry*)node_1;
    StringListEntry* second = (StringListEntry*)node_2;

    return _stricmp(first->value, second->value);
}

int main()
{
    srand((unsigned int)time(NULL));

    StringListEntry* stringList = NULL;
    stringList = CreateAndInitNewStringListEntry(stringList, "string");
    AddStringTailStringList(&stringList, "string2");
    AddStringTailStringList(&stringList, "string3");
    AddStringTailStringList(&stringList, "string4");
    for (int i = 0; i < 10; ++i) {
        GenerateRandomStringList(&stringList, MAX_STRING_SIZE);
    }
    PrintListEntry(stringList);
    stringList = QuickSort((_ListEntry*)stringList, CompareByLength);
    printf("--------sorting--------\n");
    PrintListEntry(stringList);
    FreeStringList(&stringList);
    return 0;
}

/*1. Реализовать быструю сортировку строк, хранящихся в двусвязном списке.
Двусвязный список следует организовать через структуру ListEntry
(хранящую ссылки на два соседних элемента), с помощью которой можно организовать
список любых сущностей, не изменяя код работы со списком. Эта структура включается
в структуру с полезными данными. Всё логика работы со списком реализуется на уровне
структур ListEntry (а не объемлющей структуры).
"Поменять местами два элемента" в сортируемом контейнере для списка должно означать
изменение ссылок между элементами (а не смену полезных данных элементов)*/