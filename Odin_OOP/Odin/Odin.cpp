#include <iostream>
#include "Header.h"
using namespace Prog1;
int main()
{
	Mat* arr = nullptr; 
	double res; 
	arr = get_Mat();
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	if (!Input(arr))
	{
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	int* a;
	if (!(a = Task(arr)))
	{
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	output(arr, a);
	erase(arr);

	return 0;
}
