// RB_WH.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <ctime>
//Расскраска дерева
#define RED 0
#define BLACK 1
typedef struct Node {
	int key;
	int color;
	char* info;
	struct Node* parent, * left, * right;
}Node;
typedef struct Item {
	int key;
	Node* Node;
}Item;
//Организуем EList
Node* EList = (Node*)malloc(sizeof(Node));
Node* Root;
const char* msgs[] = { "0->Exit","1->Insert","2->Search","3->Delete","4->Show","5->Show as TREE","6->Timing_RB","7->Timing_RB_WH" };
const int N = 10;//Размер кеш-буфера
int counter;
////////////////////////////
const int h = 1;////////////Шаг хеширования
int hash_function(int key)//
{						  //
	return key % N;		 ///
						////
}					  //////
////////////////////////////

Item* Table = (Item*)calloc(N, sizeof(Item));

void RB_Delete_Fixup(Node*);
void Left_rotate(Node*);
void Right_rotate(Node*);
int D_Load(Node*);
int D_Insert(Node*);
int D_Search(Node*);
int D_Delete(Node*);
int D_Show(Node*);
int rb_show(Node*);
int D_ShowTREE(Node*);
int D_Timing_RB(Node*);
int D_Timing_RB_WH(Node*);
int (*Function_RB[])(Node*) = { NULL,D_Insert,D_Search,D_Delete,D_Show,D_ShowTREE,D_Timing_RB,D_Timing_RB_WH };
int dialog(void);
Node* tree_minimum(Node*);
void rb_replace(Node*, Node*);
int RB_Delete(Node*);
char* getSTR(void);
int insert_RB(Node*);
int RB_Insert_Fixup(Node*);
int rb_tear_down(Node*, Node**);
Node* find_Table(int);
Node* Find_RB(Node*, int );
Node* Find_RB_Iter(Node*, int);
Node* Find_RB_WH(int);
int insert_HT(Item);
int getInt(void);
int show_as_tree(int, Node*);

int main()
{
	Root = EList;
	EList->parent = EList;
	EList->color = BLACK;
	EList->left = EList;
	EList->right = EList;
	int rc;
	if (D_Load(Root) == 0);
	while (rc = dialog())
	{
		if (!Function_RB[rc](Root))
			break;
	}
	rb_tear_down(Root, &Root);
	printf("\nThis all. Bye!");
	return 0;
}
int D_Load(Node* R)
{
	printf("Input file name:");
		char* fname = getSTR();
		if (fname == NULL)
			return 0;
		int len = strlen(fname);
		realloc(fname, len + 5);
		strcat(fname, ".txt");
		FILE *fd = NULL;
		errno_t err = fopen_s(&fd, fname, "r");
		if (err)
		{
			printf("\n File doesn't exist\n");
			return 0;
		}
		//возвращаем указатель в начало
		rewind(fd);
		char* info = (char*)calloc(100,sizeof(char));
		int k;

		while (fscanf(fd, "%d%s", &k, info) != EOF)
		{
			Node* New;
			New = (Node*)malloc(sizeof(Node));
			New->color = RED;
			New->key = k;
			New->left = EList;
			New->right = EList;
			New->info = info;
			Item NewIt = { k, New };
			insert_HT(NewIt);
			insert_RB(New);
		}
		free(info);
		free(fname);
		fclose(fd);
		return 1;
}
int dialog(void)
{
	int rc=9;
	for (int i = 0; i < 8; ++i)
		printf("\n%s", msgs[i]);
	while (rc >= 8)
	{

		printf("\nMake your choise:");
		rc = getInt();
		if(rc>=8)
			printf("\nError(<=7)");
		if (rc < 0)
		{
			return 0;
		}
	}
	return rc;
}

int rb_show(Node* x) {
	if (x != EList) {
		rb_show(x->left);
		printf("[key: %d | info: %s]\n", x->key, x->info);
		rb_show(x->right);
	}
	return 1;
}

int D_Show(Node*) {
	rb_show(Root);
	return 1;
}
int D_ShowTREE(Node*){
	puts("Tree:");
	show_as_tree(0, Root);
	return 1;
}
int show_as_tree(int count, Node* nd) {
	int i = 0;
	if (nd == EList) return 1;
	show_as_tree(count + 1, nd->left);
	for (; i < count; ++i) {
		printf("   ");
	}
	printf("%d;%d;%s\n", nd->key, nd->color, nd->info);
	show_as_tree(count + 1, nd->right);
	return 1;
}

int rb_tear_down(Node* ptr, Node** root) {
	if (ptr == EList) return 1;
	rb_tear_down(ptr->left, root);
	rb_tear_down(ptr->right, root);
	RB_Delete(ptr);
	return 1;
}

int D_Timing_RB(Node*)
{
	Node* root = Root,*x,*cur;
	int n = 10, key[10000], k, cnt = 1000000, i, m,j;
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0) {
		for (i = 0; i < 10000; ++i)
			key[i] = rand() * rand();
		for (i = 0; i < cnt;) {
			k = rand() * rand();
			x = (Node*)malloc(sizeof(Node));
			x->color = RED;
			x->right = EList;
			x->left = EList;
			x->key = k;
			/*
				New = (Node*)malloc(sizeof(Node));
	New->color = RED;
	New->key = key;
	New->left = EList;
	New->right = EList;
	New->info = info;
	Item NewIt = { key, New };
	insert_HT(NewIt);
	insert_RB(New);
			*/if (Find_RB(Root, k) == EList)
			{
				if (insert_RB(x))
					++i;
			}
		}
		m = 0;
		first = clock();//Зассекаем время
		for (i = 0; i < 10000; ++i) {
			if (Find_RB(Root,key[i])!=EList) {
				++m;
			}
		}
		last = clock();
		printf("%d items were found\n", m);
		printf("test #%d, number of nodes = %d, time = %ld\n",
			10 - n, (10 - n) * cnt, (last - first));
		cur = Root;
		for (j = 0; cur != EList; ++j) {
			cur = cur->left;
		}
		printf("tree height: %d\n", j);
	}
	rb_tear_down(Root, &Root);
	Root = EList;
	return 1;
}

int D_Timing_RB_WH(Node*)
{
	Node* root = Root, * x, * cur;
	int n = 10, key[10000], k, cnt = 1000000, i, m, j;
	clock_t first, last;
	srand(time(NULL));
	while (n-- > 0) {
		for (i = 0; i < 10000; ++i)
			key[i] = rand() * rand();
		for (i = 0; i < cnt;) {
			k = rand() * rand();
			x = (Node*)malloc(sizeof(Node));
			x->color = RED;
			x->right = EList;
			x->left = EList;
			x->key = k;
			Item NewIt = { k, x };
			/*
				New = (Node*)malloc(sizeof(Node));
	New->color = RED;
	New->key = key;
	New->left = EList;
	New->right = EList;
	New->info = info;
	Item NewIt = { key, New };
	insert_HT(NewIt);
	insert_RB(New);
			*/if ((find_Table(k)==EList)||(Find_RB(Root, k) == EList))//Не нашел элемент
			{
				if (insert_HT(NewIt)&&insert_RB(x))
					++i;
			}
		}
		Item Tabletko = *Table;
		m = 0;
		first = clock();//Зассекаем время
		for (i = 0; i < 10000; ++i) {
			if (find_Table(key[i]) != EList)//Нашел элемент
			{
				++m;
				continue;
			}
			if (Find_RB(Root, key[i])!=EList) {
				++m;
			}
		}
		last = clock();
		printf("%d items were found\n", m);
		printf("test #%d, number of nodes = %d, time = %ld\n",
			10 - n, (10 - n) * cnt, (last - first));
		cur = Root;
		for (j = 0; cur != EList; ++j) {
			cur = cur->left;
		}
		printf("tree height: %d\n", j);
	}
	rb_tear_down(Root, &Root);
	Root = EList;
	return 1;
}
void Left_rotate(Node* x)
{
	Node* y = x->right;
	Node* p = x->parent;
	//Переустанавливаем правое поддерево
	x->right = y->left;
	//Переустанавливаем родительский узел левого поддерева 
	if (y->left != EList)
		y->left->parent = x;
	//Формируем связь родитель - правый ребенок
	y->parent = p;
	if (p == EList)
	{
		Root = y;
	}
	else
	{
		if (p->left == x)
			p->left = y;
		else
			p->right = y;
	}
	//Формируем связь y-x
	y->left = x;
	x->parent = y;
}
void Right_rotate(Node* x)
{
	Node* p = x->parent;
	Node* y = x->left;
	x->left = y->right;
	
	if (y->right != EList)
	{
		y->right->parent = x;
	}
	y->parent = p;
	if (p == EList)
	{
		Root = y;
	}
	else {
		if (p->left == x)
			p->left = y;
		else
			p->right = y;
	}
	y->right = x;
	x->parent = y;
}
int D_Search(Node* R)
{
	int key;
	printf("\nWrite key:");
	key = getInt();
	if (key < 0)
	{
		return 0;
	}
	Find_RB_WH(key);
	return 1;
}

Node* find_Table(int key)//Поиск во всей таблице
{
	int i;
	i = hash_function(key);
		if (Table[i].key == key)
			return Table[i].Node;
	return EList;
}
int D_Insert(Node* x)
{
	Node* New;//Новый узел
	int key;
	printf("\nWrite key:");
	key = getInt();
	if (key < 0)
	{
		return 0;
	}
	printf("\nWrite Information:");
	char* info;
	info = getSTR();
	if (info == NULL)
		return 0;
	//Попробовали найти в хеш-таблице
	if (Find_RB_WH(key) != EList)
	{
		printf("\nERORR: Dublicate key");
		return 1;
	}
	//Таблица поиска
	New = (Node*)malloc(sizeof(Node));
	New->color = RED;
	New->key = key;
	New->left = EList;
	New->right = EList;
	New->info = info;
	Item NewIt = { key, New };
	insert_HT(NewIt);
	insert_RB(New);
	printf("\nInsert was successful");
	return 1;
}

Node* Find_RB(Node* ptr ,int key)
{//Хочу рекурсивный поиск
	if (ptr == EList)
		return EList;
	if (ptr->key == key)
		return ptr;
	if (key < ptr->key)
		Find_RB(ptr->left, key);
	else
		Find_RB(ptr->right, key);
}
Node* Find_RB_Iter(Node* ptr, int key)
{//Итеррационный поиск
	while (ptr != EList)
	{
		if (ptr->key = key)
			return ptr;
		if (key < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return EList;
}
Node* Find_RB_WH(int key)
{
	Node* find = find_Table(key);
	if (find == EList)
	{
		printf("\nThis element wasn't found in hash-table  :C");
	}
	else
	{
		printf("\nThis element was found in hash-table    C:");
		printf("\nKey-%d\nInfo:|%s|", key, find->info);
		return find;
	}
	Node* x = Root;
	find = Find_RB(x, key);
	if (find == EList)
	{
		printf("\nThis element wasn't found in RB-TREE   :C");
	}
	else
	{
		printf("\nThis element was found in RB-TREE   C:");
		printf("\nKey-%d\nInfo:|%s|", key, find->info);
		return find;
	}
	printf("\nThis element doesn't exists in RB_WH   C:");
	return find;
}
int D_Delete(Node* x)
{
	printf("\nWrite key:");
	int k = getInt();
	if (k < 0)
	{
		return 0;
	}
	Node* find = Find_RB_WH(k);
	if (find == EList)
	{
		printf("\nERORR: No element");
		return 1;
	}
	if(Table[hash_function(k)].key== k)
		Table[hash_function(k)].key = 0;//Ячейке онулируется
	free(find->info);
	RB_Delete(find);
	return 1;
}
int insert_HT(Item New)
{
	Table[hash_function(New.key)] = New;//Найс вставка)
	return 1;
}
int insert_RB(Node* New)
{
	//Вставка как в бинарное дерево
	Node* prev = EList;
	Node* ptr = Root;
	while (ptr != EList)
	{
		prev = ptr;
		if (New->key < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	New->parent = prev;//Родитель
	if (prev == EList)
	{
		Root = New;
	}
	//Теперь, когда нашли свободный узел выбираем поддерево
	if (New->key < prev->key)
		prev->left = New;
	else
		prev->right = New;
	RB_Insert_Fixup(New);
	return 1;
}

char* getSTR()
{
	char* ptr = NULL;
	ptr = (char*)malloc(1);//Ввод
//Создаем буфер для считыывания
	char buf[81];
	int len = 0, n;
	*ptr = '\0';
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

int RB_Insert_Fixup(Node* x)
{
	while (x->parent->color == RED)//Тк новый элемент красный - ошибка в свойстве 4 (2 красных узла)
	{
		Node* p1 = x->parent;//Родитель
		Node* pp = p1->parent;//Дедушка
		Node* p2 = NULL;//Второй родитель
		if (pp->left == p1)
		{//Левая ветка от дедана
			p2 = pp->right;
			//Случай 1: Когда p2- Краснный
			if (p2->color == RED)//Просто перекрашивание
			{
				p2->color = BLACK;
				p1->color = BLACK;
				pp->color = RED;
				x = pp;
			}
			else//Случай 2 когда  P2-черный
			{
				if ((p1->right == x))//Соответсвенно случай 2.левый
				{
					x = p1;//Рокировка
					Left_rotate(x);
					p1 = x->parent;
				}
				//Случай 3
				p1->color = BLACK;
				pp->color = RED;
				//Теперь крутим деда вправо и радуемся жизни
				Right_rotate(pp);
			}
		}
		else
		{//p1-правая ветка
			p2 = pp->left;
			//Случай 1: Когда p2- Краснный
			if (p2->color == RED)//Просто перекрашивание
			{
				p2->color = BLACK;
				p1->color = BLACK;
				pp->color = RED;
				x = pp;
			}
			else//Случай 2 когда  P2-черный
			{
				if ((p1->left == x))//Соответсвенно случай 2.правый
				{
					x = p1;//Рокировка
					Right_rotate(x);
					p1 = x->parent;
				}
				//Случай 3
				p1->color = BLACK;
				pp->color = RED;
				//Теперь крутим деда влево и радуемся жизни
				Left_rotate(pp);
			}
		}
		
	}
	Root->color = BLACK;//Если вдруг нарушено свойство 5
	return 1;
}

int RB_Delete(Node* z)
{
	// Удаление производится тем же механизмом, что и удаление BST. Если у Z нет ребенка, то Z удалён.
	// Если Z имеет одного ребенка, Z заменяется его ребенком. Иначе z заменяется на его преемника
	// Если преемник не является прямым ребенком z, то он заменяется сначала на своего собственного ребенка.
	// Затем Z заменяется преемником.
	//
	// Указатель Y используется для отслеживания. В первых двух случаях Y - это Z. В третьем случае Y - преемник Z
	// Итак, в первых двух случаях "Y" удаляется. В третьем случае Y перемещается.
	//
	// Другой указатель X используется для отслеживания узла, который заменяет Y.
	//
	// Так как удаление или перемещение Y может повредить свойства красно-черного дерева,
	// переменная yOriginalColor используется для отслеживания оригинального цвета. Если он ЧЕРНЫЙ, тогда
	// удаление или перемещение - плохо для свойств красно-черного дерева.

			
		Node* y, * x;
		int yOriginalColor;
		y = z;
		yOriginalColor = y->color;

		if (z->left == EList) {// случай 1,2 когда ребенок либо 1 либо  его нет 
			x = z->right;
			rb_replace(z, z->right);
		}
		else if (z->right == EList) {// случай 2 когда ребенок справа 1? 
			x = z->left;
			rb_replace(z, z->left);
		}
		else {//Детей двое
			y = tree_minimum(z->right);//Минимум - самая левая ветка от z(следующий элемемнт)
			yOriginalColor = y->color;//Цвет самого левого узла

			x = y->right;//следующий за y

			if (y->parent == z) {
				x->parent = y;//ЕЕе, просто замена
			}
			else {
				rb_replace(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rb_replace(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		if (yOriginalColor == BLACK) {
			RB_Delete_Fixup(x);
		}
		return 1;
}


void RB_Delete_Fixup(Node* x)
{
	Node* p;
	Node* w;
	while ((x != Root) && (x->color == BLACK))
	{
		p = x->parent;
		//Проверяем в каком поддереве лежит x
		if (x == p->left)//# ЛЕВОЕ НАЧАЛО
		{
			w = p->right;
			//Анализируем все случаи
			if (w->color == RED)
			{// Случай 1 Шаг 1...3
				w->color = BLACK;
				p->color = RED;
				//Крутимся влево
				Left_rotate(p);
				w = p->right;
			}//Переходимк случаям 2..4
			if ((w->left->color == BLACK) && (w->right->color == BLACK))
			{//Случай 2
				w->color = RED;//Забрали краску
				x = p;
			}
			else if (w->right->color == BLACK)
			{//Случай 3
				w->color = RED;
				w->left->color = BLACK;
				Right_rotate(w);
				w = p->right;
			}
			//Случай 4
			w->color = p->color;
			p->color = BLACK;
			w->right->color = BLACK;
			Left_rotate(p);
			x = Root;
		}
		else //#ПРАВОЕ НАЧАЛО
		{
			w = p->left;
			//Анализируем все случаи
			if (w->color == RED)
			{// Случай 1 Шаг 1...3
				w->color = BLACK;
				p->color = RED;
				//Крутимся вправо
				Right_rotate(p);
				w = p->left;
			}//Переходимк случаям 2..4
			if ((w->right->color == BLACK) && (w->left->color == BLACK))
			{//Случай 2
				w->color = RED;//Забрали краску
				x = p;
			}
			else if (w->left->color == BLACK)
			{//Случай 3
				w->color = RED;
				w->right->color = BLACK;
				Left_rotate(w);
				w = p->left;
			}
			//Случай 4
			w->color = p->color;
			p->color = BLACK;
			w->left->color = BLACK;
			Right_rotate(p);
			x = Root;
		}
	}
	x->color = BLACK;
}

Node* tree_minimum(Node* x) {
	while (x->left != EList) {
		x = x->left;
	}
	return x;
}
void rb_replace(Node* u, Node* v) {
	if (u->parent == EList) {
		Root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}


int getInt()
{
	int x=1;
	int n;
	do
	{
		n = scanf("%d", &x);
		if (n < 0)//EOF
		{
			printf("\nEOF detected");
			return -1;
		}
		if (n == 0)
		{
			printf("\nError input");
			printf("\nRepeat please:");
			scanf_s("%*[^\n]");
		}
		else
		{
			if (x < 0)
			{
				printf("\nError input");
				printf("\nRepeat please:");
				scanf_s("%*[^\n]");
			}
		}
	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return x;
}
