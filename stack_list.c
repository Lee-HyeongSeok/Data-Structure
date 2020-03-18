#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef int element;
typedef struct StackNode { // ��� ����ü
	element data;
	struct StackNode *link;
}StackNode;

typedef struct { // ���� ����ü
	StackNode *top;
}LinkedStackType;

void init(LinkedStackType *s) { // �ʱ�ȭ �Լ�
	s->top = NULL;
}
int is_empty(LinkedStackType *s) { // ������ ������� �˻�
	return (s->top == NULL);
}
int is_full(LinkedStackType *s) {	// full�� ������ �� ����.
	return 0;
}
void push(LinkedStackType *s, element data) { // ���ÿ� �����ϴ� �Լ�
	StackNode *temp = (StackNode*)malloc(sizeof(StackNode)); // ���ο� ��� ����
	temp->data = data; // �� ����� �����Ϳ� ���ڷ� ���޵� ������ ����
	temp->link = s->top; // �� ����� ��ũ�� ������ top�� ����Ű�� ��带 ����Ŵ
	s->top = temp; // ������ top�� �� ��带 ����, �� ��忡�� ������ top ������ ����
}
void print_stack(LinkedStackType *s) {
	for (StackNode *p = s->top; p != NULL; p = p->link) {
		printf("%d -> ", p->data);
	}
	printf("NULL \n");
}
element pop(LinkedStackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "������ ������� \n");
		exit(1);
	}
	else {
		StackNode *temp = s->top; // temp���� s->top�� ����Ű�� �������� �ʱ�ȭ
		int data = temp->data; // ���� �����͸� data �����ȿ� ����
		s->top = s->top->link;	// ������ ž�� ����Ű�� ���� ��带 s->top�� ����
		free(temp);	// temp �Ҹ���Ѽ� temp�� ����Ű�� �����Ϸ��� ����� ������ ����
		return data;	// �����ϴ� ��尡 ������ �ִ� �����͸� ��ȯ
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
