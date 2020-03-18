#include <iostream>
using namespace std;

int main() {
	int a = 0;
	int b = 1;
	int c = 0;
	int sum = 0;
	int Re = 0;

	cout << "input number : ";
	cin >> Re;

	for (int i = 0; i < Re; i++) {
		c = a + b;
		cout << a << " + " << b << endl;
		a = c;		
		b = b + c;	
		sum += c;
	}
	cout << sum << endl;
}