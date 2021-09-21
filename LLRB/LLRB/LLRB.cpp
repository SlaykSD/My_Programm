// LLRB.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <ctime>
#include <string.h> 

//Расскраска дерева
#define RED 0
#define BLACK 1
typedef struct Info
{
	unsigned int version;//Порядковый номер(предполагаем, что дубликаты существуют)
	float number;
	char* string;
	Info* next; //Информационный список, 
}Info;
typedef struct Node {
	unsigned int key; // неотрицательное целое
	int color; // 1 или 0 зависит от цвета
	Info* info_head;// Указатель на информационные поле
	struct Node* parent, * left, * right;
}Node;


//Организуем EList
Node* EList = (Node*)malloc(sizeof(Node));
Node* Root;
const char* msgs[] = { "0->Exit","1->Insert","2->Search","3->Delete","4->Show","5->Show as TREE","6->Timing RBLL" };
const int Nmsgs = sizeof(msgs) / sizeof(msgs[0]);

void RB_Delete_Fixup(Node*);
void Left_rotate(Node*);
void Right_rotate(Node*);
int D_Load(Node*);
int D_Insert(Node*);
int D_Search(Node*);
int D_Delete(Node*);
int D_Show(Node*);
int D_ShowTREE(Node*);
int D_Timing_RBLL(Node*);
int rb_show(Node*);
int (*Function_RB[])(Node*) = { NULL,D_Insert,D_Search,D_Delete,D_Show,D_ShowTREE,D_Timing_RBLL };
int dialog(void);
Node* tree_minimum(Node*);
void rb_replace(Node*, Node*);
int RB_Delete(Node*);
Node* Find_RB(Node*, int);
Node* Find_RB_Final(int key);
int insert_RB(Node*);
int RB_Insert_Fixup(Node*);
char* getSTR(void);
int getInt(void);
int getFloat(void);
int show_as_tree(int, Node*);

int rb_tear_down(Node*, Node**);
//НОВОЕ
int Find_Ver(int);
Info* getVersion(Node*, int);
Node* rotateLeft(Node*);
Node* rotateRight(Node*);
void flipColors(Node*);
int insert_llrb(Node*);
Node* insert(Node*, Node*);
int delete_llrb(Node*);
Node* deleter(Node*, int);
int min(Node* x);
Info* get(Node*, int);
Node* moveRedRight(Node*);
Node* moveRedLeft(Node*);
Node* deleteMin(Node*);
Node* fixUp(Node*);


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
//Корректые вводы:
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
int getInt()
{
	unsigned int x = 1;
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
	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return x;
}
int getFloat()
{
	float x = 1;
	int n;
	do
	{
		n = scanf("%fl", &x);
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
	} while (n == 0);
	scanf_s("%*[^\n]");
	scanf_s("%*c");
	return x;
}

//Реализация диалогов:
int dialog(void)
{
	int rc = Nmsgs;
	for (int i = 0; i < Nmsgs; ++i)
		printf("\n%s", msgs[i]);
	while (rc >= Nmsgs)
	{

		printf("\nMake your choise:");
		rc = getInt();
		if (rc >= Nmsgs)
			printf("\nError(<%d)", Nmsgs);
		if (rc < 0)
		{
			return 0;
		}
	}
	return rc;
}

int D_Insert(Node* x)
{
	Node* New;
	int key;
	printf("\nWrite key:");
	key = getInt();

	printf("\nWrite Information(String):");
	char* info;
	info = getSTR();
	if (info == NULL)
		return 0;
	printf("\nWrite Information(float):");
	float info_f;
	info_f = getFloat();
	if (info_f == NULL)
		return 0;

	New = (Node*)malloc(sizeof(Node));
	New->color = RED;
	New->key = key;
	New->left = EList;
	New->right = EList;
	Info* Data = (Info*)malloc(sizeof(Info));
	Data->number = info_f;
	Data->string = info;
	Data->next = NULL;
	New->info_head = Data;
	int ver;
	if (!((ver = Find_Ver(key)) >= 0))
	{
		printf("\nDublicate key was not found");
	}
	New->info_head->version = ver + 1;
	insert_llrb(New);
	printf("\nInsert was successful");
	return 1;
}
int D_Delete(Node* x)
{
	printf("\nWrite key:");
	int k = getInt();
	if (k < 0)
	{
		return 0;
	}
	Node* find = Find_RB_Final(k);
	if (find == EList)
	{
		printf("\nERORR: No element");
		return 1;
	}
	delete_llrb(find);
	return 1;
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
	FILE* fd = NULL;
	errno_t err = fopen_s(&fd, fname, "r");
	if (err)
	{
		printf("\n File doesn't exist\n");
		return 0;
	}
	//возвращаем указатель в начало
	rewind(fd);
	//char* info = (char*)calloc(100, sizeof(char));
	//char information[100];
	char* info = (char*)calloc(100, sizeof(char));
	float info_f;
	int k;//id

	while ((fscanf(fd, "%d %fl", &k, &info_f) != EOF) && (fscanf(fd, "%s\n", info) != EOF))
	{
		Node* New;
		New = (Node*)malloc(sizeof(Node));
		New->color = RED;
		New->key = k;
		Info* Data = (Info*)malloc(sizeof(Info));
		Data->number = info_f;
		Data->string = info;
		Data->next = NULL;
		New->info_head = Data;
		int ver;
		if (!((ver = Find_Ver(k)) >= 0))
		{
			printf("\nDublicate key was not found");
		}
		New->info_head->version = ver + 1;
		New->left = EList;
		New->right = EList;
		info = (char*)calloc(100, sizeof(char));
		insert_llrb(New);
	}
	free(info);
	free(fname);
	fclose(fd);
	return 1;
}
int D_Show(Node*) {
	rb_show(Root);
	return 1;
}
int D_ShowTREE(Node*) {
	puts("Tree:");
	show_as_tree(0, Root);
	return 1;
}
int D_Timing_RBLL(Node*)
{
	printf("Yah, I'mhere thre");
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
			Info* Data = (Info*)malloc(sizeof(Info));
			Data->next = NULL;
			x->info_head = Data;
			int ver = Find_Ver(k);
			x->info_head->version = ver + 1;
			insert_llrb(x);
				++i;

		}
		m = 0;
		first = clock();//Зассекаем время
		for (i = 0; i < 10000; ++i) {
			if (Find_RB(Root, key[i]) != EList) {
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
	/*rb_tear_down(Root, &Root);
	Root = EList;*/
	return 1;
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
	Node* res = Find_RB_Final(key);
	if (res->info_head->next != NULL)
	{
		printf("\nInput version: ");
		int ver = getInt();
		Info* version = getVersion(res, ver);
		if (version != NULL)
		{
			printf("\nYour full element: [Key: %d,Color %d, Version %d, String %s,Float %fl]",
				res->key, res->color, ver, version->string, version->number);
		}
		else
		{
			printf("\nThis element doesn't exist");
		}
	}
	return 1;
}

//Основыне фунцкии
Node* rotateLeft(Node* h)
{
	Node* x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
	//Node* y = x->right;
	//Node* p = x->parent;
	////Переустанавливаем правое поддерево
	//x->right = y->left;
	////Переустанавливаем родительский узел левого поддерева 
	//if (y->left != EList)
	//	y->left->parent = x;
	////Формируем связь родитель - правый ребенок
	//y->parent = p;
	//if (p == EList)
	//{
	//	Root = y;
	//}
	//else
	//{
	//	if (p->left == x)
	//		p->left = y;
	//	else
	//		p->right = y;
	//}
	////Формируем связь y-x
	//y->left = x;
	//x->parent = y;

	//y->color = x->color;
	//x->color = RED;
	//return y;
}
Node* rotateRight(Node* h)
{
	Node* x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
	/*Node* p = x->parent;
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

	y->color = x->color;
	x->color = RED;
	return y;*/
}
void flipColors(Node* h)//инверс цветов
{
	h->color = h->color == RED ? BLACK : RED;
	h->left->color = h->left->color == RED ? BLACK : RED;
	h->right->color = h->right->color == RED ? BLACK : RED;
}
int insert_llrb(Node* curr)
{
	if (curr->info_head->version > 0)
	{
		Node* ptr = Root;
		while (ptr != EList)
		{
			if (ptr->key == curr->key) break;
			if (curr->key < ptr->key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		Info* head = ptr->info_head;
		while (head->next != NULL)
			head = head->next;
		head->next = curr->info_head;
		curr->info_head = NULL;
		free(curr);
		return -1; //Вставка данных в узел, из-за дубиката
	}
	else
	{
		Root = insert(Root, curr);
		Root->color = BLACK;
		Root->parent = EList;
	}
	return 1; //Успешно завершена вставка нового узла
}
bool isRed(Node* ptr) { return ptr->color == RED; }

Node* insert(Node* h, Node* curr)
{
	if (h == EList) return curr;
	if (isRed(h->left) && isRed(h->right)) flipColors(h);

	if (h->key > curr->key)
		h->left = insert(h->left, curr);
	else
		h->right = insert(h->right, curr);

	if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
	return h;
}

int delete_llrb(Node* curr)
{
	if (curr->info_head->next != NULL)
	{
		Info* ptr = curr->info_head;
		curr->info_head = curr->info_head->next;
		ptr->next = NULL;
		free(ptr);
		return -1; //Таким образом удаилась последняя версия узла (Первая версия) ЫЫ т.к чем больше версия, тем элемент новее
	}
	else
	{
		Root = deleter(Root, curr->key);
		Root->color = BLACK;
		Root->parent = EList;
	}
	return 1;
}
Info* getVersion(Node* curr, int ver)
{
	Info* ptr = curr->info_head;
	while (ptr != NULL && ptr->version != ver)
		ptr = ptr->next;
	return ptr;
}
// Исправление правых красных связей
Node* fixUp(Node* h)
{
	if (isRed(h->right))
		h = rotateLeft(h);
	// Вращение 2-ой красной пары пары
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	// Балансировка узла с 4-я потомками
	if (isRed(h->left) && isRed(h->right))
		flipColors(h);
	return h;
}
Node* deleteMin(Node* h)
{
	if (h->left == EList) return EList;
	if (!isRed(h->left) && !isRed(h->left->left))
		h = moveRedLeft(h);
	h->left = deleteMin(h->left);
	return fixUp(h);
}
Node* moveRedLeft(Node* h)
{
	flipColors(h);
	if (isRed(h->right->left))
	{
		h->right = rotateRight(h->right);
		h = rotateLeft(h);
		flipColors(h);
	}
	return h;
}
Node* moveRedRight(Node* h)
{
	flipColors(h);
	if (isRed(h->left->left))
	{
		h = rotateRight(h);
		flipColors(h);
	}
	return h;
}
Info* get(Node* x, int key)
{
	if (x == EList)        return NULL;
	if (key == x->key) return x->info_head;
	if (key < x->key) return get(x->left, key);
	else                  return get(x->right, key);
}
int min(Node* x)
{
	if (x->left == EList) return x->key;
	else                return min(x->left);
}
Node* deleter(Node* h, int key)
{
	if (key < h->key)
	{
		if (!isRed(h->left) && !isRed(h->left->left))
			h = moveRedLeft(h);
		h->left = deleter(h->left, key);
	}
	else
	{
		if (isRed(h->left))
			h = rotateRight(h);
		if (key == h->key && (h->right == EList))
			return EList;
		if (!isRed(h->right) && !isRed(h->right->left))
			h = moveRedRight(h);
		if (key == h->key)
		{
			h->info_head = get(h->right, min(h->right));
			h->key = min(h->right);
			h->right = deleteMin(h->right);
		}
		else h->right = deleter(h->right, key);
	}
	return fixUp(h);
}
Node* Find_RB_Final(int key)
{
	Node* x = Root;
	x = Find_RB(x, key);
	if (x == EList)
	{
		printf("\nThis element wasn't found in LLRB-TREE   :C");
	}
	else
	{
		printf("\nThis element was found in LLRB-TREE   C:");
		printf("\nFirst element have a Key-%d\nInfo:|%s %fl|", key, x->info_head->string, x->info_head->number);
		return x;
	}
	printf("\nThis element doesn't exists in LLRB_WH   C:");
	return x;
}

Node* Find_RB(Node* ptr, int key)
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
//Поиск версии в списке
int Find_Ver(int key)
{
	Node* ptr = Root;
	int res = -1;
	while (ptr != EList)
	{
		if (ptr->key == key)
		{
			Info* head = ptr->info_head;
			while (head->next != NULL)
				head = head->next;
			res = head->version;
			break;
		}
		if (key < ptr->key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	return res;
}
//Показ всех узлов в обратном следовании ключей C:
int rb_show(Node* x) {
	if (x != EList) {
		rb_show(x->left);
		rb_show(x->right);
		printf("[key: %d | ", x->key);
		Info* head = x->info_head;
		while (head != NULL)
		{
			printf("version: %d, string: %s, float: %fl | ", head->version, head->string, head->number);
			head = head->next;
		}
		printf("]\n");
	}
	return 1;
}

int show_as_tree(int count, Node* nd) {
	int i = 0;
	if (nd == EList) return 1;
	show_as_tree(count + 1, nd->left);
	for (; i < count; ++i) {
		printf("   ");
	}
	printf("%d;%d;%s;%fl\n", nd->key, nd->color, nd->info_head->string, nd->info_head->number);
	show_as_tree(count + 1, nd->right);
	return 1;
}
int rb_tear_down(Node* ptr, Node** root) {
	if (ptr == EList) return 1;
	rb_tear_down(ptr->left, root);
	rb_tear_down(ptr->right, root);
	delete_llrb(ptr);
	return 1;
}


