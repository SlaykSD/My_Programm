#include <iostream>
#include "Prog1.h"
using namespace Prog1;
int main()
{
	Line* arr = nullptr; // ȜȥȩȢȘȡȯȝ ȠȔȥȥȜȖ
	int m; // ȞȢȟȜȫșȥȦȖȢ ȥȦȤȢȞ Ȗ ȠȔȦȤȜȪș
	double res; // ȣȢȟȧȫșȡȡȯȝ ȤșțȧȟȰȦȔȦ
	arr = input(m); // ȖȖȢȘ ȠȔȦȤȜȪȯ
	if (!arr) {
		std::cout << "incorrect data" << std::endl;
		return 1;
	}
	if (minmax(arr, m, res)) { // ȖȯȫȜȥȟșȡȜș ȦȤșȕȧșȠȢȗȢ ȤșțȧȟȰȦȔȦȔ
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}
	output("Sourced matrix", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); // ȢȥȖȢȕȢȚȘșȡȜș ȣȔȠȳȦȜ
	return 0;
}
