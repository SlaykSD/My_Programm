#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Info
{
    int release;
    char* info;
    Info* next;
}Info;
typedef struct Item
{
    int busy;
    int key;
    Info* info;
}Item;

/////////////////// Объявление таблицы
int const M = 10;// Количество элементов таблицы
Item Ptable[M];  // Хеш-таблица
int const h = 3; //<-Шаг перемешивания
///////////////////
int hash_function(int key)
{
    return key % M;
}
void Inizilization_my_Table(void);//Инициализация исходной таблицы
int insert(void);//Добавление элемента таблицы
char* getSTR(void);//Получение строки(Информация таблицы)
int getINT_0(void);//Получение ключа
int natural(int*);//Получение диалоговой информации(ввод варианта действия)
int output(void);//Вывод таблицы

int getVersion(int*);//Получение версии элемента с таким же ключом
int cleaner(void);//Очистка определенной строчки или элемента таблицы
void deletedALL(void);//Очистка использованной таблицы
int insertList(int, int, char*);
int dialog(void);
Item* CreateNewTableMORE(int , int );
Item* CreateNewTableONE(int , int, int* );
int delMORE(int);
int delONE(int, int*);
const char* msgs[] = { "Welcome to my program","That's OKEY"};
const char* NMsgs[] = {"You need to choose one of the following items-> " ,"Exit: 0","Insert: 1",
"Delete: 2" ,"Show: 3" ,"Search: 4" };

Item* searсh(void);//поиск необхоодимых элементов и создание новой таблицы найденных элементов
int (*fptr[])(void) = { NULL,insert,cleaner,output};


int main()
{
	Inizilization_my_Table();
	int rc,key;
	while (rc = dialog())
	{
		if (rc == 4)
			Item* NewTable = searсh();
		else
		{
			if (!fptr[rc]())
				break;
		}
	}
	deletedALL();
    return 0;
}

int dialog(void)
{
	int rc;
	printf("%s", msgs[0]);
	for (int i = 0; i < 6; ++i)
	{
		printf("\n%s", NMsgs[i]);
	}
	natural(&rc);
	return rc;
}

void Inizilization_my_Table()
{
	for (int i = 0; i < M; i++)
	{
		Ptable[i].busy = 0;//Аля позиция свободна как ветер
		Ptable[i].key = 0;
	}
}

int insert(void)
{
	int key = getINT_0();
	char* inf;
	inf = getSTR();
	if (inf==NULL)
	{
		return 0;
	}
	int i;
	int strt = i = hash_function(key);
	while ((Ptable[i].busy == 1)||(Ptable[i].busy == -1))
	{
		if (Ptable[i].key == key)//ага, ключики совпали
		{
			return insertList(key, i, inf);
		}
		i = hash_function(i + h);//двигаемся на шаг хешир-я
		if (i == strt)
		{
			puts("My Table is fulled");
			return -2;
		}
	}
	Ptable[i].busy = 1;
	Ptable[i].key = key;
	Info* curr = Ptable[i].info;
	if (curr == NULL)
	{
		curr = (Info*)malloc(sizeof(Info));
		curr->release = 1;
		curr->info = inf;
		curr->next = NULL;
		Ptable[i].info = curr;
		return 1;
	}
	else
	{
		printf("Error from Insert");
		exit(2);
	}
}
int insertList(int key, int i,char* inf)
{
	Info* curr =NULL;
	Info* tmp = Ptable[i].info;
	curr = (Info*)malloc(sizeof(Info));
	curr->info = inf;
	curr->release = tmp->release + 1;
	Ptable[i].info = curr;
	curr->next = tmp;
	return -1;
}

char* getSTR()
{
	char* ptr = (char*)malloc(1);//Ввод
	//Создаем буфер для считыывания
	char buf[81];
	int len = 0, n;
	*ptr = '\0';
	printf("Write Information :\n");
	do
	{
		n = scanf_s("%80[^\n]", buf, 81);
		if (n < 0) // встречен конец файла
		{
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
			scanf_s("%*c");
		else
		{
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}
int getINT_0()
{
	int x = 1;
	int n;
	do {
		printf("Write KEY {1..INT_MAX} ");
		n = scanf_s("%d", &x);
		if (n < 0) {
			printf("EOF detected");
			exit(1);//Летал
		}
		if (n == 0)
		{
			printf("Input Err!\n");
			scanf_s("%*[^\n]");
		}
		else
		{
			if (x <= 0)
			{
				n = 0;
				printf("Input Err!\n");
				scanf_s("%*[^\n]");
			}
		}
		
	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return x;
}
int natural(int* x)
{
	int n;
	do {
		printf("\nWrite Natural number under or equal 4!: ");
		n = scanf_s("%d", x);
		if (n < 0) {
			printf("EOF detected");
			exit(1);
		}
		if (n == 0)
		{
			printf("Input Err!\n");
			scanf_s("%*[^\n]");
		}
		else
		{
			if ((*x < 0) or (*x > 4))
			{
				n = 0;
				printf("Input Err!\n");
				scanf_s("%*[^\n]");
			}
		}
	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return *x;
}

int output(void)
{
	for (int i = 0; i < M; ++i)
	{
		Info* curr = Ptable[i].info;
		if (Ptable[i].busy != -1)
		{
			printf("///////////// %d ////////////\n", i);
			while (curr != NULL)
			{

				printf("Key: %d;\nInformation:\"%s\";\nVersion %d;\n", (Ptable[i].key), curr->info, (curr->release));
				curr = curr->next;
			}
		}
	}
	return 1;
}


int getVersion(int* x)
{
	int n;
	int counter = 0;
	do {
		printf("\nWrite Release(natural number)\n");
		printf("If you will all key values then write '0'\n");
		n = scanf_s("%d", x);
		if (n < 0) {
			printf("EOF detected");
			exit(1);
		}
		if (n == 0)
		{
			printf("Input Err!\n");
			scanf_s("%*[^\n]");
		}
		else
		{
			if ((*x < 0))
			{
				n = 0;
				printf("Input Err!\n");
				scanf_s("%*[^\n]");
			}
			else
				if (*x == 0)
					counter++;
		}
	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return counter;
}
Item* searсh(void)
{
	int key = getINT_0();
	int *ver= (int*)malloc(sizeof(int));
	int i;
	int strt = i = hash_function(key);

		while (Ptable[i].busy >= -1)
		{
			if (Ptable[i].key == key)
			{
				if ((getVersion(ver)) > 0)
				{
					return CreateNewTableMORE(key,i);
				}
				else
				{
					return CreateNewTableONE(key,i,ver);
				}
			}
			i = hash_function(i + h);
			if (i == strt)
			{
				puts("This key wasn't found");
				return NULL;
			}
		}
		puts("This key wasn't found or it is delated");
		return NULL;
}
int cleaner(void)
{
	printf("\nWelcome to the Ceaner, you need to choose the key and one realise or more...\n");
	int* ver = (int*)malloc(sizeof(int));
	int k = getINT_0();
	int i;
	int strt = i = hash_function(k);
	while ((Ptable[i].busy == 1) || (Ptable[i].busy == -1))
	{
		if (Ptable[i].key == k)
		{
			if (getVersion(ver) > 0)
			{
				return delMORE(i);
			}
			else
			{
				return delONE(i, ver);
			}
		}
		i = hash_function(i + h);
		if (i == strt)
		{
			puts("This key wasn't found");
			return -1;
		}
	}
	puts("This key wasn't found");
	return -1;
}

void deletedALL(void)
{
	for (int i = 0; i < M; ++i)
	{
		Info* curr = Ptable[i].info;
		while (curr != NULL)
		{
			Info* tmp = curr;
			curr = curr->next;
			free(tmp->info);
			free(tmp);
		}
	}
}
Item* CreateNewTableMORE(int key,int i)
{
	Info* curr = Ptable[i].info;
	Info* tmp = (Info*)malloc(sizeof(Info));
	Info* tmp2 = tmp;
	while (curr != NULL)
	{
		printf("Element with a key: %d AND Realise: %d \n \"%s\"\n", Ptable[i].key, curr->release, curr->info);
		tmp->release = curr->release;
		tmp->info = curr->info;
		curr = curr->next;
		if (curr != NULL)
		{
			tmp->next = (Info*)malloc(sizeof(Info));
			tmp = tmp->next;
		}
	}
	Item PtableSEARCH[M];
	int j = hash_function(key);
	PtableSEARCH[j].key = key;
	PtableSEARCH[j].busy = 1;
	PtableSEARCH[j].info = tmp2;
	return PtableSEARCH;
}
Item* CreateNewTableONE(int key , int i, int* ver)
{
	Info* curr = Ptable[i].info;
	while (curr != NULL)
	{
		if (*ver == (curr->release))
		{
			printf("Element with a key: %d AND Realise: %d \n \"%s\"\n", Ptable[i].key, curr->release, curr->info);
			Item PtableSEARCH[M];
			int j = hash_function(key);
			PtableSEARCH[j].key = key;
			PtableSEARCH[j].busy = 1;
			PtableSEARCH[j].info = curr;
			return PtableSEARCH;
		}
		curr = curr->next;
	}
	puts("This Realise wasn't found");
	return NULL;

}
int delONE(int i, int* ver)
{
	Info* curr = Ptable[i].info;
	Info* tmp = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->release == *ver)
		{
			Ptable[i].info = curr;
			if (curr == NULL)
			{
				Ptable[i].busy = -1;
				Ptable[i].key = 0;
			}
			free(tmp->info);
			free(tmp);
			curr = Ptable[i].info;
			printf("Delete was complated successfully");
			return 1;
		}
		if ((curr != NULL) && (curr->release == *ver))
		{
			tmp->next = curr->next;
			free(curr->info);
			free(curr);
			printf("Delete was complated successfully");
			return 1;
		}
	}
	puts("This Realise wasn't found");
	return -2;
}
int delMORE(int i)
{
	Info* curr = Ptable[i].info;
	while (curr != NULL)
	{
		Info* tmp = curr;
		curr = curr->next;
		free(tmp->info);
		free(tmp);
	}
	Ptable[i].busy = -1;// Ячейка считается удаленной
	Ptable[i].info = NULL;
	Ptable[i].key = 0;
	printf("Delete was complated successfully");
	return 1;
}