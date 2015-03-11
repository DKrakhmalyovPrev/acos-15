#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long uint64;

//���-�������
uint64 hash(char* code)
{
    uint64 h = 0;
    char *i;
    for (i = code; *i; i++) {
        h = h * 37 + *i - 'a' + 1;
    }
    return h;
}

typedef struct List {
    char *code;//���� - ������
    int len;//����� ������-�����
    uint64 h;//�������� ���-�������
    struct List *ne;//��������� �� ��������� ������� � �������
} List;

typedef struct Table {
    int N, M;//N - ���������� ��������� � �������, M - ������ �������
    List** t;//������ ���������� �� ������ �������� �������
} Table;

Table* T;
char T_empty = 1;//����, ������� ����������, ��� �� ���� ������� ��� �� ���� �������, ���������� ����� 1 (������)
int T_cur = 0;//��������� ����������� ������� (���������� ��������� ��������)
int T_sz = 0; //������ ���������� ������ (��� ���� ������ ��������)

//������� �������� ����� �������� � ����
void table_init(Table *table) {
    table->N = 0;
    table->M = 1;
    table->t = malloc(sizeof(List*));
    table->t[0] = NULL;
}

//������� ���������� ��������
void rebuild_table(Table *ta) {
    printf("The rebuilding\n");//���������� �����
    List **li;//��������������� ������ ���������� �� ������ �������� �������
    li = malloc(ta->N * sizeof (List*));
    int i, li_cur = 0;
    for (i = 0; i < ta->M; i++) {//� ����� �������� �� ��������� ������� ���������� �� ������ �������� �������
        List *it = ta->t[i];
        while (it != NULL) {
            li[li_cur++] = it;
            it = it->ne;
            li[li_cur - 1]->ne = NULL;//� ���������� �������� ������, � ������� �������� ��� �������� �������� �������
        }
    }
    ta->M *= 2;//����������� ������ ������� � ��� ����
    ta->t = realloc(ta->t, ta->M * sizeof(List*));
    for(i = 0; i < ta->M; i++) {
        ta->t[i] = NULL;
    }
    for (i = 0; i < ta->N; i++) {//� ����� ������������� ����� ��������
        li[i]->ne = ta->t[li[i]->h % ta->M];
        ta->t[li[i]->h % ta->M] = li[i];
    }
    free(li);
}

//������� ������ ������ � ���������� ��������� ��������
void write_in_table(Table *ta, char *code) {//ta - ��������� �� ��������, � ������� ������������ ������
    if (ta->N == ta->M)
        rebuild_table(ta);//����� ���������� ���������� ��������, ����� ��������� � ������� ������� � � �������
    uint64 h = hash(code);//������� ��� �� �����
    List *it;
    it = malloc(sizeof(List));
    it->h = h;
    it->len = strlen(code);
    char *code_copy;
    code_copy = malloc(it->len + 1);
    memcpy(code_copy, code, it->len + 1);
    it->code = code_copy;
    it->ne = ta->t[h % ta->M];
    ta->t[h % ta->M] = it;
}

//������� ������ �������� � ���������� ������ �� ����������� ����
char exist_in_list(List *it, uint64 h, char *code) {
    while (it) {
        if (it->h == h && strcmp(it->code, code) == 0)
            return 1;
        it = it->ne;
    }
    return 0;
}

//������� �������� �������� � ���������� ������ �� ����������� ����
char erase_in_list(List **prev, List *it, uint64 h, char *code) {
    while (it) {
        if (it->h == h && strcmp(it->code, code) == 0) {
            *prev = it->ne;
            free(it);
            return 1;
        }
        prev = &it->ne;
        it = it->ne;
    }
    return 0;
}

//������� ������ �������� � ���������� ��������� ��������
char exist_in_table(Table *ta, char *code) {
    uint64 h = hash(code);
    return exist_in_list(ta->t[h % ta->M], h, code);//������� ������ �������� � ���������� ������ �� ����������� ����
}

//������� ������� ������� ������� �� ���������� ��������� ��������
char erase_in_table(Table *ta, char *code) {
    uint64 h = hash(code);
    return erase_in_list(&ta->t[h % ta->M], ta->t[h % ta->M], h, code);//������� �������� �������� � ���������� ������ �� ����������� ����
}

void clear_list(List* it) {//�������, ������� ������������ ������� ������� ����������� ������
    if (it) {
        clear_list(it->ne);
        free(it);
    }
}

//�������, ������� ������������ �������� ������� �� ����������� ������
void clear_table(Table* ta) {
    int i;
    for (i = 0; i < ta->M; i++)
        clear_list(ta->t[i]);//�������, ������� ������������ ������� ������� ����������� ������
    free(ta->t);
}

//������� �������� �������, ���������� � ��������� �����
int table_Creation() {
    if (T_empty) {
        T = malloc(sizeof(Table));
        T_sz = 1;
        T_empty = 0;
    }
    if (T_cur == T_sz) {
        T_sz = T_sz * 2;
        T = realloc(T, T_sz * sizeof(Table));
    }
    table_init(&T[T_cur]);//������� �������� ����� �������� � ����
    return T_cur++;
}

//������� ������ ������
void table_Write(int id, char* code) { //������� ������: � ����� ������� (id) � ��� �������� (code)
    assert(0 <= id && id < T_cur);
    write_in_table(&T[id], code);//������� ������ ������ � ���������� ��������� ��������
}

//����� ��������
char table_Exist(int id, char* code) {
    assert(0 <= id && id < T_cur);
    return exist_in_table(&T[id], code);//������� ������ �������� � ���������� ��������� ��������
}

//�������� ��������
char table_Erase(int id, char* code){
    assert(0 <= id && id < T_cur);
    return erase_in_table(&T[id], code);//������� ������� ������� ������� �� ���������� ��������� ��������
}

//�������� �������
void table_Clear(int id) {
    assert(0 <= id && id < T_cur);
    clear_table(&T[id]);//�������, ������� ������������ �������� ������� �� ����������� ������
}
