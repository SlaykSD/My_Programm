
#include <iostream>
#include "Prog1.h"
namespace Prog1 {
	// ??????? ?????
	Line* input(int& rm)
	{
		const char* pr = ""; // ??????? ????????? ?? ??????
		Line* lines = nullptr; // ???????????? ?????? ????? ???????
		int m; // ?????????? ????? ???????
		// ??????? ?????? ?????????? ?????
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter number of lines: --> ";
			pr = "You are wrong; repeat please!";
			if (getNum(m) < 0) // ?????????? ?????? ????? ??? ????? ?????
				return nullptr;
		} while (m < 1);
		// ???????? ?????? ??? ?????? ???????? - ????? ???????
		try {
			lines = new Line[m];
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return nullptr;
		}
		for (int i = 0; i < m; i++) {
			// ?????? ??? ?????? ?????? ??????? ?????? ?????????? ????????
			pr = "";
			do {
				std::cout << pr << std::endl;
				std::cout << "Enter number of items in line #" << (i + 1) << " --> ";
				pr = "You are wrong; repeat please!";
				if (getNum(lines[i].n) < 0) { // ?????????? ?????? ????? ??? ????? ?????
					erase(lines, i); // ???????????? ??????, ??????? ????? ?????????? ????????
					return nullptr;
				}
			} while (lines[i].n < 1);
			// ? ???????? ??????????? ?????? ??? ???????? ??????
			try {
				lines[i].a = new double[lines[i].n];
			}
			catch (std::bad_alloc & ba)
			{
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}
			// ?????? ????? ??????? ???? ???????? ?????? ?????? ???????
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < lines[i].n; j++) {
				if (getNum(lines[i].a[j]) < 0) { // ?????????? ?????? ????? ??? ????? ?????
					erase(lines, i + 1); // ???????????? ??????, ??????? ????? ?????????? ????????
					return nullptr;
				}
			}
		}
		// ????????? ????????? - ?????????? ????? ? ???????
		rm = m;
		return lines;
	}
	// ??????? ??????
	void output(const char* msg, Line* a, int m)
	{
		int i, j;
		std::cout << msg << ":\n";
		for (i = 0; i < m; ++i) {
			for (j = 0; j < a[i].n; ++j)
				std::cout << a[i].a[j] << " ";
			std::cout << std::endl;
		}
	}
	// ??????? ???????????? ??????? ??????
	Line* erase(Line*& lines, int m)
	{
		int i;
		for (i = 0; i < m; i++)
			delete[] lines[i].a;
		delete[] lines;
		return nullptr;
	}
	// ??????? ?????????? ???????? ??????????
	int minmax(struct Line lines[], int m, double& res)
	{
		double* s = nullptr;
		try {
			s = new double[m]; // ?????? ??? ????????? max ????????? ? ?????? - ?? ???????
		}
		catch (std::bad_alloc & ba)
		{
			std::cout << ba.what() << std::endl;
			return 1;
		}
		int i;
		for (i = 0; i < m; i++)
			s[i] = minmax(lines[i].a, lines[i].n, isgreater);
		res = minmax(s, m, isless);
		delete[] s;
		return 0;
	}

	// ??????? ?????????? min/max ???????? ???????
	double minmax(double a[], int m, int(*f)(double, double))
	{
		double res = a[0];
		int i;
		for (i = 0; i < m; ++i)
			if (f(a[i], res) > 0)
				res = a[i];
		return res;
	}
}
��?? Prog1main.cpp
� ???????? ?????????? ??????? main()
#include <iostream>
#include "Prog1.h"
using namespace Prog1;
// ???????? ???????
int main()
{
	Line* arr = nullptr; // ???????? ??????
	int m; // ?????????? ????? ? ???????
	double res; // ?????????? ?????????
	arr = input(m); // ???? ???????
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	if (minmax(arr, m, res)) { // ?????????? ?????????? ??????????
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}
	output("Sourced matrix", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); // ???????????? ??????
	return 0;
}