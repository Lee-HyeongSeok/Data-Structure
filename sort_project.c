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
//��������
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++)
			/* �յ��� ���ڵ带 ���� �� ��ü */
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
// ��������
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; /* ���ڵ��� ������ �̵� */
		list[j + 1] = key;
	}
}
//��������
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) 	// �ּҰ� Ž��
			if (list[j] < list[least]) least = j;
		//if(i!=least)
		SWAP(list[i], list[least], temp);
	}
}
//
//������
inc_insertion_sort(int list[], int first, int last, int gap)
{
	// gap ��ŭ ������ ��ҵ��� ���� ����
	// ������ ������ first���� last
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
		for (i = 0; i < gap; i++)		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}
//�պ�����
void merge(int list[], int left, int mid, int right, int sorted[])
{

	/* i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
	j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
	k�� ���ĵ� ����Ʈ�� ���� �ε��� */
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {

		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
		}
		else
		{
			sorted[k++] = list[j++];
		}
	}

	if (i > mid)	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
		}
	else	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
		}
	/* �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� */
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
}
void merge_sort(int list[], int left, int right, int sorted[])
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;     /* ����Ʈ�� �յ� ���� */
		merge_sort(list, left, mid, sorted);    /* �κ� ����Ʈ ���� */
		merge_sort(list, mid + 1, right, sorted); /* �κ� ����Ʈ ���� */
		merge(list, left, mid, right, sorted);    /* �պ� */
												  //	printf("���� �� ���\n");
												  //	print_list(list, right);
												  //	printf("���� �� ���\n");
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
//�� ����
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

		if (r - l + 1 > 1) {  // �������� :: ���� �ִ� ������ ���� ������ 1�� �̻��� ���
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

			// pivot�� i���� ��ȯ
			t = a[i];
			a[i] = a[r];
			a[r] = t;

			push(r);     // ������ ������ ������ ��
			push(i + 1);  // ������ ������ ���� ��
			push(i - 1);  // ���� ������ ������ ��
			push(l);     // ���� ������ ���� ��

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

// �ʱ�ȭ �Լ�
init(HeapType * h)
{
	h->heap_size = 0;
}
// ���� �Լ�
void insert_max_heap(HeapType * h, int item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
int delete_max_heap(HeapType * h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// �켱 ���� ť�� ������ �̿��� ����
void heap_sort(int list[], int n)
{
	int i;
	HeapType h;
	h.heap = (int*)malloc(sizeof(int) * n);//������
	init(&h);
	for (i = 0; i < n; i++) {
		insert_max_heap(&h, list[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		list[i] = delete_max_heap(&h);
	}
}


typedef int element;	// ����� Ÿ��
typedef struct QueueNode {	// ť�� ����� Ÿ�� 
	element item;
	struct QueueNode* link;
} QueueNode;
typedef struct {		// ť ADT ����
	QueueNode* front, *rear;
} QueueType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init2(QueueType * q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType * q)
{
	return (q->front == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType * q)
{
	return 0;
}
// ���� �Լ�
void enqueue(QueueType * q, element item)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else {
		temp->item = item; 		// ������ ����
		temp->link = NULL; 		// ��ũ �ʵ带 NULL
		if (is_empty(q)) { 		// ť�� �����̸�
			q->front = temp;
			q->rear = temp;
		}
		else { 		// ť�� ������ �ƴϸ�
			q->rear->link = temp;  // ������ �߿�
			q->rear = temp;
		}
	}
}
// ���� �Լ�
element dequeue(QueueType * q)
{
	QueueNode* temp = q->front;
	element item;
	if (is_empty(q))			// �������
		error("ť�� ��� �����ϴ�");
	else {
		item = temp->item; 		// �����͸� ������.
		q->front = q->front->link; // front�� ������带 ����Ű���� �Ѵ�.
		if (q->front == NULL) 	// ���� ����
			q->rear = NULL;
		free(temp); 			// �����޸� ����
		return item; 			// ������ ��ȯ
	}
}
// peek �Լ�
element peek(QueueType * q)
{
	element item;
	if (is_empty(q))
		error("ť�� ��� �����ϴ�");
	else {
		item = q->front->item;	// �����͸� ������.
		return item; 			// ������ ��ȯ
	}
}

void radix_sort(int list[], int n, int digit)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) init2(&queues[b]);  // ť���� �ʱ�ȭ

	for (d = 0; d < digit; d++) {
		for (i = 0; i < n; i++)			// �����͵��� �ڸ����� ���� ť�� ����
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)  // ��Ŷ���� ������ list�� ��ģ��.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// �� ���� �ڸ����� ����.
	}
}

void main()
{
	int i, n, size = 70001, sel_data, digit = 0;
	int sel_result, ins_result, bub_result, shell_result, merge_result, quick_result, heap_result, radix_result;

	int* tmp_list1 = (int*)malloc(sizeof(int) * size);
	int* tmp_list2 = (int*)malloc(sizeof(int) * size);
	int* tmp_list3 = (int*)malloc(sizeof(int) * size);

	int* sel_list = (int*)malloc(sizeof(int) * size);  //��������
	int* ins_list = (int*)malloc(sizeof(int) * size);  //��������
	int* bub_list = (int*)malloc(sizeof(int) * size);  //��������
	int* shell_list = (int*)malloc(sizeof(int) * size);//������
	int* merge_list = (int*)malloc(sizeof(int) * size);//�պ�����
	int* sorted_list = (int*)malloc(sizeof(int) * size);//�պ�����2
	int* quick_list = (int*)malloc(sizeof(int) * size);//������
	int* heap_list = (int*)malloc(sizeof(int) * size);//������
	int* radix_list = (int*)malloc(sizeof(int) * size);//������

	while (1) {

		n = size;

		for (; size > 0; size = size / 10)
		{
			digit++;
		}
		makelist(tmp_list1, tmp_list2, tmp_list3);
		printf("\n[������ ����] \n1.���� \n2.���ĵ� ���� \n3.�������� ���ĵ� ���� \n4.���� \n >> ");
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
			printf("1~4 �� �ٽ� ������ �ּ���.\n");
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
		selection_sort(sel_list, 70001); // �������� ȣ�� 
		finish = clock();
		sel_result = finish - start;

		start = clock();
		insertion_sort(ins_list, 70001); // �������� ȣ�� 
		finish = clock();
		ins_result = finish - start;

		start = clock();
		bubble_sort(bub_list, 70001); // �������� ȣ��/
		finish = clock();
		bub_result = finish - start;

		start = clock();
		shell_sort(shell_list, 70001); // ������ ȣ��/
		finish = clock();
		shell_result = finish - start;

		start = clock();
		merge_sort(merge_list, 0, 70000, sorted_list); // �պ����� ȣ�� 
		finish = clock();
		merge_result = finish - start;

		start = clock();
		//quick_sort(quick_list, 0, n); // ������ ȣ�� 
		qsort_copy((void*)quick_list, (size_t)70001, sizeof(int), compare);
		finish = clock();
		quick_result = finish - start;

		start = clock();
		heap_sort(heap_list, 70001);	//�������� ȣ��
		finish = clock();
		heap_result = finish - start;

		start = clock();
		radix_sort(radix_list, 70001, digit);	//�������� ȣ��
		finish = clock();
		radix_result = finish - start;

		//for (i = 0; i < n; i++) {
		//	printf("%d,	%d,	%d,	%d,	%d,	%d\n", i + 1, shell_list[i], merge_list[i], quick_list[i], heap_list[i], radix_list[i]);
		//}

		printf("�������� : %d\n", ins_result);
		printf("�������� : %d\n", sel_result);
		printf("�������� : %d\n", bub_result);
		printf("������ : %d\n", shell_result);
		printf("�պ����� : %d\n", merge_result);
		printf("������ : %d\n", quick_result);
		printf("�������� : %d\n", heap_result);
		printf("������� : %d\n", radix_result);
	}
}