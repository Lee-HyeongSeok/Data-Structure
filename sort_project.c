#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define BUCKETS 10
#define MAX_NUM 50
int stack[MAX_NUM];
int top = 0;


void makelist(int* randomlist, int* uplist, int* downlist) {

	int tmp_data = 0;
	int length[3] = { 0 };
	FILE* fp[3];

	fp[0] = fopen("Data1.txt", "r");
	fp[1] = fopen("Data2.txt", "r");
	fp[2] = fopen("Data3.txt", "r");

	fscanf(fp[0], "%d", &tmp_data);

	do {
		fscanf(fp[0], "%d", &tmp_data);
		uplist[length[0]++] = tmp_data;
	} while (uplist[length[0] - 1] != uplist[length[0] - 2]);

	fscanf(fp[1], "%d", &tmp_data);
	downlist[length[1]++] = tmp_data;

	do {
		fscanf(fp[1], "%d", &tmp_data);
		downlist[length[1]++] = tmp_data;
	} while (downlist[length[1] - 1] != downlist[length[1] - 2]);

	fscanf(fp[2], "%d", &tmp_data);
	randomlist[length[2]++] = tmp_data;

	do {
		fscanf(fp[2], "%d", &tmp_data);
		randomlist[length[2]++] = tmp_data;
	} while (randomlist[length[2] - 2] != randomlist[length[2] - 1]);

	for (int i = 0; i < 3; i++) {
		length[i] -= 1;
		fclose(fp[i]);
	}

}

void print_list(int list[], int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		if (list[i] < 0) {
			printf("Error");
		}
		printf("%d->", list[i]);
	}
	printf("\n");

}
//버블정렬
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			/* 앞뒤의 레코드를 비교한 후 교체 */
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
// 삽입정렬
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; /* 레코드의 오른쪽 이동 */
		list[j + 1] = key;
	}
}
//선택정렬
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) 	// 최소값 탐색
			if (list[j] < list[least]) least = j;
		//if(i!=least)
		SWAP(list[i], list[least], temp);
	}
}
//
//셸정렬
inc_insertion_sort(int list[], int first, int last, int gap)
{
	// gap 만큼 떨어진 요소들을 삽입 정렬
	// 정렬의 범위는 first에서 last
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
void shell_sort(int list[], int n)   // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}
//합병정렬
void merge(int list[], int left, int mid, int right, int sorted[])
{

	/* i는 정렬된 왼쪽리스트에 대한 인덱스
	j는 정렬된 오른쪽리스트에 대한 인덱스
	k는 정렬될 리스트에 대한 인덱스 */
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;

	/* 분할 정렬된 list의 합병 */
	while (i <= mid && j <= right) {

		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
		}
		else
		{
			sorted[k++] = list[j++];
		}
	}

	if (i > mid)	/* 남아 있는 레코드의 일괄 복사 */
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
		}
	else	/* 남아 있는 레코드의 일괄 복사 */
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
		}
	/* 배열 sorted[]의 리스트를 배열 list[]로 재복사 */
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}
void merge_sort(int list[], int left, int right, int sorted[])
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;     /* 리스트의 균등 분할 */
		merge_sort(list, left, mid, sorted);    /* 부분 리스트 정렬 */
		merge_sort(list, mid + 1, right, sorted); /* 부분 리스트 정렬 */
		merge(list, left, mid, right, sorted);    /* 합병 */
												  //	printf("정렬 전 출력\n");
												  //	print_list(list, right);
												  //	printf("정렬 후 출력\n");
												  //	print_list(sorted, right);
	}
}

void init_stack()
{
	top = 0;
}

void push(int i)
{

	if (top >= MAX_NUM) {
		printf("stack full\n");
		return;
	}
	else
		stack[top++] = i;
}

int pop()
{

	if (top == 0)
		return 0;
	else
		return stack[--top];

}

int is_stack_empty()
{

	if (top == 0)
		return 1;
	else
		return 0;

}
//퀵 정렬
void qsort_copy(int a[], int n)
{
	int p, t;
	int i, j;
	int l, r;

	init_stack();

	l = 0;
	r = n - 1;

	push(r);
	push(l);

	while (!is_stack_empty()) {
		l = pop();
		r = pop();

		if (r - l + 1 > 1) {  // 종료조건 :: 남아 있는 분할의 원소 개수가 1개 이상일 경우
			p = a[r];
			i = l - 1;
			j = r;

			while (1) {
				while (a[++i] < p);
				while (a[--j] > p);

				if (i >= j)
					break;

				t = a[i];
				a[i] = a[j];
				a[j] = t;

			}

			// pivot과 i값을 교환
			t = a[i];
			a[i] = a[r];
			a[r] = t;

			push(r);     // 오른쪽 분할의 오른쪽 끝
			push(i + 1);  // 오른쪽 분할의 왼쪽 끝
			push(i - 1);  // 왼쪽 분할의 오른쪽 끝
			push(l);     // 왼쪽 분할의 왼쪽 끝

		} // if
	} // while
}

int compare(const void* arg1, const void* arg2)
{
	if (*(int*)arg1 > * (int*)arg2) return 1;
	else if (*(int*)arg1 == *(int*)arg2) return 0;
	else return -1;
}

typedef struct {
	int* heap;
	int heap_size;
} HeapType;

// 초기화 함수
init(HeapType * h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_max_heap(HeapType * h, int item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
int delete_max_heap(HeapType * h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 우선 순위 큐인 히프를 이용한 정렬
void heap_sort(int list[], int n)
{
	int i;
	HeapType h;
	h.heap = (int*)malloc(sizeof(int) * n);//힙정렬
	init(&h);
	for (i = 0; i < n; i++) {
		insert_max_heap(&h, list[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		list[i] = delete_max_heap(&h);
	}
}


typedef int element;	// 요소의 타입
typedef struct QueueNode {	// 큐의 노드의 타입 
	element item;
	struct QueueNode* link;
} QueueNode;
typedef struct {		// 큐 ADT 구현
	QueueNode* front, *rear;
} QueueType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화 함수
void init2(QueueType * q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType * q)
{
	return (q->front == NULL);
}
// 포화 상태 검출 함수
int is_full(QueueType * q)
{
	return 0;
}
// 삽입 함수
void enqueue(QueueType * q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다");
	else {
		temp->item = item; 		// 데이터 저장
		temp->link = NULL; 		// 링크 필드를 NULL
		if (is_empty(q)) { 		// 큐가 공백이면
			q->front = temp;
			q->rear = temp;
		}
		else { 		// 큐가 공백이 아니면
			q->rear->link = temp;  // 순서가 중요
			q->rear = temp;
		}
	}
}
// 삭제 함수
element dequeue(QueueType * q)
{
	QueueNode* temp = q->front;
	element item;
	if (is_empty(q))			// 공백상태
		error("큐가 비어 있읍니다");
	else {
		item = temp->item; 		// 데이터를 꺼낸다.
		q->front = q->front->link; // front를 다음노드를 가리키도록 한다.
		if (q->front == NULL) 	// 공백 상태
			q->rear = NULL;
		free(temp); 			// 동적메모리 해제
		return item; 			// 데이터 반환
	}
}
// peek 함수
element peek(QueueType * q)
{
	element item;
	if (is_empty(q))
		error("큐가 비어 있읍니다");
	else {
		item = q->front->item;	// 데이터를 꺼낸다.
		return item; 			// 데이터 반환
	}
}

void radix_sort(int list[], int n, int digit)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init2(&queues[b]);  // 큐들의 초기화

	for (d = 0; d < digit; d++) {
		for (i = 0; i < n; i++)			// 데이터들을 자리수에 따라 큐에 삽입
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)  // 버킷에서 꺼내어 list로 합친다.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// 그 다음 자리수로 간다.
	}
}

void main()
{
	int i, n, size = 70001, sel_data, digit = 0;
	int sel_result, ins_result, bub_result, shell_result, merge_result, quick_result, heap_result, radix_result;

	int* tmp_list1 = (int*)malloc(sizeof(int) * size);
	int* tmp_list2 = (int*)malloc(sizeof(int) * size);
	int* tmp_list3 = (int*)malloc(sizeof(int) * size);

	int* sel_list = (int*)malloc(sizeof(int) * size);  //선택정렬
	int* ins_list = (int*)malloc(sizeof(int) * size);  //삽입정렬
	int* bub_list = (int*)malloc(sizeof(int) * size);  //버블정렬
	int* shell_list = (int*)malloc(sizeof(int) * size);//쉘정렬
	int* merge_list = (int*)malloc(sizeof(int) * size);//합병정렬
	int* sorted_list = (int*)malloc(sizeof(int) * size);//합병정렬2
	int* quick_list = (int*)malloc(sizeof(int) * size);//퀵정렬
	int* heap_list = (int*)malloc(sizeof(int) * size);//힙정렬
	int* radix_list = (int*)malloc(sizeof(int) * size);//힙정렬

	while (1) {

		n = size;

		for (; size > 0; size = size / 10)
		{
			digit++;
		}
		makelist(tmp_list1, tmp_list2, tmp_list3);
		printf("\n[데이터 선택] \n1.랜덤 \n2.정렬된 상태 \n3.역순으로 정렬된 상태 \n4.종료 \n >> ");
		scanf_s("%d", &sel_data);
		switch (sel_data)
		{
		case 1:
			for (i = 0; i < 70001; i++)
			{
				sel_list[i] = tmp_list1[i];
			}
			break;
		case 2:
			for (i = 0; i < 70001; i++)
			{
				sel_list[i] = tmp_list2[i];
			}
			break;
		case 3:
			for (i = 0; i < 70001; i++)
			{
				sel_list[i] = tmp_list3[i];
			}
			break;
		case 4: exit(1);
		default:
			printf("1~4 중 다시 선택해 주세요.\n");
			break;
		}
		for (i = 0; i < 70001; i++)
		{
			ins_list[i] = sel_list[i];
			bub_list[i] = sel_list[i];
			shell_list[i] = sel_list[i];
			merge_list[i] = sel_list[i];
			quick_list[i] = sel_list[i];
			heap_list[i] = sel_list[i];
			radix_list[i] = sel_list[i];
		}
		time_t start, finish;

		start = clock();
		selection_sort(sel_list, 70001); // 선택정렬 호출 
		finish = clock();
		sel_result = finish - start;

		start = clock();
		insertion_sort(ins_list, 70001); // 삽입정렬 호출 
		finish = clock();
		ins_result = finish - start;

		start = clock();
		bubble_sort(bub_list, 70001); // 버블정렬 호출/
		finish = clock();
		bub_result = finish - start;

		start = clock();
		shell_sort(shell_list, 70001); // 쉘정렬 호출/
		finish = clock();
		shell_result = finish - start;

		start = clock();
		merge_sort(merge_list, 0, 70000, sorted_list); // 합병정렬 호출 
		finish = clock();
		merge_result = finish - start;

		start = clock();
		//quick_sort(quick_list, 0, n); // 퀵정렬 호출 
		qsort_copy((void*)quick_list, (size_t)70001, sizeof(int), compare);
		finish = clock();
		quick_result = finish - start;

		start = clock();
		heap_sort(heap_list, 70001);	//히프정렬 호출
		finish = clock();
		heap_result = finish - start;

		start = clock();
		radix_sort(radix_list, 70001, digit);	//히프정렬 호출
		finish = clock();
		radix_result = finish - start;

		//for (i = 0; i < n; i++) {
		//	printf("%d,	%d,	%d,	%d,	%d,	%d\n", i + 1, shell_list[i], merge_list[i], quick_list[i], heap_list[i], radix_list[i]);
		//}

		printf("삽입정렬 : %d\n", ins_result);
		printf("선택정렬 : %d\n", sel_result);
		printf("버블정렬 : %d\n", bub_result);
		printf("쉘정렬 : %d\n", shell_result);
		printf("합병정렬 : %d\n", merge_result);
		printf("퀵정렬 : %d\n", quick_result);
		printf("히프정렬 : %d\n", heap_result);
		printf("기수정렬 : %d\n", radix_result);
	}
}