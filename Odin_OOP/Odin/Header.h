
namespace Prog1 {
	struct Line {
		int i, j;
		int info;
		int numbers;
		struct Line* next;
	};

	struct Mat {
		int m, n;
		Line** lines;
	};


	Mat* get_Mat(void);
	Mat* Input(Mat*);
	void addLine(Mat*, Line*);
	void erase(Mat* M); 
	int getNat(int& a);
	int* Task(Mat*);
	double Average(Line*);
	void output(Mat*, int[]);
	int getint(int& a);
	void output_V(int a[], int);
	int Print_size(Mat* M, Line* Elem);
	int find(Mat*, Line*);
}