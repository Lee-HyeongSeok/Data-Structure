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

	// n이 올바른 값인지 검사
	if ((n < MaxSize) || (n < 1)) {
		throw "Error !... n out of range";
	}
	else if (!(n % 2)) {
		throw "Error! ... n is event";
	}

	// n이 홀수. Coxeter의 규칙이 사용 가능하다.
	// H,Coxeter는 n이 홀수일 때 매직 스퀘어를 만들기 위해 다음과 같은 규칙을 제시한다.
	// 1. n개의 행과 n개의 열을 가진 2차원 배열로 표현된다.
	// 2. 행과 열을 1에서 n까지 번호를 붙이는 것 보다 0에서 n-1까지 번호를 붙이는 것이 편하다.
	// 3. 프로그램은 정방형을 벗어나면 i, 혹은 j 값은 0이나 n-1로 되돌아 간다.

	for (int i = 0; i < n; i++) {
		fill(square[i], square[i] + n, 0); // square를 0으로 초기화, STL 알고리즘
	}
	square[0][(n - 1) / 2] = 1; // 첫 행의 중간

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
			i = (i + 1) % n; // sqaure가 채워졌다. 아래로 이동
		else {
			i = k;
			j = l;
		}

		square[i][j] = key;
		key++;
	}// while의 끝

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