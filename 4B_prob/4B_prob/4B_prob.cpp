#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
    int          key;
    long         offset; //место первой буквы в ПЗУ
    int          len; //длина строки
} Item;

typedef struct Table {
    struct Item* first;
    int n;
    int SZ;
    FILE* fd;
} Table;

int insert(Table* ptab, int k, char* str);
char* findInfo(Table ptab, int k);
int D_Find(Table* ptab);
int find(Table ptab, int k);
int create(Table* ptab, char* fname, int sz);
int dialog(const char*[]);
int D_Add(Table*);
int D_Find(Table*);
int D_Show(Table*);
int D_Delete(Table*);
int D_Load(Table*);
int save(Table*);
void deltab(Table*);
int load(Table* , char* );
int create(Table*,char*,int);
int (*fptr[])(Table*) = { NULL, D_Add, D_Find, D_Delete, D_Show };
const char* msgs[] = {"0-> Exit","1->Add","2-> Find","3-> Delete","4-> Show"};
const char* NMsgs = 0;

char* getStr() {
    char* ptr = (char*)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf_s("%80[^\n]", buf, 81);
        if (n < 0) {
            free(ptr);
            return NULL;
        }
        else
            if (n) {
                len += strlen(buf);
                ptr = (char*)realloc(ptr, len + 1);
                int k = strcspn(buf, "\0"); // длина слова
                int l = strlen(ptr) + k + 1;
                strncat_s(ptr, l, buf, k);
            }
    } while (n > 0);
    scanf_s("%*c");
    return ptr;
}
int getInt(int* pn) {
    const char* errmsg = "";
    int n;
    do {
        puts(errmsg);
        errmsg = "Repeat input";
        n = scanf_s("%d", pn);
        if (n < 0)
            return 0;
        scanf_s("%*[^\n]");
        scanf_s("%*c");
    } while (n == 0);
    return 1;
}

int main()
{
    int rc;
    Table ptab = {NULL,0,0,NULL};
    if (D_Load(&ptab) == 0)
        return 1;
    while (rc = dialog(msgs))
        if (!fptr[rc](&ptab))
            break;
    save(&ptab);
    deltab(&ptab);
    printf("Bye,Bye, Nigga!");
    return 0;
}
int D_Add(Table* ptab)
{
    int k, rc, n;
    char* info = NULL;
    printf("Enter key: -->");
    n = getInt(&k);
        if (n == 0)
            return 0; 
    printf("Enter info:\n");
    info = getStr(); 
    if (info == NULL)
        return 0; 
    rc = insert(ptab, k, info);
    free(info); 
    printf("\nOK");
    return 1;
}
int insert(Table* ptab, int k, char* str)
{
    if (find(*ptab, k) >= 0)
        return 1; 
    if (ptab->n >= ptab->SZ)
        return 2; 
    ptab->first[ptab->n].key = k; 
    ptab->first[ptab->n].len = strlen(str) + 1; 

    fseek(ptab->fd, 0, SEEK_END);
    ptab->first[ptab->n].offset = ftell(ptab->fd); 
    fwrite(str, sizeof(char), ptab->first[ptab->n].len, ptab->fd);
    ++(ptab->n); 
    return 0;
}
int D_Find(Table* ptab)
{
    char* info = NULL;
    int k, n, i;
    puts("Enter key: -->");
    n = getInt(&k);
    if (n == 0)
        return 0;
    info = findInfo(*ptab, k);
    if (info) {
        printf("key = %d, info = \"%s\"\n", k, info);
        free(info);
    }
    else
        printf("Item %d was not found\n", k);
    return 1;
}
char* findInfo(Table ptab, int k)
{
    char* info = NULL;
    int i = find(ptab, k);
    if (i >= 0) {
        info = (char*)malloc(ptab.first[i].len);
        fseek(ptab.fd, ptab.first[i].offset, SEEK_SET);
        fread(info, sizeof(char), ptab.first[i].len, ptab.fd);
    }
    return info;
}
int find(Table ptab, int k)
{
    int i = 0;
    for (; i < ptab.n; ++i)
        if (ptab.first[i].key == k)
            return i;
    return -1;
}
int D_Show(Table*)
{
    return 1;
}
int D_Delete(Table*)
{
    return 1;
}
void deltab(Table* tab)
{
    free(tab->first);
    free(tab->fd);
}
int D_Load(Table* tab)
{
    printf("\nInput please name's file: ");
    char* fname =getStr();
    if (fname == NULL)
        return 0;
    int SZ;
    //Пытаемся загрузить табличку
    if (load(tab, fname) == 0)
    {
        printf("\nYour tab doesn't exists\n....\nCreated NEW С:");
        printf("Enter a size the table: ");
        if (getInt(&SZ) == 0)
            return 0;
        create(tab, fname, SZ);
    }
    free(fname);
    return 1;
}
int dialog(const char* msgs[]) {
    const char* errmsg = "";
    int rc;
    int i, n;
    do {
        puts(errmsg);
        errmsg = "You're wrong, please re input!";
        for (i = 0; i < 5; ++i)
            puts(msgs[i]);
        puts("Your chose: --> ");
        n = getInt(&rc);
        if (n == 0)
            rc = 0;
    } while (rc < 0 || rc >= 5);
    return rc;
}

int load(Table* tab, char* fname)
{
    int len = strlen(fname) + 5;
    fname = (char *)realloc(fname,len);
    strcat(fname, ".tab");
    fopen_s(&tab->fd,fname,"r+b");
    if (tab->fd == NULL)
        return 0;
    fread(&tab->SZ, sizeof(int), 1, tab->fd);
   //Выделяем память под размерчик
    tab->first = (Item*)calloc(tab->SZ,sizeof(int));
    fread(&tab->n, sizeof(int), 1, tab->fd);//Считали тек. размер
    fread(tab->first, sizeof(Item), tab->n, tab->fd);//Считали всю табличку
    return 1;
}

int create(Table* ptab, char* fname, int sz)
{

    ptab->SZ = sz;
    ptab->n = 0;
    if (fopen_s(&(ptab->fd), fname, "w+b") != 0) {
        ptab->first = NULL;
        return 0;
    }
    ptab->first = (Item*)calloc(ptab->SZ, sizeof(Item));
    fwrite(&ptab->SZ, sizeof(int), 1, ptab->fd);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->SZ, ptab->fd);
    return 1;
}
int save(Table* ptab)
{
    fseek(ptab->fd, sizeof(int), SEEK_SET);
    fwrite(&ptab->n, sizeof(int), 1, ptab->fd);
    fwrite(ptab->first, sizeof(Item), ptab->n, ptab->fd);
    fclose(ptab->fd);
    ptab->fd = NULL;
    return 1;
}