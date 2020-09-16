
#include <iostream>
#include "Header.h"
namespace Prog1 {
	int getint(int& a)
	{
		std::cin >> a;
		if (!std::cin.good())
		return -1;
		return 1;
	}
	int getNat(int& a)
	{
		const char* msg = "";
		do
		{
			std::cout << msg;
			std::cin >> a;
			if (!std::cin.good())
				return -1;
			std::cout << "" << std::endl;
			msg = "Incorrect input, try again(Natural):  ";
		} while (a<0);
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
			std::cout << "a[i,j]: i = ";
			//пофиксить
			do {
				if (getNat(Elem->i) < 0)
					return nullptr;
				if (Elem->i >= M->m)
					std::cout << "Incorrect unput,repet please: " << std::endl;
				std::cin.sync();
			} while (Elem->i >= M->m);
			do {
				std::cout << "a[i,j]: j = ";
				if (getNat(Elem->j) < 0)
					return nullptr;
				if (Elem->i >= M->m)
					std::cout << "Incorrect unput,repet please: " << std::endl;
				std::cin.sync();
			} while (Elem->j >= M->n);
			msg = "Next information";
			addLine(M, Elem);
			k++;
		} while (k < count);
	}
	
	void addLine(Mat* M, Line* L)
	{
		if (M->lines[L->i] == nullptr)
			M->lines[L->i] = L;
		else
		{ 
			Line* ptr = M->lines[L->i];
			if ((ptr->next == nullptr) && (ptr->j < L->j))
			{
				ptr->next = L;
				return;
			}
			else
			{
				if (ptr->next == nullptr)
				{
					L->next = ptr;
					M->lines[L->i] = L;
					return;
				}
			}
			while ((ptr->next != nullptr) && (L->j > ptr->j))
			{
				ptr = ptr->next;
			} 
			if ((ptr->j > L->j))
			{
				L->next = ptr->next;
				ptr->next = L;
			}
			else
			{
				ptr->next = L;
			}

		}
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
			a[i] = 0;
			double ar_mean;
			Line* ptr = M->lines[i];
			ar_mean = Average(M->lines[i]);
			while (ptr != nullptr)
			{
				if (ptr->info > ar_mean)
					a[i] += ptr->info;
				ptr = ptr->next;
			}
		}
		return a;
	}
	double Average(Line* L)
	{
		double sum=0;
		int N=0;
		Line* ptr = L;
		while (ptr != nullptr)
		{
			sum += ptr->info;
			N += 1;
			ptr = ptr->next;
		}
		return sum / N;
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
