
#define _CRT_SECURE_NO_WARNINGS
#define White 0
#define Gray 1
#define Black 2

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <ctime>
#include <time.h>

typedef struct vertex { //Данные вершины
	int color;//цвет
	struct adjList* pred;
	int d;
	int f;
	int num; //Номер
	int x, y; //Координаты
} vertex;

//  info about vertex, which this list represents
typedef struct adjList { //Вершины
	int N; //Количество смежных вершин
	struct vertex* vertex; //Указатель на данные вершины
	struct adjNode* head; //Указатель на 1 смежную вершину
	struct adjList* next; //Указатель на следующую вершину
} adjList;

typedef struct adjNode { //Информация о ребрах
	struct adjList* V; //Сама вершина
	int N_reserv;//Вершина для записи в файл
	struct adjNode* next; //Указатель на следующую смежную вершину
} adjNode;

typedef struct Graph {//Граф
	int N; //Количество вершин
	char* fname;//Имя файла
	struct adjList* adjList; //Указатель на 1 вершину
} Graph;
typedef struct Item_DFS {
	vertex* V;
	struct Item_DFS* Next;
}Item_DFC;
const char* msgs[] = { "0->Exit","1->Insert Vertex","2->Insert Edge","3->Delete Vertex","4->Sort",
"5->Insert Random Vertex","6->Insert Random Edges","7->Show Graph" ,"8->Timing",};
bool Acyclic;
int time_set;
Item_DFS* DFS_LIST;
int N_V;//Дополнить

int T_Add_Random_E(Graph* G, int N);
int T_Add_Random_V(Graph*, int);
void Redistribution(Graph* G);
void Destruction(Graph* G);
int getInt(void);
void OutMatr(Graph* G);
void output_L(Item_DFS* Sort_L);
adjList* Random_E(Graph* G);
vertex* Generate_Random_V(Graph* G);
void DeleteList(Item_DFS* DFS_List);
int Delete_V(Graph*, int);
void Del_free_V(adjList* V);
int Del_Incoming_Edges(Graph* G, adjList* V_D);
adjNode* find_E(adjNode*, adjNode*, adjList*);
adjList* find(Graph*, int );
int Insert_V(Graph*, adjList*);
int Delete_E(adjList*);
int D_Add_Random_V(Graph* G);
int D_Add_Random_E(Graph* G);
int D_Load(Graph*);
int D_Insert_V(Graph*);
int D_Insert_E(Graph*);
void Insert_E(Graph* G, adjList* V1, adjList* V2);
int Check_E(adjList* V1, adjList* V2);
int D_Delete_V(Graph*);
int D_Sort(Graph*);
int D_Show(Graph*);
int D_Timing(Graph*);
int Save(Graph* G);
int (*Function_Graf[])(Graph*) = { NULL,D_Insert_V,D_Insert_E,D_Delete_V,D_Sort,D_Add_Random_V,D_Add_Random_E,D_Show,D_Timing};
int dialog(void);
char* getSTR(void);
Item_DFS* DFS(Graph*);
int DFC_Visit(Graph*, adjList*);

int main()
{
	int rc;
	Graph Dracula = {0,NULL,NULL};
	if (D_Load(&Dracula) == 0)
		return 0;
	Redistribution(&Dracula);
	while (rc = dialog())
	{
		if (!Function_Graf[rc](&Dracula))
			break;
	}
	Save(&Dracula);
	Destruction(&Dracula);
	printf("\nThis all. Bye!");
	return 0;
}
void Destruction(Graph* G)
{
	adjList* curr = G->adjList;
	while (curr != NULL)
	{
		adjList* tmp = curr;
		curr = curr->next;
		Del_free_V(tmp);
	}
	free(G->fname);
}
int D_Show(Graph* G)
{
	printf("\n");
	printf("\nAcyclic Graph:\n");
	OutMatr(G);
	return 1;
}
void OutMatr(Graph* G)
{
	adjList* curr = G->adjList;
	int** a = (int**)calloc(G->N, sizeof(int*));
	for  (int i = 0; i < G->N; ++i)
	{
		a[i] = (int*)calloc(G->N,sizeof(int));
	}
	for(int i =0;i < G->N;++i)
	{
		printf("|");
		adjNode* Node = curr->head;
		while (Node != NULL)
		{ 
			int k = 0;
			adjList* tmp = G->adjList;
			while ((tmp!=NULL)&&(++k)&&(tmp != Node->V))
			{
				tmp = tmp->next;
			}
			a[i][k-1] = 1;
			Node = Node->next;
		}
		curr = curr->next;
	}
	printf("|\n");
	curr = G->adjList;
	for (int i = 0; i < G->N; i++)
	{
		printf("|");
		printf("|Vertex %d [%3.d,%3.d]|", curr->vertex->num, curr->vertex->x, curr->vertex->y);
		for (int j = 0; j < G->N; j++)
		{
			printf("%d ", a[i][j]);
		}
		printf("|\n");
		curr = curr->next;
	}
	for (int i = 0; i < G->N; ++i)
	{
		free(a[i]);
	}
	free(a);
}
int D_Sort(Graph* G)
{
	Item_DFS* Sort_L = NULL;
	Sort_L = DFS(G);
	output_L(Sort_L);
	DeleteList(Sort_L);
	return 1;
}
void output_L(Item_DFS* Sort_L)
{
	Item_DFS* curr = Sort_L;
	while (curr != NULL)
	{
		printf("\n|Vertex %d [%d,%d]|", curr->V->num, curr->V->x, curr->V->y);
		curr = curr->Next;
	}
}
int D_Insert_E(Graph*G)
{
	printf("\nWrite two exiting Vertex");
	int Ver1, Ver2;
	printf("\nFirst Vertex:");
	Ver1 = getInt();
	if (Ver1 == -1)
		return 0;
	printf("\nFirst Vertex:");
	Ver2 = getInt();
	if (Ver2 == -1)
		return 0;
	//Проверим на подлинность
	adjList* V1 = find(G, Ver1);
	if (V1 == NULL)
		return 1;
	adjList* V2 = find(G, Ver2);
	if (V2 == NULL)
		return 1;
	if (Check_E(V1, V2) < 0)
	{
		printf("This Edges already exists!!!!");
		return 1;
	}
	Insert_E(G, V1, V2);
	V1->N += 1;
	Item_DFS* Peshka_Revolution = DFS(G);//Что-то должен выдать
	if (Peshka_Revolution == NULL)
	{
		printf("\nCyclic!!!!!");//Разурушаем наш список.
		Delete_E(V1);
		V1->N -= 1;
	}
	DeleteList(Peshka_Revolution);
	return 1;
}
int Delete_E(adjList* V1)
{
	adjNode* curr = V1->head;
	V1->head = curr->next;
	free(curr);
	return 1;
}
int Check_E(adjList* V1, adjList* V2)
{
	adjNode* curr = V1->head;
	while (curr != NULL)
	{
		if (curr->V == V2)
		{
			return -1;
		}
		curr = curr->next;
	}
	return 1;
}
void Insert_E(Graph* G, adjList* V1, adjList* V2)
{
	adjNode* NewE = NULL;
	NewE = (adjNode*)calloc(1, sizeof(adjNode));
	NewE->V = V2;
	NewE->next = V1->head;
	V1->head = NewE;
}

adjList* find(Graph* G, int Ver)
{
	adjList* V = G->adjList;
	for (int j = 0; j < G->N; ++j)
	{
		if (V->vertex->num == Ver)//Нашли вершину
		{
			return V;
		}
		V = V->next;
	}
	printf("\nA Vertex wasn't found");
	return NULL;
}

int D_Add_Random_V(Graph* G)
{
	int N;
	printf("How meny vertexes do you want to generate:");
	N = getInt();
	if (N < 0)
		return 1;
	vertex* V = NULL;
	adjList* List_V = NULL;
	int count=0;
	for (int i = 0; i < N; ++i)
	{
		V = Generate_Random_V(G);
		if (V == NULL)
			continue;
		List_V = (adjList*)calloc(1, sizeof(adjList));
		List_V->vertex = V;
		Insert_V(G, List_V);
		List_V = NULL;
		V = NULL;
		count++;
	}
	printf("Was add |%d| Vertex into Graph",count);
	return 1;
}
//Нужно добавить рандом ребра
int D_Add_Random_E(Graph* G)
{
	int N;
	printf("How meny edges do you want to generate:");
	N = getInt();
	if (N < 0)
		return 1;
	adjList* V1 = NULL;
	adjList* V2 = NULL;
	int count=0;
	for (int i = 0; i < N; ++i)
	{
		V1 = Random_E(G);
		if (V1 == NULL)
			continue;
		V2 = Random_E(G);
		if (V2 == NULL)
			continue;
		if (Check_E(V1, V2) < 0)
			continue;
		Insert_E(G, V1, V2);
		V1->N += 1;
		Item_DFS* Peshka_Revolution = DFS(G);//Что-то должен выдать
		if (Peshka_Revolution == NULL)
		{
			Delete_E(V1);
			V1->N -= 1;
			continue;
		}

		DeleteList(Peshka_Revolution);
		count++;
	}
	printf("Was add |%d| Edges into Graph", count);
	return 1;
}
adjList* Random_E(Graph* G)
{
	adjList* curr = G->adjList;
	int count = rand() % G->N;
		while (curr != NULL && count != 0)
		{
			curr = curr->next;
			count--;
		}
		//Нашли веришинку
		if (curr == NULL)
			return NULL;
		return curr;
}
vertex* Generate_Random_V(Graph* G)
{
	vertex* V = NULL;
	V = (vertex*)calloc(1, sizeof(vertex));
	V->x = rand() % 99 - 49;
	V->y = rand() % 99 - 49;
	adjList* find = G->adjList;
	for (int i = 0; i < G->N; ++i)
	{
		if ((V->x == find->vertex->x) && (V->y == find->vertex->y))
		{
			free(V);
			return NULL;
		}
		find = find->next;
	}
	V->num = G->N;
	return V;
}
Item_DFS* DFS(Graph* G)
{
	adjList* ptr = G->adjList;
	for (int i = 0; i < G->N; i++)
	{
		ptr->vertex->color= White;
		ptr->vertex->pred = NULL;
		ptr = ptr->next;
	}
	DFS_LIST = NULL;
	Acyclic = false;
	time_set = 0;
	ptr = G->adjList;
	for (int i = 0; i <G->N ; i++)
	{
		if (ptr->vertex->color == White)
		{
			DFC_Visit(G, ptr);
			if (Acyclic == true)
			{
				DeleteList(DFS_LIST);
				return NULL;
			}
		}
		ptr = ptr->next;
	}
	return DFS_LIST;//Затем не забываем врубить функцию по очистке стека)
}
int DFC_Visit(Graph* G,adjList* ptr)
{
	ptr->vertex->color = Gray;
	time_set += 1;
	ptr->vertex->d = time_set;
	adjNode* curr = ptr->head;
	for (int j = 0; j < ptr->N; ++j)//Бегаем по ребрам
	{
		if (curr->V->vertex->color == White)
		{
			curr->V->vertex->pred = ptr;//pred[v] = u
			DFC_Visit(G,curr->V);
		}
		else 
		{
			if (curr->V->vertex->color == Gray)
			{
				Acyclic = true;
			}
		}
		curr = curr->next;
	}
	ptr->vertex->color = Black;
	time_set += 1;
	ptr->vertex->f = time_set;
	//Вставка
	Item_DFS* New = (Item_DFS*)calloc(1,sizeof(Item_DFS));
	New->V = ptr->vertex;
	New->Next = DFS_LIST;
	DFS_LIST = New;
	if (time_set == 2 * (G->N))
		return 1;
}

void DeleteList(Item_DFS* DFS_List)
{
	Item_DFS* tmp = NULL;
	while (DFS_List != NULL)
	{
		tmp = DFS_List;
		DFS_List = DFS_List->Next;
		free(tmp);
	}
}

int D_Load(Graph* G)
{
	printf("Input file name:");
	char* fname = getSTR();
	if (fname == NULL)
		return 0;
	
	int len = strlen(fname);
	realloc(fname, len + 5);
	strcat(fname, ".txt");
	FILE* f;
	G->fname = fname;
	fopen_s(&f, fname, "r+");
	adjList* ptr = NULL;
	if (f != 0)
	{
		printf("\nFile was found!");;
		fscanf(f, "%d ", &G->N);
		if (G->N > 0) {
			G->adjList = (adjList*)calloc(1, sizeof(adjList));
			G->adjList->vertex = (vertex*)calloc(1, sizeof(vertex));
			ptr = G->adjList;
			while (fscanf(f, "%d %d %d %d ", &ptr->N, &ptr->vertex->num, &ptr->vertex->x, &ptr->vertex->y) != EOF) {//ФИКСИТЬ
				if (ptr->N > 0)
				{
					ptr->head = (adjNode*)calloc(1, sizeof(adjNode));
					adjNode* tmpNode = ptr->head;
					tmpNode->next = nullptr;
					for (int i = 0; i < ptr->N; ++i) {
						fscanf(f, "%d ", &tmpNode->N_reserv);
						tmpNode->next = (adjNode*)calloc(1, sizeof(adjNode));
						tmpNode = tmpNode->next;
					}
					free(tmpNode);
					auto* tmp = ptr->head;
					for (int i = 0; i < (ptr->N -1) ; ++i)
						tmp = tmp->next;
					tmp->next = NULL;
				}
				
				ptr->next = (adjList*)calloc(1, sizeof(adjList));
				ptr = ptr->next;
				ptr->vertex = (vertex*)calloc(1, sizeof(vertex));
				N_V++;
			}
			free(ptr);
			N_V--;
			auto* tmp = G->adjList;
			for (int i = 0; i < G->N - 1; ++i)
				tmp = tmp->next;
			tmp->next = NULL;
		}
	}
	else
	{
		printf("\nFile with the specified name does not exist\n\nFile creation...\n\nFile was created successfully\n");
		fopen_s(&f, fname, "w+b");
	}
	fclose(f);
	//Перераспределение указателей на вершины графа
	printf("\nSize of your graph: %d\n", G->N);
	return 1;
}

void Redistribution(Graph* G)
{
	adjList* curr = G->adjList;
	while (curr != NULL)
	{
		adjNode* Node = curr->head;
		while (Node != NULL)
		{
			Node->V = find(G, Node->N_reserv);
			Node = Node->next;
		}
		curr = curr->next;
	}
}

int Save(Graph* G)
{
	FILE* FG;
	printf("Press enter to save Graph");
	fflush(stdin);//Чистим поток
	char press;
	scanf("%c", &press);
	if (press != '\n') return 1;
	fopen_s(&FG,G->fname, "w+");
	adjList* curr = G->adjList;
	fprintf(FG, "%d ", G->N);
	for (int i = 0; i < G->N; ++i)
	{//Чекнуть везде N - количество ребер
		fprintf(FG, "%d %d %d %d ",curr->N,curr->vertex->num,curr->vertex->x,curr->vertex->y);
		//Запсываем ребра
		adjNode* curr_E = curr->head;
		while (curr_E != NULL)
		{
			fprintf(FG, "%d ", curr_E->V->vertex->num);
			curr_E = curr_E->next;
		}
		curr = curr->next;
	}
	fclose(FG);
	return 1;
}
int D_Delete_V(Graph*G)
{
	printf("\nWrite please namber's vertex:");
	int Ver;
	Ver = getInt();
	if (Ver < 0)
		return 1;
	Delete_V(G, Ver);
	return 1;
}
int Delete_V(Graph* G, int Ver)
{
	//Шаг 0 - найдем вершину и ей предшуствующую в списке
	adjList* pred = NULL;
	adjList* curr = G->adjList;
	while (curr != NULL)
	{
		if (curr->vertex->num == Ver)
			break;
		pred = curr;
		curr = curr->next;
	}
	if (curr == NULL)
	{
		printf("This vertex isn't exists");
		return -1;
	}
	//Шаг 1 - Проибиваем все вершины кроме Ver
	Del_Incoming_Edges(G, curr);
	//Шаг 2 - удаляем вершину
	if (pred == NULL)//первый списка
	{
		G->adjList = curr->next;
		Del_free_V(curr);
	}
	else
	{
		pred->next = curr->next;
		Del_free_V(curr);
	}
	G->N -= 1;
	//N_V - не уменьшается, тк уникальные номер!!!
	return 1;
}

void Del_free_V(adjList* V)
{
	//Шаг 1 - удаяем данные
	free(V->vertex);
	// Шаг 2- удаляем инцендентныен ребра
	adjNode* curr = V->head,* tmp = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	//Шаг 3 - удалаем V
	free(V);
}
int Del_Incoming_Edges(Graph* G,adjList* V_D)
{
	int i;
	adjList* curr = G->adjList;
	adjNode* Pred_E = NULL;

	for (i = 0; i < G->N; ++i)
	{
		if (V_D != curr)//Чутка ускорим процесс, удаляемую вершинку удаляем позже
		{
			
			Pred_E = NULL;
			adjNode* curr_N = curr->head;
			while (curr_N != NULL)
			{
				if (curr_N->V == V_D)
					break;
				Pred_E = curr_N;
				curr_N = curr_N->next;
			}
			if (curr_N != NULL)
			{
				curr->N -= 1;
				if (Pred_E == NULL)//Значит голова списка
				{
					curr->head = curr_N->next;
					free(curr_N);// Гы
				}
				else
				{
					Pred_E->next = curr_N->next;
					free(curr_N);// ГЫГЫГЫГЫ
				}
			}
		}
		curr = curr->next;
	}
	//Теперь Удаляемая вершина не имеет входящих в нее ребер
	return 1;
}
adjNode* find_E(adjNode* pred,adjNode* head, adjList* V_D)
{
	pred = NULL;
	adjNode* curr = head;
	while (curr != NULL)
	{
		if (curr->V == V_D)
			return curr;
		pred = curr;
		curr = curr->next;
	}
	return NULL;//Откза - нет такой входящий дуги
}


int dialog(void)
{
	int rc = 9;
	for (int i = 0; i < 9; ++i)
		printf("\n%s", msgs[i]);
	while (rc >= 9)
	{

		printf("\nMake your choise:");
		rc = getInt();
		if (rc >= 9)
			printf("\nError(<=8)");
		if (rc < 0)
		{
			return 0;
		}
	}
	return rc;
}

int D_Insert_V(Graph* G)
{//Проверка на координату
	printf("\nInput Coordinate x:");
	int x = getInt();
	if (x < 0)
		return 0;
	printf("\nInput Coordinate y:");
	int y = getInt();
	if (y < 0)
		return 0;
	vertex* V = NULL;
	V = (vertex*)calloc(1, sizeof(vertex));//Выделяем вершину
	V->num = N_V;
	V->x = x;
	V->y = y;
	//Проверим на наличе данной вершины
	adjList* find = G->adjList;

	for (int i = 0; i < G->N; ++i)
	{
		if ((V->x ==find->vertex->x)&&(V->y== find->vertex->y))
		{
			printf("This vertex already exist");
			return 1;
		}
		find = find->next;
	}

	//Если вершины такой нет бежим добавлять ее в граф:D
	//1- Создаем новую ячейку в нашем спсике смежностей
	adjList* NewVertex = NULL;
	NewVertex = (adjList*)calloc(1, sizeof(adjList));
	NewVertex->vertex = V;
	Insert_V(G,NewVertex);
	return 1;
}

int Insert_V(Graph* G, adjList* New)
{
	New->next = G->adjList;
	G->adjList = New;
	G->N += 1;
	N_V++;
	return 1;
}

int getInt()
{
	int x = 1;
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
 
int D_Timing(Graph* G_NOT_USE)
{
	Graph G = { 0,NULL,NULL };
	clock_t first, last;
	srand(time(NULL));
	int count = 500,n =10;
	while (n--)
	{ 
		T_Add_Random_V(&G, count);
		printf("\n");
;		T_Add_Random_E(&G, count);
		first = clock();
		Item_DFS* Sort_L = NULL;
		Sort_L = DFS(&G);
		DeleteList(Sort_L);
		last = clock();
		printf("\n| test №%d, time =%ld, volume = %d |\n", 10 - n, (last - first), G.N);
		count += 500;
	}
	Destruction(&G);
	return 1;
}
int T_Add_Random_V(Graph* G, int N)
{
	vertex* V = NULL;
	adjList* List_V = NULL;
	int count = 0;
	for (int i = 0; i < N; ++i)
	{
		V = Generate_Random_V(G);
		if (V == NULL)
			continue;
		List_V = (adjList*)calloc(1, sizeof(adjList));
		List_V->vertex = V;
		Insert_V(G, List_V);
		List_V = NULL;
		V = NULL;
		count++;
	}
	printf("Was add |%d| Vertex into Graph", count);
	return 1;
}
int T_Add_Random_E(Graph* G,int N)
{
	adjList* V1 = NULL;
	adjList* V2 = NULL;
	int count = 0;
	for (int i = 0; i < N; ++i)
	{
		V1 = Random_E(G);
		if (V1 == NULL)
			continue;
		V2 = Random_E(G);
		if (V2 == NULL)
			continue;
		if (Check_E(V1, V2) < 0)
			continue;
		Insert_E(G, V1, V2);
		V1->N += 1;
		Item_DFS* Peshka_Revolution = DFS(G);//Что-то должен выдать
		if (Peshka_Revolution == NULL)
		{
			Delete_E(V1);
			V1->N -= 1;
			continue;
		}

		DeleteList(Peshka_Revolution);
		count++;
	}
	printf("Was add |%d| Edges into Graph", count);
	return 1;
}