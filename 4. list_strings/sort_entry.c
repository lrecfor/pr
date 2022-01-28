#include <stdlib.h>
#include <stdbool.h>

#include "sort_entry.h"

_ListEntry* Merge(_ListEntry* first, _ListEntry* second, int(*compareStringsFunction)(const void*, const void*))
{
    if (!first)
        return second;

    if (!second)
        return first;

    if (compareStringsFunction(first, second) < 0)
    {
        first->next = Merge(first->next, second, compareStringsFunction);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = Merge(first, second->next, compareStringsFunction);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

_ListEntry* QuickSort(_ListEntry* head, int(*compareStringsFunction)(const void*, const void*))
{
    if (!head || !head->next)
        return head;
    _ListEntry* second = DivideList(head);

    head = QuickSort(head, compareStringsFunction);
    second = QuickSort(second, compareStringsFunction);

    return Merge(head, second, compareStringsFunction);
}

_ListEntry* DivideList(_ListEntry* head)
{
    _ListEntry* first = head, *second = head;
    while (first->next && first->next->next)
    {
        first = first->next->next;
        second = second->next;
    }
    _ListEntry* temp = second->next;
    second->next = NULL;
    return temp;
}