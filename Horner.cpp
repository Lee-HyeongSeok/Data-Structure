#include <iostream>
using namespace std;

// 재귀 함수
// horner 법칙 : A(x) = (...(anx0+an-1)x0+...+a1)x0 + a0
// 함수에 들어갈 수, 배열, 배열의 수
int horner(const int& x, const int *a, const int &n) {
	if (n == 1) // n이 1일 때 a[0]을 반환
		return a[0];
	else
		return (horner(x, a, n - 1) * x + a[n - 1]); 
}
int main(void) {
	// A(x) = 1*x^3 + 2*x^2 + 3*x^1 + 4
	int arr[4] = { 1, 2, 3, 4 };

	cout << horner(3, arr, 4) << endl;
}