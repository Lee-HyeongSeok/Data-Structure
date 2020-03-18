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
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
void enqueue(QueueType *q, TreeNode* item) {
	if (is_full(q))
		error("ť�� ��������Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
Data get_leaf_count(TreeNode *node) {
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) // ���� ����� ���ʰ� �������� NULL�� ��
			return 1; // 1����
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right); // ���ʰ� ������ ����� ������ count�� ����
	}
	return count;
}
// ��带 Ž���ϴ� �Լ�
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
// ���ο� ��� ����, ��尡 �� ���
TreeNode* new_Node(Data item) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode)); // ���ο� ��� ����
	temp->data = item; // ����� �����Ϳ� ���޵� item ����
	temp->left = temp->right = NULL; // ���� ��ũ�� ������ ��ũ NULL�� �ʱ�ȭ
	return temp; // ��� ��ȯ
}
TreeNode* insert_node(TreeNode *node, Data key) { // ��带 �����ϴ� �Լ�
	if (node == NULL) return new_Node(key); // �θ� ��尡 ���� �� �� ��带 �����ϴ� �Լ��� ���޵� key�� �����Ͽ� ȣ��

	if (key < node->data) // ���� ���� Ű ���� ���� ����� ������ ���� ���� ��
		node->left = insert_node(node->left, key); // ����� ���ʿ� ��� �Լ��� ���� ����� ���ϴ� ��带 �����Ѵ�.

	else if (key > node->data) // ���� ���� Ű ���� ���� ����� ������ ���� Ŭ ��
		node->right = insert_node(node->right, key); // ����� �����ʿ� ��� �Լ��� ���� ����� ���ϴ� ��带 �����Ѵ�.
	return node;
}
TreeNode* min_value_node(TreeNode *node) {
	TreeNode *cur = node;
	while (cur->left != NULL) // ���ʿ� ���� ���ϴܿ� �ִ� ��尡 �ּҰ��� ������ �ȴ�.
		cur = cur->left;
	return cur;
}
// ��带 �����ϴ� �Լ�
TreeNode* delete_node(TreeNode* root, Data key) {
	if (root == NULL) return root; // �θ��尡 ���� �� ����

	if (key < root->data) // ���޵� key���� ��Ʈ�� ������ ���� ���� ��
		root->left = delete_node(root->left, key); // �������� ��ȸ
	else if (key > root->data) // ���޵� key ���� ��Ʈ�� ������ ���� Ŭ ��
		root->right = delete_node(root->right, key); // ���������� ��ȸ
	else { // �� �� �ƴ� ���
		if (root->left == NULL) { // �θ� ����� ������ NULL�� ��
			TreeNode *temp = root->right; // �� �ӽ� ��忡 �θ� ����� �������� ������
			free(root); // �θ� ��� ����
			return temp;
		}
		else if (root->right == NULL) { // �θ� ����� �������� NULL�� ��
			TreeNode *temp = root->left; // �� �ӽ� ��忡 �θ� ����� ������ ������
			free(root); // ���� �ִ� �θ� ��� ����
			return temp;
		}
		TreeNode *temp = min_value_node(root->right);
		root->data = temp->data;
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}
int get_node_count(TreeNode *root) {	// ��� ������ ���ϴ� �Լ�
	int cnt = 0;
	if (root != NULL) {
		cnt = 1 + get_node_count(root->left) + get_node_count(root->right);
	}
	return cnt;
}
int get_height(TreeNode *root) {	// Ʈ�� ���̸� ���ϴ� �Լ�
	int h = 0;
	if (root != NULL)
		h = 1 + max(get_height(root->left), get_height(root->right));
	return h;
}
// ���� ��ȯ
void inorder(TreeNode *root) {
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}
// ���� ��ȯ
void preorder(TreeNode *root) {
	if (root) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
// ���� ��ȯ
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
// ���� ��ȯ
void postorder(TreeNode *root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}
int Func(int repeat) { // ���޵� ���� ��ŭ 2�� n�������� �����ִ� �Լ�
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
// Ʈ�� ���
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
		for (a = 1; a < numOfNode*height; a++) {   // 1~15 �Ƕ�̵� ����
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
	printf("1. ���� \n");
	printf("2. ���� \n");
	printf("3. ���� ��ȯ \n");
	printf("4. ���� ��ȯ \n");
	printf("5. ���� ��ȯ \n");
	printf("6. ���� ��ȯ \n");
	printf("7. Ž�� \n");
	printf("8. ���� \n");
	printf("9. Ʈ�� ��� ���� \n");
}
int main() {
	int value;
	int choice;
	int s_num=0;

	TreeNode *root = NULL;
	TreeNode *S = NULL;
	printMenu();
	do {
		printf(" <<<<<<< �޴� ���� >>>>>>> \n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: 
			printf("�� �Է� : ");
			scanf("%d", &value);
			if (sizeof(value) != sizeof(int)) {
				printf("�Է��� ���� ������ �ƴմϴ�. ");
			}
			else {	// �������
				root = insert_node(root, value);
			}
			break;
		case 2 : 
			printf("������ �� �Է� : ");
			scanf("%d", &value);
			if (sizeof(value) != sizeof(int)) {
				printf("�Է��� ���� ������ �ƴմϴ�. ");
				break;
			}
			else {
				root = delete_node(root, value);
			}
			break;
		case 3 : 
			printf("���� ��ȯ \n");
			if (root == NULL) {
				printf("��尡 �������� �ʽ��ϴ�. �����Ͻʽÿ� \n");
				break;
			}
			inorder(root);
			printf("\n");
			break;
		case 4 : 
			printf("���� ��ȯ \n");
			if (root == NULL) {
				printf("��尡 �������� �ʽ��ϴ�. �����Ͻʽÿ� \n");
				break;
			}
			preorder(root);
			printf("\n");
			break;
		case 5 : 
			printf("���� ��ȯ \n");
			if (root == NULL) {
				printf("��尡 �������� �ʽ��ϴ�. �����Ͻʽÿ� \n");
				break;
			}
			postorder(root);
			printf("\n");
			break;
		case 6 : 
			printf("���� ��ȯ \n");
			if (root == NULL) {
				printf("��尡 �������� �ʽ��ϴ�. �����Ͻʽÿ� \n");
				break;
			}
			level_order(root);
			printf("\n");
			break;
		case 7 :
			if (root == NULL) {
				if (root == NULL) {
					printf("\n��尡 �������� �ʽ��ϴ�. �����Ͻʽÿ� \n");
					break;
				}
			}
			printf("Ž���� �� �Է�[ Ž�� ���� �� 0�� ]");
			scanf("%d", &s_num);
			if (s_num == 0) {
				printf("Ž�� ����...\n");
				break;
			}
			S = search(root, s_num);
			if (S == NULL) {
				printf("Ž�� ���� \n");
				break;
			}
			else {
				printf("%d�� ã�ҽ��ϴ�. \n", s_num);
				break;
			}
			break;
		case 8 : 
			printf("���α׷� ���� \n");
			return 0;
			break;
		case 9 : 
			ShowGraphic(root);
			break;
		default : 
			printf("�� ���� �� �Է� \n");
			break;
		}
		
	} while (choice != 8);
	
}



