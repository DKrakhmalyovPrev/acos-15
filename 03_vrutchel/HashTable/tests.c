#ifndef STDLIB_H_INCLUDED
#define STDLIB_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "table.h"

//������� �������� ������� ��������� �����
char **randomize_strings() {
    int i, j, c;
    char** array = malloc(sizeof(char*) * 100);
    for(j = 0; j < 100; j++)
    {
        array[j] = malloc(16);
        for(i = 0; i < 15; i++)
        {
            c = rand() % 26;
            c = 'a' + c;
            array[j][i] = c;
        }
        array[j][15] = '\0';
    }
    return array;
}

void Testing_first() {
    char **array = randomize_strings();
    int i, j;

    printf("Randomizing strings: \n");
    for(i = 0; i < 100; i++)
    {
        printf("%s ", array[i]);
    }
    printf("\n");

    //� ����� ������ 10 ����� ��������
    printf("Create new tables:\n");
    for(i = 0; i < 10; i++)
    {
        printf("%d ", table_Creation());
    }
    printf("\n\n");

    //� ����� ���������� � ������ �� �������� ����� ��������
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 100; j++)
        {
            table_Write(i, array[j]);//��������! ������! � ���������� �� ���������� ��������� �������� (�� table.c)
        }
    }

    //��������� ��� ������ � ������ ��������
     for(i = 0; i < 100; i++)
    {
        table_Write(0, array[i]);//� ����� ������: ������ �������� �� �����������?
    }

    //������� �������� �� ��������
    printf("Deleting existing elements:\n");
    for(i = 0; i < 99; i++)
    {
        printf("%d ", table_Erase(1, array[i]));
    }
    printf("\n\n");

    //��������, ���� �� � �������� ������ �������� ��������
    printf("Checking: are elements exist:\n");
    for(i = 0; i < 100; i++)
    {
        printf("%d ", table_Exist(1, array[i]));//��������� ������� ������ ������������, ��� ��� �� ��� �� �������
    }
    printf("\n\n");

    //������ ������ �� �������� ������ ���������, ��� � ��� ����������
    printf("Deleting more elements than exist:\n");
    printf("%d ", table_Erase(1, array[99]));
    for(i = 0; i < 20; i++)
    {
        printf("%d ", table_Erase(1, array[i]));
    }
    printf("\n\n");

    //������ ������ ��� ������������ ��������, � ���������� ����� ������� ��������, ������� �� ����������
    printf("Deleting all tables and more:\n");
    for(i = 0; i < 10; i++)
    {
        table_Clear(i);
    }
    printf("\n\n");
    table_Clear(0);//������ ���, �� ��������� ��������� (������ ���, ���� ����� �������� �� ����������), �� ����, ����� �� ��� ����������
    //table_Clear(125);//� ��� � ���� ����� ��� �������� ������� ��������, ��� ����� �������� ���
    //�������� �������� � ����������� ��������, ���� �� �������� ���������� ����� (�������� � ��������� ������ ������ � �� ��������),
    //���� �� ��� ���-�� ���, �� ���� �� ����, ��� � �������� ������������ ������ �� ���� �������, ��� ����������� ����������
    //�� ���������� ������� ��������
    //�� ���� ����� ������

}

#endif // STDLIB_H_INCLUDED
