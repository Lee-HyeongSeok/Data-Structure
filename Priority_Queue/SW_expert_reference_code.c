#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
Priority Queue : 높은 우선순위를 가진 원소는 낮은 우선순위를 가진 원소보다 먼저 처리되는 자료구조

주어진 N(2 <= N <= 100)개의 수를 작은 숫자가 높은 우선순위 Priority Queue에 저장하고, 
우선 순위가 높은 숫자부터 차례대로 출력

[입력]

2 // 테스트 케이스 수
10 // 입력 개수 
10 49 38 17 56 92 8 1 13 55 // 입력 데이터
13 // 입력 개수
4 22 50 13 5 1 22 35 21 7 99 100 14 // 입력 데이터 

[출력]
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
	// 배열이 포화상태일 때
	if (heapSize + 1 > MAX_SIZE) {
		printf("Queue is full!");
		return 0;
	}

	// 배열이 불포화 상태일 때
	heap[heapSize] = value; // 배열에 값 삽입

	int current = heapSize; // 현재 배열 크기를 저장

	// 현재 배열 크기가 0보다 크고 새로 들어온 값이 이전 인덱스 값보다 작은 경우
	while (current > 0 && heap[current] < heap[(current - 1) / 2]) {

		// 새로 들어온 값과 이전 인덱스의 값을 교환
		int temp = heap[(current - 1) / 2];
		heap[(current - 1) / 2] = heap[current];
		heap[current] = temp;

		// 교환 후 현재 인덱스 상태를 교체한 인덱스 상태로 저장
		current = (current - 1) / 2;
	}

	// 다음 값 저장을 위해 인덱스+1
	heapSize = heapSize + 1;
	return 1;
}

int heapPop(int *value) {
	// 배열이 빈 상태인 경우
	if (heapSize <= 0) {
		return -1;
	}

	*value = heap[0]; // 배열의 첫 번째 값을 주소에 저장
	heapSize = heapSize - 1; // 배열의 최대 크기 -1

	// 현재 배열의 최대 인덱스에 해당하는 요소를 배열의 첫 번째 인덱스 요소로 등록
	heap[0] = heap[heapSize]; 
	
	int current = 0;

	// 2진 탐색을 위해 현재 인덱스가 값을 입력하는 배열의 최대 인덱스를 넘지 않도록 검사
	while (current * 2 + 1 < heapSize) {
		int child;

		// 자식 노드를 검사
		if (current * 2 + 2 == heapSize) {
			child = current * 2 + 1;
		}
		else {
			child = heap[current * 2 + 1] < heap[current * 2 + 2] ? current * 2 + 1 : current * 2 + 2;
		}
		// 현재 인덱스 요소가 자식 인덱스 요소보다 작다면 
		if (heap[current] < heap[child]) {
			break; // 루프 탈출
		}

		// 작은 인덱스의 요소보다 큰 인덱스의 요소가 숫자가 더 작다면 교환
		int temp = heap[current];
		heap[current] = heap[child];
		heap[child] = temp;

		current = child;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int T, N; // 테스트 케이스, 숫자 개수

	scanf("%d", &T); // 테스트 케이스 입력

	for (int test_case = 1; test_case <= T; test_case++) {
		scanf("%d", &N);

		heapInit(); // 배열 초기화
		
		for (int i = 0; i < N; i++) { // 숫자 개수만큼 for문
			int value;
			scanf("%d", &value);
			heapPush(value); // 배열에 값 입력
		}
		printf("%d 결과 ", test_case);

		for (int i = 0; i < N; i++) {
			int value;
			heapPop(&value); // Pop에서 요소를 반환하는데, value의 주소에 값을 삽입한다.
			printf("%d ", value);
		}
		printf("\n");
	}
	return 0;
}
