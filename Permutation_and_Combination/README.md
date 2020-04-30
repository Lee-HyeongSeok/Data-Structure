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
		cout << combinationStack << endl;
		return;
	}
	for (int i = offset; i <= length - k; ++i) {
		push(str[i]);
		Combination(str, length, i + 1, k - 1);
		pop();
	}
}
```