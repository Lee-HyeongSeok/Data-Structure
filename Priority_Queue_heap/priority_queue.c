#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#include <stdio.h>

int heap[MAX_SIZE];
int heapSize = 0; // heap ũ�� 

// heap �ʱ�ȭ
void heapInit(void) {
	heapSize = 0;
}

int heapPush(int value) {
	if (heapSize + 1 > MAX_SIZE) {
		printf("Queue is full! \n");
		return 0;
	}

	// ó�� �Լ� ȣ�� �� heapSize = 0���� setting
	// �ֻ��� ��Ʈ ���(ù ��° �Է��� �� �����)
	heap[heapSize] = value; // heap �迭�� �� ����

	int current = heapSize; // ���� heapSize�� ����

	
	// loop�� current = 1���� ����
	// ���� cur ������ 0 �̻��̸�, ���� ���� ���� �θ� ��� �� ���� ������
	while (current > 0 && heap[current] < heap[(current - 1) / 2]) {
		// �θ� ���� ���� ���� ��带 ����
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2; // ���� ���� ���;� �� �ε����� �ٲ���
	}
	// heapPush() �Լ� ȣ�� �� ���� heapSize ���� 
	heapSize = heapSize + 1;
	return 1;
}

int heapPop(int *value) {
	if (heapSize <= 0) {
		return -1;
	}
	*value = heap[0]; // heap[0] �� ��� �Ұ����� ��
	heapSize -= 1; // ������ �ֻ��� ��带 �����ϹǷ� heapSize�� 1���ҽ�Ų��.
	heap[0] = heap[heapSize]; 
	
	int child = 0;
	int current = 0;
	while (current * 2 + 1 < heapSize) {

		// ���� heap ��ġ : heapSize�� �Ǻ� // 

		if (child * 2 + 2 == heapSize) {
			// ���� ��� �ε��� ex) 2, �ڽĳ�� �ε��� : 4, 5
			// �ڽĳ�� �ε��� ���ϴ� ��: 2 * 2 + 1 = 5
			child = current * 2 + 1; 
		}
		else {
			child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}
		if (heap[current] < heap[child]) {
			break;
		}
		// �ڽĳ��� ������ �ֻ��� ����ڸ� ��ü
		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		// ��ü �� ���� �۾��� ���� ��ġ�� �̵� 
		current = child;
	}
	return -1;
}



int main() {
	int test_case = 0; // �׽�Ʈ ���̽� ��
	int val = 0; // �Է� ������ŭ �Է¹��� ���� 
	scanf("%d", &test_case);

	int scale = 0; // �Է� ��
	for (int i = 0; i < test_case; i++) {
		scanf("%d", &scale); // ��� �Է¹��� ������
		heapInit();

		for (int i = 0; i < scale; i++) {
			scanf("%d", &val);
			heapPush(val);
		}
		printf("\n Test_Case%d :   ", test_case);
		for (int i = 0; i < scale; i++) {
			heapPop(&val);
			printf("%d  ", val);
		}
		printf("\n");
	}
	return 0;
}