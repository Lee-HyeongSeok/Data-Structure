/*
주어진 N개의 key, data쌍을 Hash table에 입력, Q 개의 key를 입력받아 key에 해당하는
data를 각 줄에 출력

(1 <= N, Q <= 4096)
key : 최대 64개의 문자열
data : 최대 128개의 문자열 
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <memory.h>

#define MAX_KEY 64
#define MAX_DATA 128
#define MAX_TABLE 4096

typedef struct {
	char key[MAX_KEY + 1];
	char data[MAX_DATA + 1];
}Hash;

Hash tb[MAX_TABLE];

unsigned long hash(const char *str) {
	unsigned long hash = 5381;
	int c;

	// 문자열의 각 문자를 c 변수에 대입
	while (c = *str++) {
		// 해시 함수
		// Left Shift 5번 + hash값 + 문자를 MAX_TABLE로 나눈 나머지
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}
	return hash % MAX_TABLE; // 위에서 계산된 결과를 다시 MAX_TABLE로 나눈 나머지를 반환 
}

int find(const char *key, char *data) {
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;

	while (tb[h].key[0] != 0 && cnt--) {
		if (strcmp(tb[h].key, key) == 0) { // 찾고자 하는 키와 tb배열의 키가 일치할 때
			strcpy(data, tb[h].data);
			return 1;
		}
		h = (h + 1) % MAX_TABLE;
	}
	return 0;
}

int add(const char *key, char *data) {
	unsigned long h = hash(key);

	while (tb[h].key[0] != 0) {
		if (strcmp(tb[h].key, key) == 0) { // 이미 같은 키 값이 존재할 때
			return 0; // 종료
		}
		h = (h + 1) % MAX_TABLE; // hash값 + 1을 MAX_TABLE로 나눈 나머지를 저장
	}
	strcpy(tb[h].key, key); // 해당 h를 인덱스로 사용
	strcpy(tb[h].data, data);
	return 1;
}
int main(int argc, char *argv[]) {
	int T, N, Q; // 테스트 케이스, 키 개수, 데이터 쌍
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; test_case++) {
		memset(tb, 0, sizeof(tb));
		scanf("%d", &N);
		char k[MAX_KEY + 1];
		char d[MAX_DATA + 1];

		for (int i = 0; i < N; i++) {
			scanf("%s %s\n", &k, &d);
			add(k, d);
		}
		printf("%d\n", test_case);

		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			char k[MAX_KEY + 1];
			char d[MAX_DATA + 1];

			scanf("%s\n", &k);

			if (find(k, d)) {
				printf("%s\n", d);
			}
			else {
				printf("not find\n");
			}
		}
	}
	return 0;
}