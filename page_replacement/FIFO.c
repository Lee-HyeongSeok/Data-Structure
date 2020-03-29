#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3
int hit = 0; // hit		��Ʈ�� ����
int count = 0; // count ��ü���� ����

typedef struct {
	int list[MAX_SIZE];
	int length;
} ArrayList;

// �迭�Ǳ��� �ʱ�ȭ
void init(ArrayList *L)
{
	L->length = 0;
}

void add(ArrayList *L, int item);
void display(ArrayList *L);

int main() {
	// ���� ���� ������ ǥ��
	// �迭����Ʈ ����
	ArrayList list1;
	init(&list1);

	// D����̺��� input.txt ������ ���ϴ�.
	FILE * fp;
	fp = fopen("D:\\input2.txt", "rt");

	int buffer;

	while (fscanf(fp, "%d", &buffer) != EOF) {
		// 99�� �Ǳ������� �ݺ�!
		if (buffer == 99)
			break;

		// ���߰��� ���
		add(&list1, buffer);
		count++;
	}
	printf("���߷��� %d/%d �Դϴ�.\n", hit, count);
	fclose(fp);
}

void add(ArrayList *L, int item)
{
	int i;
	for (i = 0; i < L->length; i++) {
		// list���ڿ� ���� ���ڰ� ������ hit����
		if (L->list[i] == item) {
			printf("Hit!!\n\n");
			hit++;
			return;
		}
	}
	// �迭�� �� ����
	L->list[(count - hit) % 3] = item;

	//  �迭�� ������ �ʾҴٸ� length 1����
	if (L->length < MAX_SIZE)
		L->length++;

	// �� ���
	display(L);
}

void display(ArrayList *L) {
	int i;
	// ���� ���
	for (i = 0; i < L->length; i++) {
		printf("%2d", L->list[i]);
		if (i != L->length - 1)
			printf(" : ");
	}
	printf("\n--------------\n\n");
}
