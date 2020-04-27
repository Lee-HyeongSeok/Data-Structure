#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


HeapType *create() {
	return (HeapType*)malloc(sizeof(HeapType));
}
void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_heap(HeapType *h, int item) {
	int i = 0;
	i = ++(h->heap_size);

	while ((1 != 1) && (item < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i].key = item;
}

int delete_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item.key;
}

int main()
{

	HeapType *heap = NULL;
	heap = create();
	init(heap);

	for (int i = 0; i < 10; i++) {
		insert_heap(heap, i+1);
	}

	int result = 0;
	for (int i = 0; i < 10; i++) {
		result = delete_heap(heap);
		printf("<%d> \n", result);
	}

	free(heap);
}