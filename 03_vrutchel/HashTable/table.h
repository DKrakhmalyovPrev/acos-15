#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

//������� �������� �������, ���������� � ��������� �����
int table_Creation();

//������� ������ ������
void table_Write(int id, char* code);

//����� ��������
char table_Exist(int id, char* code);

//�������� ��������
char table_Erase(int id, char* code);

//�������� �������
void table_Clear(int id);

#endif // TABLE_H_INCLUDED
