#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode { // 큐 노드 구조체
	element data;
	struct QueueNode *link;
}QueueNode;

typedef struct { // 큐 구조체
	QueueNode *front, *rear;
}LinkedQueueType;

void init(LinkedQueueType *s) { // 큐의 앞, 뒤 초기화
	s->front = NULL;
	s->rear = NULL;
}
element is_empty(LinkedQueueType *s) { // 큐가 비었는지 확인하는 함수
	return (s->front == NULL);
}
void enqueue(LinkedQueueType *q, element data) { // 큐에 삽입하는 함수
	QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode)); // 새로운 노드 생성
	newNode->data = data; // 새 노드의 데이터에 인자로 전달된 데이터 저장
	newNode->link = NULL; // 링크 초기화

	if (is_empty(q)) { // 비었다면 앞에 삽입
		q->front = newNode; // 앞과 뒤에 새 노드 저장
		q->rear = newNode;
	}
	else { // 노드가 있으면 뒤에서 삽입
		q->rear->link = newNode; // 큐의 뒤쪽링크에 저장된 노드의 링크에 새 노드 저장, 뒤에서 부터 삽입
		q->rear = newNode; // 큐의 뒤쪽 링크에 새 노드 저장
	}
	
}
element	dequeue(LinkedQueueType *q) { // 큐를 삭제하는 함수
	// 삭제할 때는 앞에서 부터 삭제
	QueueNode *removed = q->front; // 삭제를 위해 노드 구조체 포인터변수 선언과 동시에 큐의 앞 노드를 저장
	element data;
	if (is_empty(q)) { // 비어있으면
		fprintf(stderr, "스택이 비어있음 \n");
		exit(1);
	}
	else { // 큐가 비어있지 않으면
		data = removed->data; // 삭제할 노드의 데이터를 저장
		q->front = q->front->link;	// q->front가 가리키는 노드의 다음 노드를 저장
		if (q->front == NULL)	//공백상태
			q->rear = NULL; // 큐의 뒤쪽 링크를 NULL로 초기화
		free(removed); // 삭제를 위해 선언한 구조체 포인터 변수 메모리 해제
		return data; // 삭제한 데이터 반환
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
