# include "stdafx.h"

/*����� �������� ���������� � ������ ������ - ����, �������� �� ������ ����� , �������� ������ ������ - ����, �������� ������ - -����*/

struct Node
{
	struct Node * next;
	struct Node* prev;
	const char* value;
};

struct List {
	struct Node * head;
	struct Node * tail;
};

/*�������� ������� ������*/
struct List* createList()
{
	struct List* list = (struct List*)malloc(sizeof(struct List));
	list->head = NULL;
	list->tail = NULL;
	return list;
}

/*�������� ������*/
void deleteList(struct List** list) /*��� ������� �������� �����*/
{
	struct Node* tmp = NULL;
	if ((*list) != NULL)
	{
		while ((*list)->head)
		{
			tmp = (*list)->head;
			(*list)->head = (*list)->head->next;
			free(tmp);
		}
		free(*list);
		(*list) = NULL;
		return;
	}
	return;
}

/*����� � ������, ���������� ��������� �� ����, ���� �����, � 0, ���� �� �����*/
struct Node* findInto(struct List* list, const char* str)
{
	struct Node * tmp = list->head;
	while (tmp)
	{
		if (strcmp(str, tmp->value) == 0)
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

/*�������� �� ������ ����� ������*/
void DeleteFromList(struct List* list, const char * str)
{
	struct Node* tmp = findInto(list, str);
	if (tmp)
	{
		if (tmp->prev)
		{
			tmp->prev->next = tmp->next;
		}
		else
		{
			list->head = tmp->next;
		}
		if (tmp->next)
		{
			tmp->next->prev = tmp->prev;
		}
		else
		{
			list->tail = tmp->prev;
		}
		free(tmp);
	}
	else
	{
		printf("No such key");
	}
	return;
}

/*������� � ������ ������*/
void InsertIntoHead(struct List* list, const char* value)
{
	struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
	tmp->value = value;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}
	list->head = tmp;
	if (!list->tail)
	{
		list->tail = tmp;
	}
	return;
}

/*������� ��� ������ �������� ������*/
void print(const char* str, size_t index)
{
	printf("(%d) -> %s \t", index, str);
	return;
}

/*������ ������*/
void printList(struct List *list, void(*print)(const char*, size_t))
{
	if (list == NULL)
	{
		printf("There's no list\n");
		return;
	}
	struct Node * tmp = list->head;
	size_t index = 1;
	while (tmp)
	{
		print(tmp->value, index);
		index++;
		tmp = tmp->next;
	}
	return;
}

void TestFunc()
{
	struct List* list = createList();
	InsertIntoHead(list, "Andrey");
	//list = realloc(list, 2*sizeof(struct List));
	InsertIntoHead(list, "Olya");
	//printList(list, print);
	struct Node* tmp = findInto(list, "Olya");
	printf("%s \n", tmp->value);
	//leteFromList(list, "Olya");
	//printList(list, print);
	//deleteList(&list);
	//printList(list, print);
}


