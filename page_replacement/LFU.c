#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 4

typedef struct { //�ֱ����ġ
	int data[MAX_STACK_SIZE]; //������
	int use_set[MAX_STACK_SIZE]; // ��� ���Ǿ����� ī��Ʈ
	int num[MAX_STACK_SIZE]; //������ ���۰� ���°�� ���Դ���
	int top;
}StackType;

void init_stack(StackType *s) { //�ֱ����ġ�� �ʱ�ȭ �����ִ� �Լ�
	s->top = -1;
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		s->data[i] = 0;
		s->use_set[i] = 0;
	}
}

int is_full(StackType *s) { //����á��?
	return (s->top == (MAX_STACK_SIZE - 1));
}

int count(StackType *s) { //�ֱ����ġ�� �� á�� �� ���� Ƚ���� ���Ͽ� ���� ���� ���� ����ϰ� ���� Ƚ���� ������� �� ���� �Էµ� ���� ����Ѵ�
	int min = 0;
	int index = 0;
	min = s->use_set[0];
	index = 0;
	for (int i = 1; i < MAX_STACK_SIZE; i++) {
		if (min > s->use_set[i]) {
			min = s->use_set[i];
			index = i;
		}
		else if (min == s->use_set[i]) {
			if (s->num[index] > s->num[i]) {
				min = s->use_set[i];
				index = i;
			}
		}
	}
	return index;
}
void ShowStack(StackType *s) { //�ֱ����ġ�� ���¸� �����ִ� �Լ�
	printf("Freq   Value\n");
	for (int i = 0; i <= s->top; i++) {
		printf("%d   %d \n", s->use_set[i], s->data[i], s->num[i]);
	}
}
int push(StackType*s, int val, int num) { // �ֱ����ġ�� 3�� ������ �����Ͱ� ���� ���� ���� ������ ���� �����ش�
	int hit = 0;

	// �׷��� ������ ���� ���� �ִ��� �˻��ϰ� ���� �ε����� �־������
	// �� �ε����� �� ä�������� ���� ���� ������ ���� ī��Ʈ�ߴ� ���� �־������
	if (s->top < 3) { // ������ ���� �� ��ä���� ���� ��
		for (int i = 0; i < MAX_STACK_SIZE; i++) {
			if (s->data[i] == val) {  // ���� ���� ������ hit!! Frequent  +1���ְ� hit+1
				s->use_set[i] += 1;
				s->num[i] = num;//
				hit++;
				printf("hit\n\n");
				break;
			}
			else { //���� ���� ������ ���� �߰����ش�
				s->data[++(s->top)] = val;
				s->use_set[s->top] += 1;
				s->num[s->top] = num;//
				break;
			}
		}
	}
	else if (is_full(s)) {   // ������ �� ä���� ���� ��, top�� �������� ���� ���ο� ������ �߰�
		int index = 0;
		int cnt = 0;
		for (int i = 0; i < MAX_STACK_SIZE; i++) {
			if (s->data[i] == val) { // ���� ���� ������ hit!! Frequent  +1���ְ� hit+1
				s->use_set[i] += 1;
				s->num[i] = num;
				hit++;
				printf("hit\n\n");
				break;
			}
			else {
				cnt++; // ���� ���� ���� �� �׳� ī��Ʈ
			}
		}
		if (cnt == 4) { // �� �� �� ���� ���� ���� �� ���� ������ ���� ��ü
			index = count(s); // ���� ������ ������ �ε��� �޾ƿ�(���� ���� ĳ�ÿ� ������)
			s->data[index] = val;
			s->use_set[index] = 1; // 1���� �ٽ� �ʱ�ȭ
			s->num[index] = num;
		}
	}
	ShowStack(s);
	printf("---------------\n");

	
	return hit;
}


int main() {
	StackType s;
	int cnt = 0;
	int hit = 0;
	int i = 0;
	init_stack(&s);
	FILE *fp;
	fp = fopen("c:\\input.txt", "r");
	int buffer;
	if (fp == NULL) {
		printf("����");
		exit(1);
	}
	while (fscanf(fp, "%d", &buffer) != EOF) { //buffer�� ���� �� ���� �Ǵ� 30�� �Էµ� �� ����(������ �Է�����)
		if (buffer == 99 || i++ >= 30)
			break;
		hit += push(&s, buffer, cnt++);
	}
	printf("%d / %d", hit, cnt);
	fclose(fp);
}