#include <iostream>
#include "Chain_Line.h"

const char* msgs[] = {	"0. EXIT",
						"1.Get an information about catenary ",
						"2.Get F(X) relative to the variable {X}",
						"3.Get the catenary length",
						"4.Get radius curvature",
						"5.Get (x,y) - coordinates of center curvature "
						"6.Get INTEGRAL your catenary" };

const int Nmsg = sizeof(msgs) / sizeof(msgs[0]);
//Создадим массив функий
int (*Operation[])(Chain_Line::CH_Line&) {}
	
int main(){

}
