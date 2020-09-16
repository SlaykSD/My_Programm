#include <iostream>
#include"lab.h"
namespace matrix {
	Mat* Mgen() {
		using namespace std;
		Mat* M = new Mat;
		cout << "Please, insert heigth of Matrix: ";
		do {
			Gets(M->m);
			if (M->m <= 0)
				std::cout << "!!! Height can't be <1. Please, try again:";
		} while (M->m <= 0);
		cout << endl << "Please, inseart wight of Matrix: ";
		do {
			Gets(M->n);
			if (M->n <= 0)
			std::cout << "!!! Wight can't be <1. Please, try again:";
		} while (M->n <= 0);
		cout << endl;
		try {
			M->lines = new Elem * [M->m];		
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
			erase(M);
			return nullptr;
		}
		for (int i = 0;i < M->m;i++)
			M->lines[i] = nullptr;
		return M;
	}
	void MInput(Mat* M) {
		Elem* tail = nullptr;
		int i = 0, j = 0, el;
		bool frst = true;
		while(std::cout << "Please, insert number of line of inputed element !=0 or -1 to end inserting: ",Gets(i),i!=-1){
			frst = true;
			if ( i<M->m && i>-2 &&( (tail!=nullptr &&i > tail->i)||tail==nullptr))
				tail = nullptr;
			else {
				std::cout << "This line has already inserted or incorrect index try again" << std::endl;
				continue;
			}
			while(std::cout << "Please, insert number  of inputed element!=0 in line or -1 to end inserting line: ",Gets(j),j!=-1) {
				if (!(j<M->n && j>-2 && ((tail != nullptr && j > tail->j) || tail == nullptr))){

					std::cout << "This element has already inserted or incorrect index try again" << std::endl;
					continue;
				}
				std::cout << "Please, insert element a" << i << j << ": ";
				if (frst) {
					try {
						if (M->lines[i] = tail = LineIn(tail), M->lines[i] == nullptr)
							throw - 1;
						frst = false;
					}
					catch (int)
					{
						std::cout << "------ too many items in matrix: " << std::endl;
						erase(M);
						return;
					}
				}
				else{
					try {
						if (tail = LineIn(tail), tail == nullptr)
							throw - 1;
					}
					catch (int)
					{
						std::cout << "------ too many items in matrix: " << std::endl;
						erase(M);
						return ;
					}
				}
					Gets(el);
					if (el != 0) {
						tail->val = el;
						tail->i = i;
						tail->j = j;
					}
					else{
						std::cout << "The element must be !=0, try again " << std::endl;
						continue;
					}
			}
		}
	}
	double* analysis(Mat* M) {
		double cmin=0, cmax=0, c = 0;
		int zeros = -1;
		bool frst;
		double* vector = nullptr;
		Elem* tail = nullptr;
		try {
			vector = new double[(M->m) + 1];
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
			erase(vector);
			erase(M);
			return nullptr;
		}
		vector[0] = M->m;
		vector += 1;
		for (int i = 0;i < M->m;i++) {
			frst = true;
			zeros = -1;
			tail = M->lines[i];
			cmax = cmin = c = 0;
			while (tail != nullptr) {
				if (frst) {
					c=cmax=cmin = tail->val;
					zeros = 0;
					frst = false;
				}
				else {
					calculator(c, cmin, cmax, tail->val);
				}
				zeros++;
				tail = tail->next;
			}
			if (zeros == -1||zeros<M->n)
				calculator(c, cmin, cmax, 0);
			formula(c, cmin, cmax, vector + i);
		}
		return vector;
	}
	inline void formula(double& c, double& cmin, double& cmax, double* el) {
		*el = (c - cmin) / (cmax - cmin);
	}
	inline void  calculator(double& c, double& cmin, double& cmax, const double& el) {
		c += el;
		cmax = el > cmax ? el : cmax;
		cmin = el < cmin ? el : cmin;
	}
	Elem* LineIn(Elem* tail) {
		if (tail == nullptr) {
			try {
				tail = new Elem;
			}
			catch (std::bad_alloc & ba)
			{
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				return nullptr;
			}
			tail->next = nullptr;
			return tail;
		}
		else {
			Elem* nt;
			try {
				nt = new Elem;
			}
			catch (std::bad_alloc & ba)
			{
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				return nullptr;
			}
			tail->next = nt;
			nt->next = nullptr;
			return nt;
		}
	}
	void Print(Mat* M) {
		using namespace std;
		int zeros;
		Elem* tail;
		cout << "***** Matrix *****" << endl;
		for (int i = 0;i < M->m;i++) {
			tail = M->lines[i];
			if (tail == nullptr) {
				for (int i = 0;i < M->n;i++)
					cout << 0<<"   ";
				cout << endl;
				continue;
			}
			int k = 0;			
			while (tail != nullptr) {
				int i;
				for(i =0,k=(tail->j)-k;i<k;i++)
					cout << 0 << "   ";
				cout << tail->val<<"   ";
				k = tail->j+1;
				tail = tail->next;
				
			}
			if (k <= M->n - 1) {
				for (k;k < M->n;k++)
					cout << 0 << "   ";
			}
			cout << endl;
		}
	}
	void Print(double* vector) {
		std::cout << ">>> Vector:" << std::endl;
		for (int i = 0;i < vector[-1];i++)
			std::cout << vector[i]<<"  ";
		std::cout << std::endl;
	}
	void erase(Mat* M) {
		Elem* tail, * trash;
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
	void erase(double* vector) {
		vector--;
		delete[]vector;
	}
}