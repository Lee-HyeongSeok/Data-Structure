#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 4

typedef struct { //�ֱ����ġ
	int data[MAX_STACK_SIZE]; //������
	int seq[MAX_STACK_SIZE]; // ����, ���� ���� �� �������� ���� ���� ����
	int top; //ĳ���� �����Ͱ� ��� ���ִ��� ī��Ʈ
}StackType;

void init_stack(StackType *s) { //ĳ�� �޸𸮸� �ʱ�ȭ �����ִ� �Լ�
	s->top = -1; //ĳ�� �޸𸮿� �ƹ� �͵� ������� ����
	for (int i = 0; i < MAX_STACK_SIZE; i++) { //������ ��� 0����, �����ʹ� ��� 99�� �ʱ�ȭ �����ش�
		s->seq[i] = 0;
		s->data[i] = 99;
	}
}

void ShowCache(StackType *s) { //ĳ�� �޸��� ���¸� �����ִ� �Լ�
	printf("ĳ�ú�� �ֱ����ġ_��Ϲ�ȣ\n");
	for (int i = 0; i <= s->top; i++) {
		printf("  %d		%d \n", i, s->data[i]);
	}
}

int Max(StackType *s) { //ĳ�ø޸𸮰� �� á�� �� ���� ������ ���� seq�� ���� ũ��.
	int max = 0; // ������ ���� ū �� ã�� ����
	int index = 0; // ������ ���� ū ���� �ε���
	max = s->seq[0]; // ù ��° ĳ�� �޸𸮸� �־��ش�
	for (int i = 1; i < MAX_STACK_SIZE; i++) { //������ ĳ�� �޸��� ��ϵ�� ���Ͽ� ���� ������ ���� ū ���� ã�´�
		if (max < s->seq[i]) {
			max = s->seq[i];
			index = i;
		}
	}
	return index;
}

int push(StackType*s, int data) { // ĳ�� �޸𸮿� 3�� ������ �����Ͱ� ���� ���� ���� ������ ���� �����ش�
	int hit = 0;
	if (s->top < 3) { // ĳ�� �޸𸮰� ���� �� ��ä���� ���� ��
		for (int i = 0; i <= s->top + 1; i++) { // top+1��ŭ���� hit�� �����Ͱ� �ִ��� Ž���ϰ�, ���ٸ� ���� �߰����ش�
			if (s->data[i] == data) {   //hit�ȴٸ�
				if (s->seq[i] != 1) { //hit�� ���� �ð��� 1�̸� �������� 1�� ������ �ʿ䰡 ���� �״�� ����ȴ�
					for (int j = 0; j <= s->top + 1; j++) { //������ ĳ�ø޸𸮿� +1�� ���ش�.
						if (j == i)
							continue;
						else
							s->seq[j]++;
					}
				}
				s->seq[i] = 1;
				hit++;
				break;
			}
		}
		if (hit == 0) { //hit�� �ȵǸ� ���� �߰����ش�
			s->data[++(s->top)] = data;
			s->seq[s->top] = 1;
			for (int i = 0; i < s->top; i++)
				s->seq[i]++;
		}
	}
	else if (s->top==3) {   // ĳ�� �޸𸮰� �� ä���� ���� ��
		int index = 0;
		for (int i = 0; i < MAX_STACK_SIZE; i++) { //hit ���� ?
			if (s->data[i] == data) {
				if (s->seq[i] != 1) { //hit�� ���� �ð��� 1�̸� �������� 1�� ������ �ʿ䰡 ���� �״�� ����ȴ�
					for (int j = 0; j < MAX_STACK_SIZE; j++) {
						if (j == i)
							continue;
						else
							s->seq[j]++;
					}
				}
				s->seq[i] = 1;
				hit++;
				break;
			}
		}
		if (hit==0) { //hit�� �ȵǸ� ���� �߰����ش�
			index = Max(s); // ���� ������ ������ �ε��� �޾ƿ�(���� ���� ĳ�ÿ� ������)
			s->data[index] = data; //���� ������ �����͸� �ٲ���
			s->seq[index] = 1; // 1���� �ٽ� �ʱ�ȭ
			for (int i = 0; i < MAX_STACK_SIZE; i++) {
				if (index == i)
					continue;
				else
					s->seq[i]++;
			}
		}
	}
	
	return hit; //hit�� ������ 1,�ƴϸ� 0�� ��ȯ
}

void readfile(StackType*s) {
	int cnt = 0,hit=0,block=0;
	FILE *fp;
	fp = fopen("c:\\input.txt", "r"); //���� �����
	int buffer;
	if (fp == NULL) {
		printf("����");
		exit(1);
	}
	while (fscanf(fp, "%d", &buffer) != EOF) { //buffer�� ���� �� ���� �Ǵ� 30�� �Էµ� �� ����(������ �Է�����)
		if (buffer == 99 || block++ >= 30) //99�� �Էµǰų� 30�� ���� ���� ����� �ԷµǸ� break
			break;
		hit += push( s, buffer); //hit�� ����ŭ �����Ͽ� �����ش�.
		cnt++;  //�� ��� �ֱ����ġ ����� �ԷµǾ�����
	}
	ShowCache(s);
	printf("-----------------------\n");
	printf("���߷� : %d / %d\n", hit, cnt);
	printf("-----------------------\n");
	fclose(fp);
}

int main() {
	StackType s;
	init_stack(&s);
	readfile(&s);
	system("pause");
}