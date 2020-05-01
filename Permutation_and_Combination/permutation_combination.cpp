#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_STRING_LEN 10

//int stackTop = 0;
//char combinationStack[MAX_STRING_LEN];

template <class T>
void ChangeSize(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0)
		throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

template <class T>
class Stack {
private :
	T *stack;
	int top;
	int capacity;
public : 
	Stack(int stackCapacity = MAX_STRING_LEN)
		: capacity(stackCapacity) {
		if (capacity < 1)
			throw "Stack capacity must be > 0";
		stack = new T[capacity];
		top = -1;
	}
	bool isEmpty() const {
		return top == -1;
	}
	void push(const T& item) {
		if (top == capacity - 1) {
			ChangeSize(stack, capacity, 2 * capacity);
			capacity *= 2;
		}
		stack[++top] = item;
	}
	void pop() {
		if (isEmpty())
			throw "Stack is empty. Cannot delete";
		stack[top--].~T();
	}
	// 스택의 모든 요소 출력
	void print() {
		for (int i = 0; i <= top; i++)
			cout << stack[i] << ' ';
		cout << endl;
	}
	~Stack() {
		delete[] stack;
	}
	
};

Stack<char> st; // 전역변수 선언


void swap(char *a, char *b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// 문자열, 0, 배열할 문자 개수
void Permutation(char *str, int l, int r) {
	if (l == r) {
		cout << "출력 : " << str << endl;
	}
	else {
		for (int i = l; i <= r; i++) {
			swap((str + l), (str + i));
			Permutation(str, l + 1, r);
			swap((str + l), (str + i));
		}
	}
}

/*
void push(char ch) {
	
	combinationStack[stackTop++] = ch;
	combinationStack[stackTop] = '\0';
	
}

void pop() {
	combinationStack[--stackTop] = '\0';
}
*/

// n개의 문자열 중 k개를 취하는 것
// *str은 문자열
// length는 n개의 문자열, k는 그 문자열 중 몇개를 뽑느냐
// offset은 0부터 시작
// 역순 x
void Combination(const char *str, int length, int offset, int k) {
	if (k == 0) {
		st.print();
		//cout << combinationStack << endl;
		return;
	}
	for (int i = offset; i <= length - k; ++i) {
		st.push(str[i]);
		Combination(str, length, i + 1, k - 1);
		st.pop();
	}
}

int main() {
	int N, K, T; // T는 테스트 케이스
	char str[MAX_STRING_LEN];
	cin >> T;

	for (int test = 1; test <= T; test++) {
		cin >> str >> N >> K;

		// 문자열의 끝을 의미하는 NULL을 표시해준 것이다.
		str[N] = 0; // 입력한 문자열 중에 n개를 선택하는 것
		cout << "#" << test << endl;

		Permutation(str, 0, N - 1);
		Combination(str, N, 0, K);
	}
	return 0;
}
