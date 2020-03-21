#include <iostream>
#include <algorithm>
#include <iterator>
#include <string.h>
using namespace std;

void Magic(const int n) {
	const int MaxSize = 51;
	int **square = new int*[MaxSize];

	for (int i = 0; i < MaxSize; i++) {
		square[i] = new int[MaxSize];
		memset(square[i], 0, sizeof(int)*MaxSize);
	}
	
	int k=0, l=0;

	// n�� �ùٸ� ������ �˻�
	if ((n < MaxSize) || (n < 1)) {
		throw "Error !... n out of range";
	}
	else if (!(n % 2)) {
		throw "Error! ... n is event";
	}

	// n�� Ȧ��. Coxeter�� ��Ģ�� ��� �����ϴ�.
	// H,Coxeter�� n�� Ȧ���� �� ���� ����� ����� ���� ������ ���� ��Ģ�� �����Ѵ�.
	// 1. n���� ��� n���� ���� ���� 2���� �迭�� ǥ���ȴ�.
	// 2. ��� ���� 1���� n���� ��ȣ�� ���̴� �� ���� 0���� n-1���� ��ȣ�� ���̴� ���� ���ϴ�.
	// 3. ���α׷��� �������� ����� i, Ȥ�� j ���� 0�̳� n-1�� �ǵ��� ����.

	for (int i = 0; i < n; i++) {
		fill(square[i], square[i] + n, 0); // square�� 0���� �ʱ�ȭ, STL �˰���
	}
	square[0][(n - 1) / 2] = 1; // ù ���� �߰�

	int key = 2;
	int i = 0; 
	int j = (n - 1) / 2;

	while (key <= n * n) {
		if (i - 1 < 0) {
			k = n - 1;
		}
		else {
			k = i - 1;
		}

		if (j - 1 < 0) {
			l = n - 1;
		}
		else {
			l = j - 1;
		}

		if (square[k][l])
			i = (i + 1) % n; // sqaure�� ä������. �Ʒ��� �̵�
		else {
			i = k;
			j = l;
		}

		square[i][j] = key;
		key++;
	}// while�� ��

	cout << "magic Square of Size" << n << endl;
	for (i = 0; i < n; i++) {
		copy(square[i], square[i] + n, ostream_iterator<int>(cout, " "));
		cout << endl;
	}

	for (int i = 0; i < MaxSize; i++) {
		delete[] square[i];
	}
	delete[] square;
}

int main() {
	int n = 0;
	cin >> n;

	Magic(n);
}