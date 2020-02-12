// labaone.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define N  100
int natural(int*);
int inversion(int*k,int c)
{
	*k = 0;
	int a = c;
	while (a != 0)
	{
		a = a / 10;
		*k=*k+1;
	}
	int x = 0;
	int chislo = 0;
	for (int j = 0; j < *k; j++)
	{
		x = 9 - c % 10;
		c = c / 10;
		chislo += pow(10, j) * x;
	}
	return chislo;
}
void vvod(int *numb,int *ind,int n)
{
	int chislo = 0;
	printf("\nHello. Write a elements of a sequence: ");
	for (int i = 0; i < n; i++)
	{
		int c; chislo = 0;
		printf("\nNumber %i: ", i);
		natural(&c);
		int l;
		chislo = inversion(&l,c);
		numb[i] = chislo;
		ind[i] = l;
	}
}
void sort(int a[], int b[],int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (a[j + 1] < a[j])
			{
				int t = a[j + 1];
				a[j + 1] = a[j];
				a[j] = t;
				t = b[j + 1];
				b[j + 1] = b[j];
				b[j] = t;
			}
		}
	}
	
}
void vivod(int *numb,int *ind,int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\n\nIndex|||| %d ||||\nkol-vo: %d\nnumber: %d", i, ind[i], numb[i]);
	}
	printf("\n");
	system("pause");
}
int main()
{
	printf("Write number of created for array(N<100): ");	
	int n;
	natural(&n);
	if ((n < 100)&&(n>0));//Контроль ввода N
	else {
		printf("\nInput ERR, N<100!!");
		return(10);
	}
	int numb[N] = { 0 }; int ind[N] = { 0 };
	vvod(numb, ind,n);
	sort(numb, ind,n);
	vivod(numb, ind, n);
	return 0;
	printf("The End");
}
int natural(int* x)
{
	int n;
	do {
		printf("\nWrite Natural number!: ");
		n = scanf_s("%d", x);
		if (n == 0)
		{
			printf("Input Err!\n");
			scanf_s("%*[^\n]");
		}
		if (*x < 0)
		{
			printf("Input Err!\n");
			scanf_s("%*[^\n]");
			n = 0;
		}
	} while (n == 0);
	n = n < 0 ? -n : n;
	scanf_s("%*[^\n]");
	return n;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
