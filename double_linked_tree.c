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
		postorder(head->llink);	// 왼쪽 서브 트리 순회
		postorder(head->rlink);	// 오른쪽 서브 트리 순회
		printf("%d", head->data); 	// 노드 방문
	}
}
void inorder(ListNode *root) {
	if (root) {
		inorder(root->llink);	// 왼쪽서브트리 순회
		printf("%d", root->data); 	// 노드 방문
		inorder(root->rlink);	// 오른쪽서브트리 순회
	}
}
void preorder(ListNode *root) {
	if (root) {
		printf("%d", root->data); 	// 노드 방문
		preorder(root->llink);	// 왼쪽서브트리 순회
		preorder(root->rlink);	// 오른쪽서브트리 순회
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
	// do while 문을 통해 처음 초기 시작에는 왼쪽 오른쪽 넣어주는 것을 시작...
}
