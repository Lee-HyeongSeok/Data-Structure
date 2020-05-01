## * S/W expert 순열 조합(Permutation & Combination)   

#### * 순열 : 순서가 부여된 임의의 집합을 다른 순서로 뒤섞는 연산
#### * 조합 : 집합에서 일부 원소를 취해 부분 집합을 만드는 방법



#### * 문제 : 주어진 문자열에 대해 조건에 만족하도록 출력   
			조건 1. 문자열의 n개 문자를 일렬로 배열하는 모든 경로 출력   
			조건 2. 문자열의 n개 문자 중 k개를 취하는 모든 경우를 출력   
			제한사항 : 문자열이 동일한 알파벳이 중복으로 포함되지 않는다.   

#### * 입력   
```c
1	// test case
ABCD
3	// 3개의 문자를 일렬로 배열한다는 입력
2	// n개의 문자중 2개를 취하는 모든 경우를 출력
```   
#### * 출력   
```c
#1
ABC
ACB
BAC
BCA
CBA
CAB
AB
AC
BC
```   

#### * Permutation Code   

```c
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
```   

#### * Combination Code   

```c
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
```   

#### * Stack class를 이용한 구현   
```c
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

```   

#### * 기존의 reference code   
```c
#include <iostream>

using namespace std;

#define MAX_STRING_SIZE 10

int stackTop = 0;
char combinationStack[MAX_STRING_SIZE];
void swap(char *a, char *b) {
	char temp = *a;
	*a = *b;
	*b = temp;
}

void Permutation(char *str, int l, int r) {
	if (l == r)
		cout << str << endl;
	else {
		for (int i = l; i <= r; i++) {
			swap((str + l), (str + i));
			Permutation(str, l + 1, r);
			swap((str + l), (str + i));
		}
	}
}

void Push(char ch) {
	combinationStack[stackTop++] = ch;
	combinationStack[stackTop] = '\0';
}

void Pop() {
	combinationStack[--stackTop] = '\0';
}
void Combination(char *str, int length, int offset, int k) {
	if (k == 0) {
		cout << combinationStack << endl;
		return;
	}
	for (int i = offset; i <= length - k; i++) {
		Push(str[i]);
		Combination(str, length, i + 1, k - 1);
		Pop();
	}
}
```