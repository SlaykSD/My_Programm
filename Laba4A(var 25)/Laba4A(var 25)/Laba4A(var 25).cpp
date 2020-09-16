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

int CopyElement(Item* Table, Info* curr, int ver, int key);
void Inizilization_my_Table(void);//Инициализация исходной таблицы
int insert(int,char*);//Добавление элемента таблицы
char* getSTR(void);//Получение строки(Информация таблицы)
int getINT_0(void);//Получение ключа
int natural(int*);//Получение диалоговой информации(ввод варианта действия)
int getVersion(int*);//Получение версии элемента с таким же ключом
int cleaner(int,int);//Очистка определенной строчки или элемента таблицы
void deletedALL(void);//Очистка использованной таблицы
int insertList(int, int, char*);
int dialog(void);
int output(Item* Table);
int delMORE(int);
int delONE(int, int*);
int D_Input(void);
int D_Del(void);
int D_Found(void);
int D_Show(void);
Info* foundNEW(int, int, Item*);
const char* msgs[] = { "Welcome to my program","That's OKEY"};
const char* NMsgs[] = {"You need to choose one of the following items-> " ,"Exit: 0","Insert: 1",
"Delete: 2" ,"Show: 3" ,"Search: 4" };

int (*fptr[])(void) = { NULL,D_Input,D_Del,D_Show,D_Found};


int main()
{
	Inizilization_my_Table();
	int rc,key,ver;
	while (rc = dialog())
	{
		if (!fptr[rc]())
			break;
	}
	deletedALL();
    return 0;
}

int dialog(void)
{
	int rc;
	printf("\n%s", msgs[0]);
	for (int i = 0; i < 6; ++i)
	{
		printf("\n%s", NMsgs[i]);
	}
	natural(&rc);
	return rc;
}

int D_Input(void)
{
	int k = getINT_0();
	char* inf = getSTR();
	if (inf == NULL)
		return 0;
	insert(k, inf);
	return 1;
}

int D_Del(void)
{
	int k = getINT_0();
	int ver = 0;
	getVersion(&ver);
	cleaner(k, ver);
	return 1;
}
int D_Found(void)
{
	int k = getINT_0();
	int ver = 0;
	Item PtableSEARCH[M];
	for (int i = 0; i < M; i++)
	{
		PtableSEARCH[i].busy = 0;
		PtableSEARCH[i].key = 0;
	}
	getVersion(&ver);
	Info*rex = foundNEW(k, ver, &Ptable[0]);
	if (rex == NULL)
		return 1;
	PtableSEARCH[hash_function(k)].key = k;
	PtableSEARCH[hash_function(k)].busy = 1;
	CopyElement(&PtableSEARCH[0],rex,ver,k);
	output(&PtableSEARCH[0]);
	if (ver == 0)
	{
		PtableSEARCH[hash_function(k)].info = NULL;
	}
	else
	{
		Info* tmp = PtableSEARCH[hash_function(k)].info;
		tmp->release = 0;
		tmp->info = NULL;
		tmp=NULL;
	}
	return 1;
}
int CopyElement(Item* Table,Info* curr, int ver,int key)
{
	Info* curr2 = NULL;
	int j = hash_function(key);
	if (ver == 0)
	{
		Table[j].info = curr;
	}
	else
	{
		curr2 = (Info*)malloc(sizeof(Info));
		Table[j].info = curr2;
		curr2->info = curr->info;
		curr2->release = curr->release;
		curr2->next = NULL;
	}
	return 0;
}
void Inizilization_my_Table()
{
	for (int i = 0; i < M; i++)
	{
		Ptable[i].busy = 0;//Аля позиция свободна как ветер
		Ptable[i].key = 0;
	}
}
/*
	while ((Ptable[i].busy == 1))
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
	*/
int find(int key,Item* Table,int* j)
{
	int i;
	int strt = i = hash_function(key);
	*j = i;
	while ((Table[i].busy == 1))
	{
		if (Table[i].key == key)
			return 1;
		i = hash_function(i + h);//двигаемся на шаг хешир-я
		*j = i;
		if (i == strt)
		{
			return -1;
		}
	}
	/*
	int i= hash_function(key);
	while( Ptable[i].busy ==1)
	{
		i=hash_function(i+ h);
	if ( i == strt)
		{
			printf("Errro");
			return 1;
		}
	}
	//vstavit element v i
	*/
	return 0;
}
int insert(int key,char* inf)
{
	int i;
	int strt = i = hash_function(key);
	int j;
	int n = find(key, &Ptable[0],&j);

	if (n&&(n!=-1))
	{//Вставка в занятую ячейку
		return insertList(key, j, inf);
	}
	else
	{ // Вставка в свободную ячейку
		if (n!=-1)
		{
			Ptable[j].busy = 1;
			Ptable[j].key = key;
			Info* curr = Ptable[j].info;
			if (curr == NULL)
			{
				curr = (Info*)malloc(sizeof(Info));
				curr->release = 1;
				curr->info = inf;
				curr->next = NULL;
				Ptable[j].info = curr;
				return 1;
			}
			else
			{
				printf("BAAAAAAN");
				return-432;
			}
		}
		else
		{
			printf("My Table is fulled");
			return -2;
		}
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

int D_Show(void)
{
	output(&Ptable[0]);
	return 1;
}

int output(Item* Table)
{
	for (int i = 0; i < M; ++i)
	{
		Info* curr = Table[i].info;
		if (Table[i].busy != -1)
		{
			printf("///////////// %d ////////////\n", i);
			if (Table[i].busy == 1)
			{
				while (curr != NULL)
				{

					printf("Key: %d;\nInformation:\"%s\";\nVersion %d;\n", (Table[i].key), curr->info, (curr->release));
					curr = curr->next;
				}
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
Info* foundNEW(int key, int ver, Item* Table)
{
	int i;
	int strt = i = hash_function(key);
	while (Table[i].busy != 0)
	{
		if ((Table[i].busy == 1)&&(Table[i].key == key))
		{
			if (ver == 0)
			{
				return Table[i].info;
			}
			Info* tmp = Table[i].info;
			while (tmp!=NULL)
			{
				if (tmp->release == ver)
				{
					return tmp;
				}
				tmp = tmp->next;
			}
			printf("\nError : This Realise is not found");
			return(NULL);
		}
		i = hash_function(i + h);
		if (strt == i)
		{
			printf("\nError : This key is not found");
			return NULL;
		}
	}
	printf("\nError : This key is not found");
	return NULL;
}
/*
Item* searсh(int key,int ver)
{
	int i;
	int strt = i = hash_function(key);

		while (Ptable[i].busy >= -1)
		{
			if (Ptable[i].key == key)
			{
				if (ver== 0)
				{
					return CreateNewTableMORE(key,i);
				}
				else
				{
					return CreateNewTableONE(key,i,&ver);
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
*/
int cleaner(int key,int ver)
{
	int i;
	int strt = i = hash_function(key);
	while ((Ptable[i].busy !=0 ))
	{
		if (Ptable[i].key == key)
		{
			if (ver == 0)
			{
				return delMORE(i);
			}
			else
			{
				return delONE(i, &ver);
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