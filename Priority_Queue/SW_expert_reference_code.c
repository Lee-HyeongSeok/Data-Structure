#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Priority Queue : ���� �켱������ ���� ���Ҵ� ���� �켱������ ���� ���Һ��� ���� ó���Ǵ� �ڷᱸ��

�־��� N(2 <= N <= 100)���� ���� ���� ���ڰ� ���� �켱���� Priority Queue�� �����ϰ�, 
�켱 ������ ���� ���ں��� ���ʴ�� ���

[�Է�]

2 // �׽�Ʈ ���̽� ��
10 // �Է� ���� 
10 49 38 17 56 92 8 1 13 55 // �Է� ������
13 // �Է� ����
4 22 50 13 5 1 22 35 21 7 99 100 14 // �Է� ������ 

[���]
1 8 10 13 17 38 49 55 56 92 (1)
1 4 5 7 13 14 21 22 22 35 50 99 100(2)
*/

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void) {
	heapSize = 0;
}

int heapPush(int value) {
	// �迭�� ��ȭ������ ��
	if (heapSize + 1 > MAX_SIZE) {
		printf("Queue is full!");
		return 0;
	}

	// �迭�� ����ȭ ������ ��
	heap[heapSize] = value; // �迭�� �� ����

	int current = heapSize; // ���� �迭 ũ�⸦ ����

	// ���� �迭 ũ�Ⱑ 0���� ũ�� ���� ���� ���� ���� �ε��� ������ ���� ���
	while (current > 0 && heap[current] < heap[(current - 1) / 2]) {

		// ���� ���� ���� ���� �ε����� ���� ��ȯ
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;

		// ��ȯ �� ���� �ε��� ���¸� ��ü�� �ε��� ���·� ����
		current = (current - 1) / 2;
	}

	// ���� �� ������ ���� �ε���+1
	heapSize = heapSize + 1;
	return 1;
}

int heapPop(int *value) {
	// �迭�� �� ������ ���
	if (heapSize <= 0) {
		return -1;
	}

	*value = heap[0]; // �迭�� ù ��° ���� �ּҿ� ����
	heapSize = heapSize - 1; // �迭�� �ִ� ũ�� -1

	// ���� �迭�� �ִ� �ε����� �ش��ϴ� ��Ҹ� �迭�� ù ��° �ε��� ��ҷ� ���
	heap[0] = heap[heapSize]; 
	
	int current = 0;

	// 2�� Ž���� ���� ���� �ε����� ���� �Է��ϴ� �迭�� �ִ� �ε����� ���� �ʵ��� �˻�
	while (current * 2 + 1 < heapSize) {
		int child;

		// �ڽ� ��带 �˻�
		if (current * 2 + 2 == heapSize) {
			child = current * 2 + 1;
		}
		else {
			child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}
		// ���� �ε��� ��Ұ� �ڽ� �ε��� ��Һ��� �۴ٸ� 
		if (heap[current] < heap[child]) {
			break; // ���� Ż��
		}

		// ���� �ε����� ��Һ��� ū �ε����� ��Ұ� ���ڰ� �� �۴ٸ� ��ȯ
		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int T, N; // �׽�Ʈ ���̽�, ���� ����

	scanf("%d", &T); // �׽�Ʈ ���̽� �Է�

	for (int test_case = 1; test_case <= T; test_case++) {
		scanf("%d", &N);

		heapInit(); // �迭 �ʱ�ȭ
		
		for (int i = 0; i < N; i++) { // ���� ������ŭ for��
			int value;
			scanf("%d", &value);
			heapPush(value); // �迭�� �� �Է�
		}
		printf("%d ��� ", test_case);

		for (int i = 0; i < N; i++) {
			int value;
			heapPop(&value); // Pop���� ��Ҹ� ��ȯ�ϴµ�, value�� �ּҿ� ���� �����Ѵ�.
			printf("%d ", value);
		}
		printf("\n");
	}
	return 0;
}
