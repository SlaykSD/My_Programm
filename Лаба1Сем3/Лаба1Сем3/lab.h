namespace matrix {

	struct Elem {
		double val;
		int i;
		int j;
		Elem* next;
	};
	struct Mat {
		int m, n;
		Elem** lines;
	};
	template <class storage>
	int Gets(storage& a) {

			std::cin >> a;
			if (!std::cin.good()) {
				std::cout << ">>>>> Incorrect data!";
				exit(-1);
			}
		return 1;
	}
	Mat* Mgen();
	void MInput(Mat*);
	Elem* LineIn(Elem*);
	void erase(Mat*);
	void erase(double*);
	void Print(Mat*);
	void Print(double*);
	double* analysis(Mat*);
	inline void calculator(double&, double&, double&,const double&);
	inline void formula(double&, double&, double&, double*);
}
