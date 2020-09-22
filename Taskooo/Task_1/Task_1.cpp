/*							Задача 1, Вариант 32
Из входного потока вводится сильно разряженная матрица чисел [aij], i=1..m, j=1..n.
Значения m и ni заранее не известны и вводятся из входного потока.
Сформировать вектор {bi}, i=1..m, i-ый элемент которого равен сумме тех элементов
i-ой строки исходной матрицы, у которых сумма цифр, использованных в записи числа,
совпаддает с суммой цифр первого элемента этой же строки исходной матрицы.
Исходную матрицу и полученный вектор вывести в выходной поток с необходимыми комментариями.
*/

#include <iostream>
#include "C:\Users\Григорий\source\repos\Task_1\Source2..h"
using namespace Prog1;

int main(){
	Matrix main = {0, nullptr };
	
	std::cout << "Hello! Put your data down." << std::endl << "If you want to stop adding put 0 in input." << std::endl << "Then the program will count the sum ";
	int rc;
	do {
		rc = getItem(main);
		if (rc == 0) {
			std::cout << "Smth went wrong. Programm will be closed" << std::endl;
			erase(main);
			return 0;
		}
		if (rc == -1)
			std::cout << "The adding has stopped" << std::endl;
	} while (rc == 1);
	show(main);

	SumItem* result=nullptr;
	if (!processing(main, result)) {
		std::cout << "Smth went wrong. Programm will be closed" << std::endl;
		erase(main);
		erase(result);
		return 0;
	}
	show(result, main.line_num);

	erase(main);
	erase(result);
	return 1;
}

/* MADE BY GRIG_KOSILOV IN MEPHI 2019 */