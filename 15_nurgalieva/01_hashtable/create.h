# include "stdafx.h"
//#ifndef "create.h"
//#define "create.h"
//#endif;

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


struct List* createList();

/*�������� ������*/
void deleteList(struct List** list) /*��� ������� �������� �����*/;

/*�������� �� ������ ����� ������*/
void DeleteFromList(struct List* list, const char * str);

/*����� � ������, ���������� ��������� �� ����, ���� �����, � 0, ���� �� �����*/
struct Node* findInto(struct List* list, const char* str);

/*������� � ������ ������*/
void InsertIntoHead(struct List* list, const char* value);

/*������� ��� ������ �������� ������*/
void print(const char* str, size_t index);

/*������ ������*/
void printList(struct List *list, void(*print)(const char*, size_t));
