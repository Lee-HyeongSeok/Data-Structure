#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode { // ť ��� ����ü
	element data;
	struct QueueNode *link;
}QueueNode;

typedef struct { // ť ����ü
	QueueNode *front, *rear;
}LinkedQueueType;

void init(LinkedQueueType *s) { // ť�� ��, �� �ʱ�ȭ
	s->front = NULL;
	s->rear = NULL;
}
element is_empty(LinkedQueueType *s) { // ť�� ������� Ȯ���ϴ� �Լ�
	return (s->front == NULL);
}
void enqueue(LinkedQueueType *q, element data) { // ť�� �����ϴ� �Լ�
	QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode)); // ���ο� ��� ����
	newNode->data = data; // �� ����� �����Ϳ� ���ڷ� ���޵� ������ ����
	newNode->link = NULL; // ��ũ �ʱ�ȭ

	if (is_empty(q)) { // ����ٸ� �տ� ����
		q->front = newNode; // �հ� �ڿ� �� ��� ����
		q->rear = newNode;
	}
	else { // ��尡 ������ �ڿ��� ����
		q->rear->link = newNode; // ť�� ���ʸ�ũ�� ����� ����� ��ũ�� �� ��� ����, �ڿ��� ���� ����
		q->rear = newNode; // ť�� ���� ��ũ�� �� ��� ����
	}
	
}
element	dequeue(LinkedQueueType *q) { // ť�� �����ϴ� �Լ�
	// ������ ���� �տ��� ���� ����
	QueueNode *removed = q->front; // ������ ���� ��� ����ü �����ͺ��� ����� ���ÿ� ť�� �� ��带 ����
	element data;
	if (is_empty(q)) { // ���������
		fprintf(stderr, "������ ������� \n");
		exit(1);
	}
	else { // ť�� ������� ������
		data = removed->data; // ������ ����� �����͸� ����
		q->front = q->front->link;	// q->front�� ����Ű�� ����� ���� ��带 ����
		if (q->front == NULL)	//�������
			q->rear = NULL; // ť�� ���� ��ũ�� NULL�� �ʱ�ȭ
		free(removed); // ������ ���� ������ ����ü ������ ���� �޸� ����
		return data; // ������ ������ ��ȯ
	}
}
void print_queue(LinkedQueueType *q) {
	for (QueueNode *Qn = q->front; Qn != NULL; Qn = Qn->link)
		printf("%d -> ", Qn->data);
	printf("NULL \n");
}
int main() {
	LinkedQueueType q;
	init(&q);
	for (int i = 0; i < 5; i++) {
		enqueue(&q, i + 1);
		print_queue(&q);
	}
	for (int i = 0; i < 5; i++) {
		dequeue(&q);
		print_queue(&q);
	}
	return 0;
}
