#include <iostream>
#include"lab.h"
using namespace matrix;


void main() {
	Mat* M = Mgen();
	MInput(M);
	double* vector = analysis(M);
	Print(M);
	Print(vector);
	erase(M);
	erase(vector);
}
