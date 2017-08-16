#include "List.h"

struct List
{
	ListNode* head;
	ListNode* tail;
	int length;
};

struct ListNode
{
	List_Item data;
	ListNode* next;
};

bool List_ValidateIndex(const List* list, int index)
{
	if (index < 0 || index >= list->length)
	{
		puts("index out of range");
		return false;
	}
	return true;
}

ListNode* ListNode_Create(List_Item data, ListNode* next)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	node->next = next;
	return node;
}

bool List_IsEmpty(const List* list)
{
	return list->length == 0;
}

List* List_Create()
{
	List* list = (List*)malloc(sizeof(List));
	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void List_Destroy(List* list)
{
	if (list == NULL) return;

	ListNode* currNode = list->head;
	while (currNode != NULL)
	{
		ListNode* next = currNode->next;
		free(currNode);
		currNode = next;
	}
	free(list);
}

ListNode* List_GetNode(List* list, int index)
{
	ListNode* targetNode = list->head;
	for (int i = 1; i <= index; ++i)
	{
		targetNode = targetNode->next;
	}
	return targetNode;
}

void List_Set(List* list, int index, List_Item data)
{
	if (!List_ValidateIndex(list, index)) exit(0);

	ListNode* targetNode = List_GetNode(list, index);
	targetNode->data = data;
}

List_Item List_Get(const List* list, int index)
{
	if (!List_ValidateIndex(list, index)) exit(0);

	ListNode* targetNode = List_GetNode(list, index);
	return targetNode->data;
}

void List_Add(List* list, List_Item data)
{
	if (List_IsEmpty(list))
	{
		list->tail = ListNode_Create(data, NULL);
		list->head = list->tail;
	}
	else
	{
		list->tail->next = ListNode_Create(data, NULL);
		list->tail = list->tail->next;
	}
	list->length++;
}

void List_Insert(List* list, int index, List_Item data)
{
	if (List_IsEmpty(list))
	{
		if (index != 0) puts("index out of range"); exit(0);
		list->head = ListNode_Create(data, NULL);
		list->tail = list->head;		
	}
	else
	{
		if (!List_ValidateIndex(list, index)) exit(0);

		if (index == 0)
		{
			list->head = ListNode_Create(data, list->head);
		}
		else
		{
			ListNode* targetPreNode = List_GetNode(list, index - 1);
			targetPreNode->next = ListNode_Create(data, targetPreNode->next);
		}
	}
		
	list->length++;
}

void List_RemoveAt(List* list, int index)
{
	if (List_IsEmpty(list)) puts("list is empty"); exit(0);
	if (!List_ValidateIndex(list, index)) exit(0);

	if (List_Length(list) == 1)
	{
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
	}
	else
	{
		if (index == 0)
		{
			ListNode* targetNode = list->head;
			list->head = list->head->next;
			free(targetNode);
		}
		else if (index == List_Length(list) - 1)
		{
			ListNode* targetPreNode = List_GetNode(list, index - 1);
			targetPreNode->next = NULL;
			free(list->tail);
			list->tail = NULL;
		}
		else
		{
			ListNode* targetPreNode = List_GetNode(list, index - 1);
			ListNode* targetNode = targetPreNode->next;
			targetPreNode->next = targetPreNode->next->next;
			free(targetNode);
		}
	}

	list->length--;
}

int List_Length(const List* list)
{
	return list->length;
}

void List_Clear(List* list)
{
	if (list == NULL) return;
	
	ListNode* currNode = list->head;
	while (currNode != NULL)
	{
		ListNode* next = currNode->next;
		free(currNode);
		currNode = next;
	}

	list->head = NULL;
	list->tail = NULL;
	list->length = 0;
}

void List_Traverse(List* list, void(*fun)(List_Item data))
{
	for (ListNode* currNode = list->head; currNode != NULL; currNode = currNode->next)
		fun(currNode->data);
}