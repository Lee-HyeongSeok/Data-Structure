#include <iostream>
using namespace std;

// ��� �Լ�
// horner ��Ģ : A(x) = (...(anx0+an-1)x0+...+a1)x0 + a0
// �Լ��� �� ��, �迭, �迭�� ��
int horner(const int& x, const int *a, const int &n) {
	if (n == 1) // n�� 1�� �� a[0]�� ��ȯ
		return a[0];
	else
		return (horner(x, a, n - 1) * x + a[n - 1]); 
}
int main(void) {
	// A(x) = 1*x^3 + 2*x^2 + 3*x^1 + 4
	int arr[4] = { 1, 2, 3, 4 };

	cout << horner(3, arr, 4) << endl;
}