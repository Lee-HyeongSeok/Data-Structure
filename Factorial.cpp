#include <iostream>

using namespace std;
int res = 1;

void Factorial(int n) {

	if (n <= 1) {
		cout << res << endl;
		return;
	}
	else {
		res = res * n;
		Factorial(n - 1);
	}
}
int main() {
	cout << "input number : ";
	int n = 0;
	cin >> n;
	Factorial(n);
}