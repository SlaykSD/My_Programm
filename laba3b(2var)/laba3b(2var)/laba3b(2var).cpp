

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>t
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
// Организуем структуру- список, в которой будет хранится наша строка
typedef struct It_list {
	char c;
	struct It_list* next;
}It_list;
int getList(It_list**);
void putList(It_list*);
It_list* deleteList(It_list*);

int main()
{
	It_list* list;
	puts("Enter STRING: ");
	while (getList(&list))
	{
		puts("Entered string: ");
		putList(list);
		list = deleteList(list);
	}
	return 0;
}

int getList(It_list** list)
{
	//создаем буфер как в прошлой лабе
	char buf[81], * str = NULL;
	It_list head = {'*',NULL};
	It_list* last = &head;
	int n, n2=1;
	do {
		n = scanf_s("%80[^\n]", buf, 81);
		if (n < 0)
		{
			deleteList(head.next);
			head.next = NULL;
			n2 = 0;
			continue;
		}
		if (n > 0)
		{
			for (str= buf;*str!='\0';++str)
			{
				last->next = (It_list*)malloc(sizeof(It_list));
			}
		}

	} while (n>1);
	return n2;
}
