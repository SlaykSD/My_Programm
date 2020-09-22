#include <iostream>
#include "C:\Users\Григорий\source\repos\Task_1\Source2..h"
namespace Prog1 {
	//Переделать на цикл перебором по значениям не больше, а не по всем
	int existence_check(Matrix& main, int u_value, int u_line_pos, int u_col_pos) { 
		int output = 0; // 0 - not exist, 1 - line exist, 2 - item exist
		for (Line* ptr_line = main.head; ptr_line; ptr_line = ptr_line->next)
			if (ptr_line->line_pos == u_line_pos) {
				output = 1;
				for (Item* ptr_item = ptr_line->head; ptr_item; ptr_item = ptr_item->next)
					if (ptr_item->col_pos == u_col_pos) {
						output = 2;
						break;
					}
			}
		return output;
	} 
	Line* find_line(Matrix& main, int u_line_pos) {
		for (Line* ptr_line = main.head; ptr_line; ptr_line = ptr_line->next)
			if (ptr_line->line_pos == u_line_pos)
				return ptr_line;
		return nullptr;
	}

	Item* born_item(int col_pos, int value) {
		Item* ptr;
		try { ptr = new Item; }
		catch (std::bad_alloc) {
			std::cout << "Memory is full";
			return nullptr;
		}
		ptr->col_pos = col_pos;
		ptr->value = value;
		return ptr;
	}
	int make_new(Line* line, int u_col_pos, int value) {
				//Добавление в начало
		if (line->head == nullptr ||
				line->head->col_pos > u_col_pos) {
				Item* buf = line->head;
				line->head = born_item(u_col_pos, value);
				if(!line->head)
					return 0;
				line->head->next = buf;
				return 1;
		}
				//Добавление в середину
		Item* ptr_item = line->head;
		for (ptr_item; ptr_item->next; ptr_item= ptr_item->next)
			if (ptr_item->next->col_pos > u_col_pos) {
				Item* buf = ptr_item->next;
				ptr_item->next = born_item(u_col_pos, value);
				if (!ptr_item)
					return 0;
				ptr_item->next->next = buf;
				return 1;
			}
				//Добавление в конец
				ptr_item->next = born_item(u_col_pos, value);
				if (!ptr_item)
					return 0;
				ptr_item->next->next = nullptr;
				return 1;
	}
	Line* born_line(int line_pos) {
		Line* ptr;
		try { ptr = new Line; }
		catch (std::bad_alloc) {
			std::cout << "Memory is full";
			return nullptr;
		}
		ptr->line_pos = line_pos;
		ptr->head = nullptr;
		return ptr;
	}
	int make_new(Matrix* main, int u_line_pos, int u_col_pos, int value) {
			//Добавление в начало
		if (main->head == nullptr ||
			main->head->line_pos > u_line_pos) {
				Line* buf = main->head;
				main->head = born_line(u_line_pos);
				if (!main->head)
					return 0;
				main->head->next = buf;
				main->line_num++;
				make_new(main->head, u_col_pos, value);
				return 1;
		}
				//Добавление в середину
		Line* ptr_line = main->head;
		for (ptr_line; ptr_line->next; ptr_line = ptr_line->next)
			if (ptr_line->next->line_pos > u_line_pos) {
				Line* buf = ptr_line->next;
				ptr_line->next = born_line(u_line_pos);
				if (!ptr_line->next)
					return 0;
				ptr_line->next->next = buf;
				main->line_num++;
				make_new(ptr_line->next, u_col_pos, value);
				return 1;
			}
				//Добавление в конец
				ptr_line->next = born_line(u_line_pos);
				if (!ptr_line->next)
					return 0;
				ptr_line->next->next = nullptr;
				main->line_num++;
				make_new(ptr_line->next, u_col_pos, value);
				return 1;
	}

	int getItem(Matrix &main) {
		//Диалоговый блок, требующий с пользователя номер строки, столбца и значение
		int value, line_pos, col_pos, rc;
		const char* pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter value " << std::endl;
			pr = "You've put not integer, repeat pls or put 0 to exit";
			rc = getNum(value);
			if (value == 0) //проверка что ввод окончен
				return -1;
		} while (rc != 1);
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter line pos " << std::endl;
			pr = "You've put not integer, repeat pls or put 0 to exit";
			rc = getNum(line_pos);
		} while (rc != 1);
		pr = "";
		do {
			std::cout << pr << std::endl;
			std::cout << "Enter col pos " << std::endl;
			pr = "You've put not integer, repeat pls or put 0 to exit";
			rc = getNum(col_pos);
		} while (rc != 1);
		//Блок проверки занятости и записи
		switch (existence_check(main, value, line_pos, col_pos)) {
			// 0 - not exist, 1 - line exist, 2 - item exist
		case 2: {
			std::cout << "Item with this cords is alreay exist";
			return 1;
			break;
		}
		case 1: {
			//Поиск нужной строки
			Line* needed_line = find_line(main, line_pos);
			if (!needed_line) {
				std::cout << "Smth went wrong";
				return 0;
			}

			if ( make_new(needed_line, col_pos, value) )
				return 1;
			else return 0;
			break;
		}
		case 0: {
			if ( make_new(&main, line_pos, col_pos, value) )
				return 1;
			else return 0;
		}
		}
	}

	int sum_count(int input) {
		int Sum = 0;
		while (input > 0) {
			Sum += input % 10;
			input /= 10;
		}
		return Sum;
	}
	int processing(Matrix main, SumItem*& res) {
		try { res = new SumItem[main.line_num]; }
		catch (std::bad_alloc) {
			std::cout << "Memory is full";
			return 0;
		}
 
		int i = 0;
		for (Line* ptr_line = main.head; ptr_line; ptr_line = ptr_line->next) {
			int Sum = 0;
			int first_sum = sum_count(ptr_line->head->value);

			for (Item* ptr_item = ptr_line->head->next; ptr_item; ptr_item = ptr_item->next)
				if (first_sum == sum_count(ptr_item->value))
					Sum += ptr_item->value;

			res[i].line_pos = ptr_line->line_pos;
			res[i++].line_sum = Sum;
		}
		return 1;
	}

	void show(Matrix main) {
		if (!main.head)
			std::cout << "Matrix is empty" << std::endl;

		for (Line* ptr_line = main.head; ptr_line; ptr_line = ptr_line->next) {
			std::cout << "Line #" << ptr_line->line_pos << ": ";
			if (!ptr_line->head)
				std::cout << "Line is empty" << std::endl;
			else
				for (Item* ptr_item = ptr_line->head; ptr_item; ptr_item = ptr_item->next)
					std::cout << ", (" << ptr_item->col_pos << "|" << ptr_item->value << ")";
			std::cout << "." << std::endl;
		}
	}
	void erase(Matrix& main) {
		Line* ptr_line = main.head;
		while (ptr_line) {
			Item* ptr_item = ptr_line->head;
			while (ptr_item) {
				Item* buf = ptr_item;
				ptr_item = ptr_item->next;
				delete(buf);
			}
			ptr_line = ptr_line->next;
		}
		main.line_num = 0;
		main.head = nullptr;
	}

	void show(SumItem* res, int n) {
		if (!res)
			std::cout << "Result isn't exist" << std::endl;

		std::cout << "These are sums:" << std::endl;
		for (int i = 0; i < n; i++) {
			std::cout << "Line #" << res[i].line_pos << ": "<< res[i].line_sum << std::endl;
		}
	}
	void erase(SumItem* res) {
		delete[] res;
	}
}