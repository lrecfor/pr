#ifndef _SORT_ENTRY_H
#define _SORT_ENTRY_H

#include "list.h"

_ListEntry* Merge(_ListEntry* first, _ListEntry* second);
_ListEntry* QuickSort(_ListEntry* head, int(*compareStringsFunction)(const void*, const void*));
_ListEntry* DivideList(_ListEntry* head);

#endif //_SORT_ENTRY_H