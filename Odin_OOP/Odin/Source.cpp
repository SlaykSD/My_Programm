
#include <iostream>
#include "Header.h"
namespace Prog1 {
	int getint(int& a)
	{
		const char* msg = "";
		bool success = false;
		do
		{
			success = false;
			std::cout << msg;
			std::cin >> a;
			if (!(std::cin.fail()))
			{
				std::cin.ignore(32767, '\n');
				success = true;
			}
			else
			{
				msg = "Incorrect input, try again(INTEGER):  ";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			std::cout << "" << std::endl;
		} while (!success);
		return 1;
	}
	int getNat(int& a)
	{
		const char* msg = "";
		bool success = false ;
		do
		{
			success = false;
			std::cout << msg;
			std::cin >> a;
			if (!(std::cin.fail())&&(a>0))
			{
				std::cin.ignore(32767, '\n');
				success = true;
			}
			else
			{
				msg = "Incorrect input, try again(Natural):  ";
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			}
			std::cout << "" << std::endl;
		} while (a<0 || !success);
		return 1;
	}
	Mat* get_Mat()
	{
		const char* pr = ""; 
		Line** lines = nullptr; 
		int m=0,n=0; 
		Mat* Matrix = new Mat;
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNat(m) < 0)
				return nullptr;
			std::cin.sync();
		} while (m < 1);
		try {
			lines = new Line * [m];
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			erase(Matrix);
			return nullptr;
		}
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of latitude: --> ";
			pr = "You are wrong; repeat please!";
			if (getNat(n) < 0)
				return nullptr;
			std::cin.sync();
		} while (n < 1);
		Matrix->lines = lines; 
		Matrix->m = m;
		Matrix->n = n;
		for (int i = 0; i < Matrix->m; i++)
			Matrix->lines[i] = nullptr;
		return Matrix;
	}
	Mat* Input(Mat* M)
	{
		int item;
		Line* Elem;
		const char* msg = "";
		int count =-1;
		const char* pr = "";
		int k = 0;
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter quatity of number: --> ";
			pr = "You are wrong; repeat please!";
			if (getNat(count) < 0)
				return nullptr;
			std::cin.sync();
		} while ((count < 0)||(count > (M->m * M->n)));
		do {
			std::cout << msg << std::endl;
			std::cout << "Please input <<INFO>>: ";
			if (getint(item) < 0)
				return nullptr;
			try {
				Elem = new Line;
			}
			catch (std::bad_alloc & ba)
			{
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				return nullptr;
			}
			Elem->next = nullptr;
			Elem->i = 0;
			Elem->j = 0;
			Elem->info = item;
			Elem->numbers = 1;
			Print_size(M, Elem);
			if (!find(M, Elem))
			{
				std::cout << "This element alraedy exist" << std::endl;
				k++;
				msg = "Next information";
				continue;
			}
			msg = "Next information";
			addLine(M, Elem);
			k++;
		} while (k < count);
	}
	int find(Mat* M, Line* Elem)
	{
		Line* ptr = M->lines[Elem->i];
		while (ptr != nullptr)
		{
			if (ptr->j == Elem->j)
				return 0;
			ptr = ptr->next;
		}
		return 1;
	}
	int Print_size(Mat* M,Line* Elem){
		do {
			std::cout << "a[i,j]: i = ";
			if (getint(Elem->i) < 0)
				return -1;
			if (Elem->i >= M->m)
				std::cout << "Incorrect unput,repet please: " << std::endl;
			std::cin.clear();
		} while ((Elem->i >= M->m) || Elem->i<=0);
		do{
			std::cout << "a[i,j]: j = ";
			if (getint(Elem->j) < 0)
				return -1;
			if (Elem->j >= M->n)
				std::cout << "Incorrect unput,repet please: " << std::endl;
			std::cin.clear();
		} while ((Elem->j >= M->n) || Elem->j <= 0);
		return 0;
	}
	void addLine(Mat* M, Line* L)
	{
		if (M->lines[L->i] == nullptr)
		{
			M->lines[L->i] = L;
			L->numbers = 1;
		}
		else
		{ 
			Line* ptr = M->lines[L->i];
			if ((ptr->next == nullptr) && (ptr->j < L->j))
			{
				ptr->next = L;
				if (ptr->info == L->info)
				{
					L->numbers = 2;
					ptr->numbers += 1;
				}
				return;
			}
			else
			{
				if (ptr->next == nullptr)
				{
				L->next = ptr;
				M->lines[L->i] = L;
				if (ptr->info == L->info)
					L->numbers = 2, ptr->numbers = 2;
				else
					L->numbers = 1;
				return;
				}
			}
			int count = find(M->lines[L->i], L->info);
			Line* tmp = M->lines[L->i];
			int joke = 0;;
			while ((ptr->next != nullptr) && (L->j > ptr->j))
			{

				if (joke > 0)
					tmp = tmp->next;
				joke++;
				ptr = ptr->next;
			} 
			if ((ptr->j > L->j))
			{
				if (tmp == M->lines[L->i]&&(M->lines[L->i]->j>(L->j)))//это корень
				{
					L->next = ptr;
					M->lines[L->i] = L;
					L->numbers = ptr->numbers;
				}
				else {
					L->next = ptr;
					tmp->next = L;
				}
			}
			else
			{
				ptr->next = L;
			}
			if (count)
			{
				NubmberUp(M->lines[L->i], L->info, count);
			}
		}
	}
	int NubmberUp(Line* ptr, int X, int number)
	{
			while (ptr != nullptr)
			{
				if (X == ptr->info)
					ptr->numbers = number + 1;
				ptr = ptr->next;
			}
			return 0;
	}
	int find(Line* ptr, int X)
	{
		while (ptr != nullptr)
		{
			if (X == ptr->info)
				return ptr->numbers;
			ptr = ptr->next;
		}
		return 0;
	}
	int* Task(Mat* M)
	{
		int* a;
		try {
			a = new int [M->m];
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << "------ too many items : " << ba.what() << std::endl;
			return nullptr;
		}
		for (int i=0; i < M->m; ++i)
		{
			if (M->lines[i] != nullptr) {
				Line* ptr = M->lines[i];
				double ex = ptr->numbers;
				while (ptr != nullptr)
				{
					if (ex < ptr->numbers)
						ex = ptr->numbers;
					ptr = ptr->next;
				}
				a[i] =ex;
			}
			else
			{
				a[i] = 0;
			}
		}
		return a;
	}
	void output(Mat*M, int a[])
	{
		for (int i = 0; i < M->m; ++i)
		{
			Line* ptr = M->lines[i];
			int k = 0;
			while (ptr != nullptr)
			{
				while (k < ptr->j)
				{
					std::cout << "0 ";
					k++;
				}
				std::cout << ptr->info <<" ";
				ptr = ptr->next;
				k++;
			}
			while (k < M->n) {
				std::cout << "0 ";
				k++;
			}
			std::cout<<""<< std::endl;
		}
		output_V(a,M->m);
		delete[] a;
	}
	void output_V(int a[], int size)
	{
		std::cout << "" << std::endl;
		std::cout << "THE VECTOR" << std::endl;
		for (int i = 0; i < size; ++i)
		{
			std::cout << a[i] << " ";
		}
		std::cout << "" << std::endl;
	}
	void erase(Mat* M) {
		Line* tail, * trash;
		for (int i = 0; i < M->m; i++) {
			tail = M->lines[i];
			while (tail != nullptr) {
				trash = tail;
				tail = tail->next;
				delete trash;
			}
		}
		delete[] M->lines;
		delete M;
	}
}
