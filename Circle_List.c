#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char element[100];
typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

// ���� ���ڿ��� ���ڷ� ���� ����
ListNode* insert_first(ListNode *head, element data) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));// ���ο� ��� ����
	strcpy(newNode->data, data); // ���ڷ� ���޹��� ���ڿ��� strcpy �Լ��� �� ����� ���ڿ� �迭�� ����
	if (head == NULL) { // ��尡 NULL�� ��
		head = newNode; // ��忡 ���ο� ��� ����
		newNode->link = head; // ���ο� ����� ��ũ�� ��带 ����Ŵ
	}
	else { // �Ǵ� 
		newNode->link = head->link; // ���ο� ����� ��ũ�� ��尡 ����Ű�� ��ũ�� �ּҸ� ����
		head->link = newNode; // ���ο� ��尡 ��尡 ����Ű�� ��ũ�� �ּ����·� ����
	}
	return head; // ��� ��ȯ 
}
ListNode* insert_last(ListNode *head, element data) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode)); // ���ο� ��� ����
	strcpy(newNode->data, data); // ���ο� ����� ���ڿ� �迭�� ���ڷ� ���޵� ���ڿ� �迭 ����
	if (head == NULL) {
		head = newNode; // ��尡 ���ο� ���� ���� �ȴ�.
		newNode->link = head; //�� ����� ��ũ���� ����� �ּҰ� ���� 
	}
	else {
		newNode->link = head->link; // �� ����� ��ũ�� ��尡 ����Ű�� �ִ� ����� �ּ� ����
		head->link = newNode; // ��尡 ����ų ���� ���ο� ���
		head = newNode; // ��忡 ���ο� ��� ���� 
	}
	return head; // ��� ��ȯ 
}
void print_list(ListNode *head) {
	ListNode *p; // ����ü ���� ����
	
	if (head == NULL) return; // �ƹ��͵� ���� �� ���� 
	p = head->link; // �� ����ü ������ ��尡 ����Ű�� ��带 ����
	while (p != head) { // ��尡 �ƴ� �� �ݺ��� ����, p�� ��尡 ����Ű�� ���� ��尡 ����Ǿ����� 
	printf("%s -> ", p->data); // ����� ������ ���
		p = p->link; // p�� ����Ű�� ���� ��尡 p�� ����� 
		
	}
	printf("%s -> ", p->data); // ������ ����� ������ ���, ��尡 ����Ű�� ���� ������ �����߱� ����
	
}
// ����Ʈ�� ���̸� ��ȯ�ϴ� �Լ� 
int Get_list_Length(ListNode *head) {
	ListNode *cur = head;
	cur = cur->link;
	int cnt = 1;
	for (; cur != head; cur = cur->link) {
		++cnt;
	}
	return cnt;
}
int main() {
	ListNode *head = NULL;

	char *str = NULL;
	int num = 0;
	printf("�÷��� �ο� �Է�");
	scanf("%d", &num);

	str = (char*)malloc(sizeof(num));

	for (int i = 0; i < num; i++) {
		printf("�÷��̾� �̸� �Է� : ");
		scanf("%s", str);
		head = insert_first(head, str);
	}

	ListNode *p = head;
	for (int i = 0; i < 10; i++) {
		printf("���� ���� = %s \n", p->data);
		p = p->link;
	}
	return 0;
	
	return 0;
}
