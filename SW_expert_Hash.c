/*
�־��� N���� key, data���� Hash table�� �Է�, Q ���� key�� �Է¹޾� key�� �ش��ϴ�
data�� �� �ٿ� ���

(1 <= N, Q <= 4096)
key : �ִ� 64���� ���ڿ�
data : �ִ� 128���� ���ڿ� 
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

	// ���ڿ��� �� ���ڸ� c ������ ����
	while (c = *str++) {
		// �ؽ� �Լ�
		// Left Shift 5�� + hash�� + ���ڸ� MAX_TABLE�� ���� ������
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}
	return hash % MAX_TABLE; // ������ ���� ����� �ٽ� MAX_TABLE�� ���� �������� ��ȯ 
}

int find(const char *key, char *data) {
	unsigned long h = hash(key);
	int cnt = MAX_TABLE;

	while (tb[h].key[0] != 0 && cnt--) {
		if (strcmp(tb[h].key, key) == 0) { // ã���� �ϴ� Ű�� tb�迭�� Ű�� ��ġ�� ��
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
		if (strcmp(tb[h].key, key) == 0) { // �̹� ���� Ű ���� ������ ��
			return 0; // ����
		}
		h = (h + 1) % MAX_TABLE; // hash�� + 1�� MAX_TABLE�� ���� �������� ����
	}
	strcpy(tb[h].key, key); // �ش� h�� �ε����� ���
	strcpy(tb[h].data, data);
	return 1;
}
int main(int argc, char *argv[]) {
	int T, N, Q; // �׽�Ʈ ���̽�, Ű ����, ������ ��
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