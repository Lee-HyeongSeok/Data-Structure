#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char element[100];
typedef struct ListNode {
	element data;
	struct ListNode *link;
}ListNode;

// 헤드와 문자열을 인자로 전달 받음
ListNode* insert_first(ListNode *head, element data) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));// 새로운 노드 생성
	strcpy(newNode->data, data); // 인자로 전달받은 문자열을 strcpy 함수로 새 노드의 문자열 배열에 복사
	if (head == NULL) { // 헤드가 NULL일 때
		head = newNode; // 헤드에 새로운 노드 복사
		newNode->link = head; // 새로운 노드의 링크는 헤드를 가르킴
	}
	else { // 또는 
		newNode->link = head->link; // 새로운 노드의 링크가 헤드가 가르키는 링크의 주소를 가짐
		head->link = newNode; // 새로운 노드가 헤드가 가르키는 링크에 주소형태로 저장
	}
	return head; // 헤드 반환 
}
ListNode* insert_last(ListNode *head, element data) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode)); // 새로운 노드 생성
	strcpy(newNode->data, data); // 새로운 노드의 문자열 배열에 인자로 전달된 문자열 배열 복사
	if (head == NULL) {
		head = newNode; // 헤드가 새로운 노드로 복사 된다.
		newNode->link = head; //새 노드의 링크에는 헤드의 주소가 저장 
	}
	else {
		newNode->link = head->link; // 새 노드의 링크에 헤드가 가리키고 있는 노드의 주소 저장
		head->link = newNode; // 헤드가 가르킬 노드는 새로운 노드
		head = newNode; // 헤드에 새로운 노드 복사 
	}
	return head; // 헤드 반환 
}
void print_list(ListNode *head) {
	ListNode *p; // 구조체 변수 선언
	
	if (head == NULL) return; // 아무것도 없을 시 종료 
	p = head->link; // 새 구조체 변수에 헤드가 가리키는 노드를 복사
	while (p != head) { // 헤드가 아닐 때 반복문 실행, p는 헤드가 가리키는 다음 노드가 복사되어있음 
	printf("%s -> ", p->data); // 노드의 데이터 출력
		p = p->link; // p가 가리키는 다음 노드가 p에 저장됨 
		
	}
	printf("%s -> ", p->data); // 마지막 헤드의 데이터 출력, 헤드가 가리키는 다음 노드부터 시작했기 때문
	
}
// 리스트의 길이를 반환하는 함수 
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
	printf("플래이 인원 입력");
	scanf("%d", &num);

	str = (char*)malloc(sizeof(num));

	for (int i = 0; i < num; i++) {
		printf("플레이어 이름 입력 : ");
		scanf("%s", str);
		head = insert_first(head, str);
	}

	ListNode *p = head;
	for (int i = 0; i < 10; i++) {
		printf("현재 차례 = %s \n", p->data);
		p = p->link;
	}
	return 0;
	
	return 0;
}
