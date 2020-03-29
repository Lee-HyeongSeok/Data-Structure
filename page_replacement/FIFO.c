#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3
int hit = 0; // hit		히트한 개수
int count = 0; // count 전체실행 개수

typedef struct {
	int list[MAX_SIZE];
	int length;
} ArrayList;

// 배열의길이 초기화
void init(ArrayList *L)
{
	L->length = 0;
}

void add(ArrayList *L, int item);
void display(ArrayList *L);

int main() {
	// 받은 값의 개수를 표시
	// 배열리스트 생성
	ArrayList list1;
	init(&list1);

	// D드라이브의 input.txt 파일을 엽니다.
	FILE * fp;
	fp = fopen("D:\\input2.txt", "rt");

	int buffer;

	while (fscanf(fp, "%d", &buffer) != EOF) {
		// 99가 되기전까지 반복!
		if (buffer == 99)
			break;

		// 값추가및 출력
		add(&list1, buffer);
		count++;
	}
	printf("적중률은 %d/%d 입니다.\n", hit, count);
	fclose(fp);
}

void add(ArrayList *L, int item)
{
	int i;
	for (i = 0; i < L->length; i++) {
		// list숫자와 받은 숫자가 같으면 hit증가
		if (L->list[i] == item) {
			printf("Hit!!\n\n");
			hit++;
			return;
		}
	}
	// 배열에 값 삽입
	L->list[(count - hit) % 3] = item;

	//  배열이 꽉차지 않았다면 length 1증가
	if (L->length < MAX_SIZE)
		L->length++;

	// 값 출력
	display(L);
}

void display(ArrayList *L) {
	int i;
	// 내용 출력
	for (i = 0; i < L->length; i++) {
		printf("%2d", L->list[i]);
		if (i != L->length - 1)
			printf(" : ");
	}
	printf("\n--------------\n\n");
}
