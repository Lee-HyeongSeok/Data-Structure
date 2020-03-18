#include <iostream>
using namespace std;

void hanoi(int n, int from, int to) {
	if (n <= 0) return;
	hanoi(n - 1, from, 6 - from - to);
	cout << from << " ���� " << n << "����" << to << "�� �̵�" << endl;
	hanoi(n - 1, 6 - from - to, to);

}
int main() {
	int N;
	cout << "input top value : ";
	cin >> N;
	hanoi(N, 1, 3);

	return 0; 
}
