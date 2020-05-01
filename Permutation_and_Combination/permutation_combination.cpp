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
	// ������ ��� ��� ���
	void print() {
		for (int i = 0; i <= top; i++)
			cout << stack[i] << ' ';
		cout << endl;
	}
	~Stack() {
		delete[] stack;
	}
	
};

Stack<char> st; // �������� ����


void swap(char *a, char *b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// ���ڿ�, 0, �迭�� ���� ����
void Permutation(char *str, int l, int r) {
	if (l == r) {
		cout << "��� : " << str << endl;
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

// n���� ���ڿ� �� k���� ���ϴ� ��
// *str�� ���ڿ�
// length�� n���� ���ڿ�, k�� �� ���ڿ� �� ��� �̴���
// offset�� 0���� ����
// ���� x
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
	int N, K, T; // T�� �׽�Ʈ ���̽�
	char str[MAX_STRING_LEN];
	cin >> T;

	for (int test = 1; test <= T; test++) {
		cin >> str >> N >> K;

		// ���ڿ��� ���� �ǹ��ϴ� NULL�� ǥ������ ���̴�.
		str[N] = 0; // �Է��� ���ڿ� �߿� n���� �����ϴ� ��
		cout << "#" << test << endl;

		Permutation(str, 0, N - 1);
		Combination(str, N, 0, K);
	}
	return 0;
}
