#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef int element;
typedef struct StackNode { // 노드 구조체
	element data;
	struct StackNode *link;
}StackNode;

typedef struct { // 스택 구조체
	StackNode *top;
}LinkedStackType;

void init(LinkedStackType *s) { // 초기화 함수
	s->top = NULL;
}
int is_empty(LinkedStackType *s) { // 스택이 비었는지 검사
	return (s->top == NULL);
}
int is_full(LinkedStackType *s) {	// full이 존재할 수 없다.
	return 0;
}
void push(LinkedStackType *s, element data) { // 스택에 저장하는 함수
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode)); // 새로운 노드 생성
	temp->data = data; // 새 노드의 데이터에 인자로 전달된 데이터 저장
	temp->link = s->top; // 새 노드의 링크는 스택의 top이 가리키는 노드를 가리킴
	s->top = temp; // 스택의 top은 새 노드를 저장, 새 노드에는 스택의 top 정보가 있음
}
void print_stack(LinkedStackType *s) {
	for (StackNode *p = s->top; p != NULL; p = p->link) {
		printf("%d -> ", p->data);
	}
	printf("NULL \n");
}
element pop(LinkedStackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있음 \n");
		exit(1);
	}
	else {
		StackNode *temp = s->top; // temp노드로 s->top이 가리키는 스택으로 초기화
		int data = temp->data; // 현재 데이터를 data 변수안에 복사
		s->top = s->top->link;	// 현재의 탑이 가리키는 다음 노드를 s->top에 복사
		free(temp);	// temp 소멸시켜서 temp가 가리키던 삭제하려는 노드의 연결을 끊음
		return data;	// 삭제하는 노드가 가지고 있던 데이터를 반환
	}
}
int main() {
	LinkedStackType s;
	init(&s);
	for (int i = 0; i < 5; i++) {
		push(&s, i + 2);
		print_stack(&s);
	}
	for (int i = 0; i < 5; i++) {
		pop(&s);
		print_stack(&s);
	}
	return 0;
}
