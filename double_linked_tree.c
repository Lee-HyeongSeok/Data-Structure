#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct ListNode {
	Data data;
	Data numOfNode;
	struct ListNode *llink;
	struct ListNode *rlink;
}ListNode;

void init(ListNode *head) {
	head->llink = NULL;
	head->rlink = NULL;
}
ListNode* insert_Left_first(ListNode *head, Data data) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->data = data;
	
	newNode->llink = head->llink;
	head->llink = newNode;
	(head->numOfNode)++;
	return head;
}
ListNode* insert_Right_first(ListNode *head, Data data) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->data = data;

	newNode->rlink = head->rlink;
	head->rlink = newNode;
	(head->numOfNode)++;
	return head;
}
void postorder(ListNode *head) {
	if (head) {
		postorder(head->llink);	// ���� ���� Ʈ�� ��ȸ
		postorder(head->rlink);	// ������ ���� Ʈ�� ��ȸ
		printf("%d", head->data); 	// ��� �湮
	}
}
void inorder(ListNode *root) {
	if (root) {
		inorder(root->llink);	// ���ʼ���Ʈ�� ��ȸ
		printf("%d", root->data); 	// ��� �湮
		inorder(root->rlink);	// �����ʼ���Ʈ�� ��ȸ
	}
}
void preorder(ListNode *root) {
	if (root) {
		printf("%d", root->data); 	// ��� �湮
		preorder(root->llink);	// ���ʼ���Ʈ�� ��ȸ
		preorder(root->rlink);	// �����ʼ���Ʈ�� ��ȸ
	}
}
int main() {
	ListNode *head = (ListNode*)malloc(sizeof(ListNode));
	init(head);
	for (int i = 0; i < 5; i++) {
		head = insert_Left_first(head, i + 1);
		head = insert_Right_first(head, i + 2);
	}
	for (int i = 10; i < 15; i++) {
		head = insert_Right_first(head, i + 2);
	}
	postorder(head);
	preorder(head);
	inorder(head);
	// do while ���� ���� ó�� �ʱ� ���ۿ��� ���� ������ �־��ִ� ���� ����...
}
