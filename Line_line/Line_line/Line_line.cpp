


#include <iostream>
#include "Catenary.h"

using namespace Chain_Line;
const char* msgs[] = { "0. EXIT",
						"1.Get an information about catenary ",
						"2.Get F(X) relative to the variable {X}",
						"3.Get the catenary length",
						"4.Get radius curvature",
						"5.Get (x,y) - coordinates of center curvature ",
						"6.Get INTEGRAL your catenary",
						"7.Change points your catenary"};

const int Nmsg = sizeof(msgs) / sizeof(msgs[0]);
//Создадим массив функий
int (*Operation[])(CH_Line&) { nullptr, dialog_info, dialog_function, dialog_lenght, dialog_radius, dialog_center, dialog_integral, dialog_set };


int main() {
	CH_Line catenary;
	int rc = 0;
	dialog_set(catenary);
	while (rc = dialog(msgs, Nmsg))
		if (!Operation[rc](catenary))
			break;
	return 0;
}
