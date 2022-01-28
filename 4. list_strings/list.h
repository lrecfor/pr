#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

typedef struct _ListEntry _ListEntry;

typedef struct {
    _ListEntry* head;
    _ListEntry* tail;
    size_t size;
} _List;

struct _ListEntry {
    _ListEntry* next;
    _ListEntry* prev;
    _List* _list;
};

_ListEntry* InitList(size_t size);
_ListEntry* InsertList(_ListEntry* newEntry);
void PopBack(_ListEntry* tail);
void RemoveEntry(_ListEntry* entry);
void FreeList(_ListEntry* list);
_ListEntry* GetNextEntry(_ListEntry* entry);
_ListEntry* GetPrevEntry(_ListEntry* entry);

#endif  // _LIST_H