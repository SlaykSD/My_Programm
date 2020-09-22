namespace Prog1 {
	struct Item {
		int col_pos;
		int value;
		Item *next;
	};
	struct Line {
		int line_pos;
		Line* next;
		Item* head;
	};
	struct Matrix {
		int line_num;
		Line* head;
	};
	struct SumItem {
		int line_pos;
		int line_sum;
	};

	int getItem(Matrix&);
	int processing(Matrix, SumItem*&);
	void show(Matrix);
	void show(SumItem*, int);
	void erase(Matrix&);
	void erase(SumItem*);

	template <class T>
	int getNum(T& a) {
		std::cin >> a;
		if (!std::cin.good())
			return -1;
		return 1;
	}
}