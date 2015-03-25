#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#define MAX_PATH 256

int words(FILE* in)
{
	int count = 0;
	char word[256];
	while (!feof(in))
	{
		word[count++] = getc(in);
	}
	printf("Function words is working\n");
	printf("%s\n", word);
	return count;
}

void run(char* dir, int depth, int limit)
{
	printf("RUN DEPTH=%d STARTED OK\n", depth);
	printf("dir : %s\n", dir);
	if (depth > limit)
	{
		printf("depth == %d > limit == %d", depth, limit);
		return;
	}
	//Здесь нужно сделать проверку на вход (не превышена ли глубина)
	
	
	DIR *CurrDir = opendir(dir);
	//Рекурсивно опуститься если директория
	//struct dirent element;
	struct dirent *element;//было ли выполнено открытие объекта
	
	element = readdir(CurrDir); //Если имя . или .., то пропустить .d_name
	
	while(element != NULL)	//Если объект есть, то есть считался
	{                 
		if (strcmp(element->d_name, ".") == 0)
		{
			element = readdir(CurrDir);
			continue;
		}
		if (strcmp(element->d_name, "..") == 0)
		{
			element = readdir(CurrDir);
			continue;
		}		
		
		printf("Element name: %s\n", element->d_name);
		
	
//Склеивание полного пути к файлу
		char filepath[MAX_PATH];
		strcpy(filepath, dir);
		strcat(filepath, "/");
		strcat(filepath, element->d_name);
//Склеивание
		
//Информацию об element dirent запишем в fileinfo
		struct stat fileinfo;
		int check = stat(filepath, &fileinfo);
		
		
		printf("filepath : %s\n", filepath);
		if (check != -1)
		{
			if(S_ISREG(fileinfo.st_mode)) //Если обычный файл
			{
				//Посчитать слова
				printf("Filepath: %s;\nFUNCTION WORDS started: \n", filepath);
				FILE *in = fopen(filepath, "r"); 
				words(in);
				printf("FUCTION WORDS finished.\n");
			}
			if(S_ISDIR(fileinfo.st_mode)) //Если директория
			{
				run(filepath, depth+1, limit);
				printf("dir %s checked.\n", dir);
				//Рекурсивно опуститься ниже
			}
			
			if(S_ISLNK(fileinfo.st_mode)) //Если символическая ссылка
			{
				
			}
		}
		element = readdir(CurrDir);
	}
	
	
	
 	// = strcat(strcpy(dir), "/", element.d_name)); //полный путь к файлу
 	//char *p1, *p2, *p3;
 	//filename = strcat(strcpy(dir), "/");
	//lstat(filename, &fileinfo);

	//fileinfo.st_mode; //тип файла:S_ISDIR()директория,S_SLINK()символьная ссылка или файлS_ISREG()
	
	//if(S_ISDIR(fileinfo.st_mode))
	//{
		//Рекурсивно опуститься на директорию ниже
	//}
}

int main(int argc, char**argv)
{
	if (argc < 2)
	{
		printf("Wrong input.\n");
		return 1;
	}
	run(argv[1], 1, 10);

return 0;
}