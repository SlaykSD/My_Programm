#pragma once
namespace OOP1 {
//������ ��������� ������������� ����������� �������
	int M, N;//���������� ��������, �������
	struct Line{ //������� �������� ������������� �������
		int i, j;
	}
	struct Vector {
		int number_line;//����� ������
		int sum_line;//����� ��-�� ������
	}
	//������ ����� �������� ��������
	template <class T>
	int getNum(T& a)
	{
		std::cin >> a;
		if (!std::cin.good())
			return -1;
		return 1;
	}
	inline int isgreater(T a, T b)
	{
		return a > b;
	}
	inline int isless(T a, T b)
	{
		return a < b;
	}
	Line* input(int&);
	void output(const char* msg, int m, Line a[]);
	Line* cleaning(Line *& a, int m);
	double average(Line a[])

}