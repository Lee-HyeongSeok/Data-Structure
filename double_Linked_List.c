#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DlistNode {
	element data;
	struct DlistNode *llink; // 왼쪽 노드를 저장
	struct DlistNode *rlink; // 오른쪽 노드를 저장
}DlistNode;

void init(DlistNode *phead) {
	phead->llink = phead; // 헤드 노드로 둘 다 초기화 시킨다.
	phead->rlink = phead;
}
void print_dlist(DlistNode *phead) {
	DlistNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink) { // 오른쪽으로 이동시킴
		printf(" <-| | %s | |-> ", p->data);
	}
	printf("\n");
}

// 노드에 데이터를 찾는 함수
void Find_data(DlistNode *phead, element data) { // 헤드와 찾을 데이터를 인자로 전달 받는다.
	DlistNode *p; // 빈 노드 선언
	int i = 1;
	p = phead->rlink; // 오른쪽으로 순회하기 위한 선언
	while (data != phead->data) { // 데이터를 찾을 때 까지
		if (data == phead->data) { // 데이터를 찾았을 때
			printf("find \n");
		}
		else { // 못 찾았을 때 계속 순회
			p = p->rlink;
		}
	}
}

//새로운 데이터를 노드 before의 오른쪽에 삽입
void dinsert(DlistNode *before, element data) {
	DlistNode *newNode = (DlistNode*)malloc(sizeof(DlistNode)); // 새로운 노드 생성

	strcpy(newNode->data, data); // 인자로 전달된 데이터를 새로운 노드의 데이터에 복사
	newNode->llink = before; // 새 노드의 왼쪽 링크는 전달 받은 노드를 가리킴
	newNode->rlink = before->rlink; // 새 노드의 오른쪽 링크는 전달 받은 노드가 가리키는 오른쪽 노드를 가리킴
	before->rlink->llink = newNode; // 전달 받은 노드의 오른쪽 링크가 가리키는 노드의 왼쪽 링크는 새로운 노드를 가리킴
	before->rlink = newNode; // 전달 받은 노드의 오른쪽 링크는 새 노드를 가리킴
}
void ddelete(DlistNode *head, DlistNode *removed) {
	if (removed == head) return; // 제거할 노드와 헤드가 같으면 종료
	removed->llink->rlink = removed->rlink; // 제거할 노드의 왼쪽 링크에 저장된 노드의 오른쪽 링크에 제거할 노드의 오른쪽 링크가 가리키는 노드를 저장
	removed->rlink->llink = removed->llink; // 제거할 노드의 오른쪽 링크에 저장된 노드의 왼쪽 링크에 제거할 노드의 왼쪽 링크가 가리키는 노드를 저장
	free(removed); // 노드 메모리 해제
}
int main() {
	DlistNode *head = (DlistNode*)malloc(sizeof(DlistNode)); // 헤드 선언
	DlistNode *cur = NULL; // 순회를 위한 구조체 포인터 변수 선언
	char ch; // 문자를 입력 받기 위한 변수선언
	init(head); // 헤드 초기화
	dinsert(head, "Mamamia");
	dinsert(head, "Dancing Queen");
	dinsert(head, "Fernando");

	cur = head->rlink; // 헤드의 오른쪽 링크 복사
	print_dlist(head); // 헤드를 기준으로 모든 리스트 출력

	do {
		printf("\n 명령어 입력 : (<, >, q) : ");
		ch = getchar();
		if (ch == '<') { // 노드를 왼쪽으로 순회
			cur = cur->llink;
			if (cur == head)
				cur = cur->llink;
		}
		else if (ch == '>') { // 노드를 오른쪽으로 순회
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
