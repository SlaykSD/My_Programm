﻿#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

char* getSTR();
char* skipSpace(char*);
int reorg(char*, char*,char*);
void ResultSTR(char*, char*);
int main()
{
	char* s = NULL, * expention= NULL;
	char* format = NULL;
	int n = 0;
	puts("enter...");
	s = getSTR();
	while (n==1)
	{
		printf("Source string: \"%s\"\n", s);
		strcat(s, " \0");
		format = (char*)malloc(strlen(s));
		char* exeption = (char*)malloc(strlen(s));
		*format = '\0';
		*exeption = '\0';
		n = reorg(s, format,expention);
		free(s);
		s = NULL;
		printf("Result string: \"%s\"\n", expention);
		printf("Result string(new): \"%s\"\n", format);
		free(expention);
		free(format);
		puts("enter...");
		s = getSTR();
	}
	puts("That's all. Bye!");
	return 0;
}
char* getSTR()
{
	char* ptr = (char*)malloc(1);//Ввод
	//Создаем буфер для считыывания
	char buf[81];
	int len = 0, n;
	*ptr = '\0';
	do
	{
		n = scanf_s("%80[^\n]", buf, 81);
		if (n < 0) // встречен конец файла
		{
			printf("");
			free(ptr);
			ptr = NULL;
		}
		if (n == 0)
			scanf_s("%*c");
		else
		{
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 2);
			strcat(ptr, buf);
		}
	} while (n < 1);

	return ptr;
}
char* skipSpace(char* s)
{
	int k = strspn(s, " \t"); // 1-̼̜ ̦е ̭о̏п̌д̛̺̜̌̀ ̛̭̥̏ол
	return s + k;
}
int reorg(char* s, char* format,char* expention)
{
	int n = 0;
	char* p = s;
	char* exeption = (char*)malloc(1);
	char* format1 = (char*)malloc(1);
	int lenX = 0, lenF = 0;
	*format1 = '\0';
	*exeption = '\0';
	for (int i = 0; i < strlen(s) - 1; i++)
	{
		

		if ((*(s + i) == '\t'))
		{
			*(s + i) = ' ';
		}
		if ((*(s + i) == *(s + i + 1) && (*(s + i) == ' ')))
			continue;
		if (*(s + i) == *(s + i + 1))
		{
			int j = 0;
			while (*(s + i + j) == *(s + i + 1 + j))
			{
				++j;//посчитали количество одинаковых символов
			}
			p = s + i;
			i += j;
			j += 1;//всего одинаковых чисел
			lenX += j;
			exeption = (char*)realloc(exeption, (lenX + 2));
			exeption = strncat(exeption, p, j);
			exeption[lenX] = ' ';
			exeption[lenX + 1] = '\0';
			lenX += 1;
			continue;
		}
		lenF += 1;
		format1 = (char*)realloc(format1, (lenF + 1));
		format1[lenF - 1] = *(s + i);
	}
	if (lenX != 0)
	{
		exeption[lenX - 1] = '\0';
	}
	format1[lenF] = '\0';
	ResultSTR(format1, format);
	free(format1);
	return n;
}
void ResultSTR(char* format1, char* format)
{
	format1 = skipSpace(format1);
	int lenF = 0;
	for (int i = 0; i < strlen(format1); i++)
	{
		if ((*(format1 + i) == *(format1 + i + 1) && (*(format1 + i) == ' ')))
			continue;
		lenF += 1;
		format[lenF - 1] = *(format1 + i);
	}
	format[lenF] = '\0';
}
