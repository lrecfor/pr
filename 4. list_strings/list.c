#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

static bool IsEmpty(_ListEntry* list) 
{ 
	return list->_list->head == NULL; 
}

_ListEntry* InitList(size_t size)
{
	_List* list = (_List*)malloc(sizeof(_List));

	if (list == NULL) {
		printf("InitList(): error\n");
		exit(EXIT_FAILURE);
	}

    list->size = size;

	_ListEntry* node = (_ListEntry*)malloc(size);
	if (node && list)
	{
		node->next = NULL;
		node->prev = NULL;

		list->head = node;
		list->tail = node;

		node->_list = list;
	}

	return node;
}

_ListEntry* InsertList(_ListEntry* newEntry)
{
	_ListEntry* node = (_ListEntry*)malloc(newEntry->_list->size);

	if (node == NULL) {
		printf("InsertList(): error\n");
		exit(EXIT_FAILURE);
	}
	
	node->next = 0;
	node->prev = 0;
	node->_list = newEntry->_list;

	if (IsEmpty(newEntry)) {
		newEntry->_list->head = node;
		newEntry->_list->tail = node;
	}
	else {
		newEntry->_list->tail->next = node;

		node->prev = newEntry->_list->tail;
		newEntry->_list->tail = node;
	}

	return node;
}

void PopBack(_ListEntry* tail)
{
    if (IsEmpty(tail)) {
		printf("PopBack(): list is empty\n");
		exit(EXIT_FAILURE);
    }

    if (tail->_list->tail->prev != NULL)
		tail->_list->tail->prev->next = NULL;

	_ListEntry* prev = tail->_list->tail->prev;
	tail->_list->tail->prev = NULL;
    free(tail->_list->tail);
	tail->_list->tail = prev;
}

void RemoveEntry(_ListEntry* entry)
{
	if (IsEmpty(entry)) {
		printf("RemoveEntry(): entry is empty\n");
		exit(EXIT_FAILURE);
	}

	_ListEntry* current = entry;
	_List* list = entry->_list;

	if (current == list->head)
	{
		list->head = current->next;
		free(current);
		current = list->head;

		if (current == NULL)
			list->tail = NULL;
	}

	else {
		current->prev->next = current->next;

		if (current->next != NULL)
			current->next->prev = current->prev;
		else
			list->tail = current->prev;

		free(current);
	}
}

void FreeList(_ListEntry* list)
{
	while (!IsEmpty(list))
		PopBack(list);

	free((list)->_list);
	free(list);

	list = NULL;
}

_ListEntry* GetNextEntry(_ListEntry* entry)
{
	return entry->next;
}


_ListEntry* GetPrevEntry(_ListEntry* entry)
{
	return entry->prev;
}