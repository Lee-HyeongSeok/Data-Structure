#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#include <stdio.h>

int heap[MAX_SIZE];
int heapSize = 0; // heap 크기 

// heap 초기화
void heapInit(void) {
	heapSize = 0;
}

int heapPush(int value) {
	if (heapSize + 1 > MAX_SIZE) {
		printf("Queue is full! \n");
		return 0;
	}

	// 처음 함수 호출 시 heapSize = 0으로 setting
	// 최상위 루트 노드(첫 번째 입력한 값 대기중)
	heap[heapSize] = value; // heap 배열에 값 삽입

	int current = heapSize; // 현재 heapSize를 저장

	
	// loop는 current = 1부터 시작
	// 현재 cur 변수가 0 이상이며, 새로 들어온 값이 부모 노드 값 보다 작으면
	while (current > 0 && heap[current] < heap[(current - 1) / 2]) {
		// 부모 노드와 새로 들어온 노드를 스왑
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;
		current = (current - 1) / 2; // 다음 값이 들어와야 할 인덱스로 바꿔줌
	}
	// heapPush() 함수 호출 때 마다 heapSize 증가 
	heapSize = heapSize + 1;
	return 1;
}

int heapPop(int *value) {
	if (heapSize <= 0) {
		return -1;
	}
	*value = heap[0]; // heap[0] 은 사용 불가능한 방
	heapSize -= 1; // 위에서 최상위 노드를 대입하므로 heapSize를 1감소시킨다.
	heap[0] = heap[heapSize]; 
	
	int child = 0;
	int current = 0;
	while (current * 2 + 1 < heapSize) {

		// 현재 heap 위치 : heapSize로 판별 // 

		if (child * 2 + 2 == heapSize) {
			// 현재 노드 인덱스 ex) 2, 자식노드 인덱스 : 4, 5
			// 자식노드 인덱스 구하는 식: 2 * 2 + 1 = 5
			child = current * 2 + 1; 
		}
		else {
			child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}
		if (heap[current] < heap[child]) {
			break;
		}
		// 자식노드와 삭제한 최상위 노드자리 교체
		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		// 교체 후 다음 작업을 위한 위치로 이동 
		current = child;
	}
	return -1;
}



int main() {
	int test_case = 0; // 테스트 케이스 수
	int val = 0; // 입력 개수만큼 입력받을 변수 
	scanf("%d", &test_case);

	int scale = 0; // 입력 수
	for (int i = 0; i < test_case; i++) {
		scanf("%d", &scale); // 몇개를 입력받을 것인지
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