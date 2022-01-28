#ifndef _STRING_LIST_H
#define _STRING_LIST_H

#include "list.h"

typedef struct _StringListEntry {
    _ListEntry listEntry;
    char* value;
}StringListEntry;

StringListEntry* CreateAndInitNewStringListEntry(StringListEntry* entry, char* str);
void FreeStringListEntry(StringListEntry* entry);
void AddStringTailStringList(StringListEntry** stringList, char* str);
void FreeStringList(StringListEntry** stringList);
void GenerateRandomStringList(StringListEntry** stringList, unsigned int max_size);
void PrintListEntry(StringListEntry* listEntry);

#endif //_STRING_LIST_H
