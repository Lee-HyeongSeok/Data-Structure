#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_QUEUE_SIZE 100

typedef int Data;
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

typedef struct {
	TreeNode* data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;
void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType *q) {
	q->front = q->rear = 0;
}
int is_empty(QueueType *q) {
	return (q->front == q->rear);
}
int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
TreeNode* dequeue(QueueType *q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
void enqueue(QueueType *q, TreeNode* item) {
	if (is_full(q))
		error("큐가 공백상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
Data get_leaf_count(TreeNode *node) {
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) // 현재 노드의 왼쪽과 오른쪽이 NULL일 때
			return 1; // 1리턴
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right); // 왼쪽과 오른쪽 노드의 개수를 count에 저장
	}
	return count;
}
// 노드를 탐색하는 함수
TreeNode* search(TreeNode *node, Data key) {
	while (node != NULL) {
		if (key == node->data) {
			return node;
		}
		else if (key < node->data) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return NULL;
}
// 새로운 노드 생성, 헤드가 될 노드
TreeNode* new_Node(Data item) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode)); // 새로운 노드 생성
	temp->data = item; // 노드의 데이터에 전달된 item 저장
	temp->left = temp->right = NULL; // 왼쪽 링크와 오른쪽 링크 NULL로 초기화
	return temp; // 노드 반환
}
TreeNode* insert_node(TreeNode *node, Data key) { // 노드를 삽입하는 함수
	if (node == NULL) return new_Node(key); // 부모 노드가 없을 시 새 노드를 생성하는 함수에 전달된 key를 포함하여 호출

	if (key < node->data) // 전달 받은 키 값이 현재 노드의 데이터 보다 작을 때
		node->left = insert_node(node->left, key); // 노드의 왼쪽에 재귀 함수를 통해 추출된 최하단 노드를 저장한다.

	else if (key > node->data) // 전달 받은 키 값이 현재 노드의 데이터 보다 클 때
		node->right = insert_node(node->right, key); // 노드의 오른쪽에 재귀 함수를 통해 추출된 최하단 노드를 저장한다.
	return node;
}
TreeNode* min_value_node(TreeNode *node) {
	TreeNode *cur = node;
	while (cur->left != NULL) // 왼쪽에 가장 최하단에 있는 노드가 최소값을 가지게 된다.
		cur = cur->left;
	return cur;
}
// 노드를 삭제하는 함수
TreeNode* delete_node(TreeNode* root, Data key) {
	if (root == NULL) return root; // 부모노드가 없을 때 종료

	if (key < root->data) // 전달된 key값이 루트의 데이터 보다 작을 때
		root->left = delete_node(root->left, key); // 왼쪽으로 순회
	else if (key > root->data) // 전달된 key 값이 루트의 데이터 보다 클 때
		root->right = delete_node(root->right, key); // 오른쪽으로 순회
	else { // 둘 다 아닐 경우
		if (root->left == NULL) { // 부모 노드의 왼쪽이 NULL일 때
			TreeNode *temp = root->right; // 새 임시 노드에 부모 노드의 오른쪽을 복사함
			free(root); // 부모 노드 삭제
			return temp;
		}
		else if (root->right == NULL) { // 부모 노드의 오른쪽이 NULL일 때
			TreeNode *temp = root->left; // 새 임시 노드에 부모 노드의 왼쪽을 복사함
			free(root); // 원래 있던 부모 노드 삭제
			return temp;
		}
		TreeNode *temp = min_value_node(root->right);
		root->data = temp->data;
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
int get_node_count(TreeNode *root) {	// 노드 개수를 구하는 함수
	int cnt = 0;
	if (root != NULL) {
		cnt = 1 + get_node_count(root->left) + get_node_count(root->right);
	}
	return cnt;
}
int get_height(TreeNode *root) {	// 트리 높이를 구하는 함수
	int h = 0;
	if (root != NULL)
		h = 1 + max(get_height(root->left), get_height(root->right));
	return h;
}
// 중위 순환
void inorder(TreeNode *root) {
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}
// 전위 순환
void preorder(TreeNode *root) {
	if (root) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
// 레벨 순환
void level_order(TreeNode *root) {
	QueueType q;

	init_queue(&q);

	if (root == NULL) return;
	enqueue(&q, root);
	while (!is_empty(&q)) {
		root = dequeue(&q);
		printf("[%d] ", root->data);
		if (root->left)
			enqueue(&q, root->left);
		if (root->right)
			enqueue(&q, root->right);
	}
}
// 후위 순환
void postorder(TreeNode *root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}
int Func(int repeat) { // 전달된 인자 만큼 2의 n제곱근을 구해주는 함수
	int mit = 2;
	int mult = 1;
	if (repeat == 0) {
		return mult;
	}
	else
	{
		for (int i = 0; i < repeat; i++)
		{
			mult *= mit;
		}
	}
	return mult;
}
// 트리 출력
void ShowGraphic(TreeNode *root) {
	int a = 0;
	int b = 0;
	int z = 0;

	int height = get_height(root);
	int numOfNode = get_node_count(root);

	QueueType q;

	init_queue(&q);

	if (root == NULL) return;
	enqueue(&q, root);

	while (!is_empty(&q)) {
		for (a = 1; a < numOfNode*height; a++) {   // 1~15 피라미드 높이
			int num = Func(a - 1);

			for (b = 0; b < num; b++) {
				for (z = 0; z < numOfNode*height - a; z++) {
					printf(" ");
				}
				root = dequeue(&q);
				printf(" [%d] ", root->data);
				if (root->left)
					enqueue(&q, root->left);
				if (root->right)
					enqueue(&q, root->right);

			}
			printf("\n");

		}
	}
}


void printMenu() {
	printf("1. 삽입 \n");
	printf("2. 삭제 \n");
	printf("3. 중위 순환 \n");
	printf("4. 전위 순환 \n");
	printf("5. 후위 순환 \n");
	printf("6. 레벨 순환 \n");
	printf("7. 탐색 \n");
	printf("8. 종료 \n");
	printf("9. 트리 모양 구현 \n");
}
int main() {
	int value;
	int choice;
	int s_num=0;

	TreeNode *root = NULL;
	TreeNode *S = NULL;
	printMenu();
	do {
		printf(" <<<<<<< 메뉴 선택 >>>>>>> \n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: 
			printf("값 입력 : ");
			scanf("%d", &value);
			if (sizeof(value) != sizeof(int)) {
				printf("입력한 값이 정수가 아닙니다. ");
			}
			else {	// 정수라면
				root = insert_node(root, value);
			}
			break;
		case 2 : 
			printf("삭제할 값 입력 : ");
			scanf("%d", &value);
			if (sizeof(value) != sizeof(int)) {
				printf("입력한 값이 정수가 아닙니다. ");
				break;
			}
			else {
				root = delete_node(root, value);
			}
			break;
		case 3 : 
			printf("중위 순환 \n");
			if (root == NULL) {
				printf("노드가 존재하지 않습니다. 삽입하십시오 \n");
				break;
			}
			inorder(root);
			printf("\n");
			break;
		case 4 : 
			printf("전위 순환 \n");
			if (root == NULL) {
				printf("노드가 존재하지 않습니다. 삽입하십시오 \n");
				break;
			}
			preorder(root);
			printf("\n");
			break;
		case 5 : 
			printf("후위 순환 \n");
			if (root == NULL) {
				printf("노드가 존재하지 않습니다. 삽입하십시오 \n");
				break;
			}
			postorder(root);
			printf("\n");
			break;
		case 6 : 
			printf("레벨 순환 \n");
			if (root == NULL) {
				printf("노드가 존재하지 않습니다. 삽입하십시오 \n");
				break;
			}
			level_order(root);
			printf("\n");
			break;
		case 7 :
			if (root == NULL) {
				if (root == NULL) {
					printf("\n노드가 존재하지 않습니다. 삽입하십시오 \n");
					break;
				}
			}
			printf("탐색할 값 입력[ 탐색 종료 시 0번 ]");
			scanf("%d", &s_num);
			if (s_num == 0) {
				printf("탐색 종료...\n");
				break;
			}
			S = search(root, s_num);
			if (S == NULL) {
				printf("탐색 실패 \n");
				break;
			}
			else {
				printf("%d를 찾았습니다. \n", s_num);
				break;
			}
			break;
		case 8 : 
			printf("프로그램 종료 \n");
			return 0;
			break;
		case 9 : 
			ShowGraphic(root);
			break;
		default : 
			printf("그 외의 값 입력 \n");
			break;
		}
		
	} while (choice != 8);
	
}



