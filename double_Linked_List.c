#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DlistNode {
	element data;
	struct DlistNode *llink; // ���� ��带 ����
	struct DlistNode *rlink; // ������ ��带 ����
}DlistNode;

void init(DlistNode *phead) {
	phead->llink = phead; // ��� ���� �� �� �ʱ�ȭ ��Ų��.
	phead->rlink = phead;
}
void print_dlist(DlistNode *phead) {
	DlistNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink) { // ���������� �̵���Ŵ
		printf(" <-| | %s | |-> ", p->data);
	}
	printf("\n");
}

// ��忡 �����͸� ã�� �Լ�
void Find_data(DlistNode *phead, element data) { // ���� ã�� �����͸� ���ڷ� ���� �޴´�.
	DlistNode *p; // �� ��� ����
	int i = 1;
	p = phead->rlink; // ���������� ��ȸ�ϱ� ���� ����
	while (data != phead->data) { // �����͸� ã�� �� ����
		if (data == phead->data) { // �����͸� ã���� ��
			printf("find \n");
		}
		else { // �� ã���� �� ��� ��ȸ
			p = p->rlink;
		}
	}
}

//���ο� �����͸� ��� before�� �����ʿ� ����
void dinsert(DlistNode *before, element data) {
	DlistNode *newNode = (DlistNode*)malloc(sizeof(DlistNode)); // ���ο� ��� ����

	strcpy(newNode->data, data); // ���ڷ� ���޵� �����͸� ���ο� ����� �����Ϳ� ����
	newNode->llink = before; // �� ����� ���� ��ũ�� ���� ���� ��带 ����Ŵ
	newNode->rlink = before->rlink; // �� ����� ������ ��ũ�� ���� ���� ��尡 ����Ű�� ������ ��带 ����Ŵ
	before->rlink->llink = newNode; // ���� ���� ����� ������ ��ũ�� ����Ű�� ����� ���� ��ũ�� ���ο� ��带 ����Ŵ
	before->rlink = newNode; // ���� ���� ����� ������ ��ũ�� �� ��带 ����Ŵ
}
void ddelete(DlistNode *head, DlistNode *removed) {
	if (removed == head) return; // ������ ���� ��尡 ������ ����
	removed->llink->rlink = removed->rlink; // ������ ����� ���� ��ũ�� ����� ����� ������ ��ũ�� ������ ����� ������ ��ũ�� ����Ű�� ��带 ����
	removed->rlink->llink = removed->llink; // ������ ����� ������ ��ũ�� ����� ����� ���� ��ũ�� ������ ����� ���� ��ũ�� ����Ű�� ��带 ����
	free(removed); // ��� �޸� ����
}
int main() {
	DlistNode *head = (DlistNode*)malloc(sizeof(DlistNode)); // ��� ����
	DlistNode *cur = NULL; // ��ȸ�� ���� ����ü ������ ���� ����
	char ch; // ���ڸ� �Է� �ޱ� ���� ��������
	init(head); // ��� �ʱ�ȭ
	dinsert(head, "Mamamia");
	dinsert(head, "Dancing Queen");
	dinsert(head, "Fernando");

	cur = head->rlink; // ����� ������ ��ũ ����
	print_dlist(head); // ��带 �������� ��� ����Ʈ ���

	do {
		printf("\n ��ɾ� �Է� : (<, >, q) : ");
		ch = getchar();
		if (ch == '<') { // ��带 �������� ��ȸ
			cur = cur->llink;
			if (cur == head)
				cur = cur->llink;
		}
		else if (ch == '>') { // ��带 ���������� ��ȸ
			cur = cur->rlink;
			if (cur == head)
				cur = cur->rlink;
		}
		print_dlist(head); 
		getchar();
	} while (ch != 'q');

	for (int i = 0; i < 3; i++) {
		ddelete(head, head->rlink);
	}
	free(head);
	return 0;
}
