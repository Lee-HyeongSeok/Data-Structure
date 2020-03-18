#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

#define MAX 2

template <typename T>
class StackType {
private :
	T *value;
	int size;
	int top;
public : 
	StackType() {
		size = MAX;
		value = new T[size];
		top = -1;
	}
	~StackType() {
		delete[] value;
	}
	bool isFull() {
		if (top + 1 == size) {
			return true;
		}
		else {
			return false;
		}
	}
	bool empty() {
		if (top < 0) {
			return true;
		}
		else {
			return false;
		}
	}
	T top() {
		if (!empty()) {
			return value[top];
		}
		else {
			return NULL;
		}
	}
	void push(T val) {
		if (!isFull()) {
			value[++top] = value;
		}
		else {
			cout << "stack overflow !" << endl;
		}
	}
	void pop() {
		if (!empty()) {
			top--;
		}
		else {
			cout << "stack is empty" << endl;
		}
	}
};
template <typename T>
void dump(const char *desc, T t) {
	cout.width(12);
	cout << left << desc << " => ";
	copy(t.begin(), t.end(), ostream_iterator<typename T::value_type>(cout, " "));
	cout << endl;
}
template <typename T>
ostream& operator<<(ostream &out, StackType<T> &st) {
	T *tmp = st.value;
	out << "=============" << endl;
	for (const auto& ref : tmp) {
		cout << *ref << endl;
	}
	out << "=============" << endl;
	return out;	//°´Ã¼ ¹ÝÈ¯
}
int main() {
	StackType<int> st;
	cout << "stack push " << endl;
	st.push(1);
	st.push(3);
	st.push(5);

	cout << st << endl;
}