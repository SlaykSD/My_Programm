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
int getList(It_list**);//Создание списка
void putList(It_list*);//Вывод списка
void deleteList(It_list*);//Удаление списка
It_list* reorg2(It_list*);
It_list* delWord(It_list*);
It_list* SkipSpac2(It_list*);
It_list* delSpace(It_list*);
It_list* skipWord(It_list*);
int main()
{
	It_list* list;
	while (puts("Enter STRING: "), getList(&list))
	{
		puts("Entered string: ");
		putList(list);
		It_list* p = reorg2(list);
		printf("\n");
		putList(p);
		printf("\n");
		deleteList(p);
	}
	return 0;
}

void putList(It_list* head)
{
	It_list* list = head;
	while (list != NULL)
	{
		printf("%c", list->c);
		list = list->next;
	}
}

int getList(It_list** list)
{
	char buf[81], * str = NULL;
	It_list head = { '*',NULL };
	It_list* last = &head;
	int n, n2 = 1;
	do {
		n = scanf_s("%80[^\n]", buf, 81);
		if (n < 0)
		{
			deleteList(head.next);
			head.next = NULL;
			n2 = 0;
			break;
		}
		if (n > 0)
		{
			for (str = buf; *str != '\0'; ++str)
			{
				last->next = (It_list*)malloc(sizeof(It_list));
				last = last->next;
				last->c = *str;
			}
			last->next = NULL;
		}
		else
			scanf_s("%*c");

	} while (n > 0);
	*list = head.next;
	return n2;
}
void deleteList(It_list* list)
{
	It_list* head = list;
	It_list* tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
It_list* SkipSpac2(It_list* curr)
{
	while (curr && ((curr->c == ' ') || (curr->c == '\t')))
	{
		It_list* tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	return curr;
}
It_list* delSpace(It_list* last)
{

	while (last && ((last->c == ' ') || (last->c == '\t')))
	{
		if (last->c == '\t')
			last->c = ' ';
		if ((last->next == NULL) && (last->c == ' '))
		{
			free(last);
			return NULL;
		}
		if ((last->c == ' ') && last->next && ((last->next->c == last->c) || (last->next->c == '\t')))
		{
			It_list* tmp = last;
			last = last->next;
			free(tmp);
		}
		else
			if (last->next && (last->next->c != ' ') && (last->next->c != '\t'))
			{
				break;
			}
			else last = last->next;
	}
	return last;
}
It_list* delWord(It_list* last)
{
	while (last->next && ((last->next->c != ' ') && (last->next->c != '\t')))
	{
		It_list* tmp = last;
		last = last->next;
		free(tmp);
	}

	It_list* tmp = last;
	last = last->next;
	free(tmp);
	return last;
}
It_list* skipWord(It_list* last)
{
	while (last->next && ((last->next->c != ' ') && (last->next->c != '\t')))
	{
		last = last->next;
	}
	return last;
}
It_list* reorg2(It_list* p)
{
	p = SkipSpac2(p);
	It_list head = { '\0', p },
		* last = &head, * prev = NULL;
	char s = p->c;//Взяли 1-ый элемень
	while (last &&
		(last->next = delSpace(last->next)))
	{
		if (last->next->c == ' ')
		{
			if (last->next->next && (last->next->next->c != s))
				last->next = delWord(last->next);
			else {
				prev = skipWord(last->next);
				last = prev;
			}
		}
		else
		{
			last = last->next;
		}
	}
	return head.next;
}