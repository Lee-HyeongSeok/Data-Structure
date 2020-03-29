#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 4

typedef struct { //주기억장치
	int data[MAX_STACK_SIZE]; //데이터
	int use_set[MAX_STACK_SIZE]; // 몇번 사용되었는지 카운트
	int num[MAX_STACK_SIZE]; //들어오는 버퍼가 몇번째로 들어왔는지
	int top;
}StackType;

void init_stack(StackType *s) { //주기억장치를 초기화 시켜주는 함수
	s->top = -1;
	for (int i = 0; i < MAX_STACK_SIZE; i++) {
		s->data[i] = 0;
		s->use_set[i] = 0;
	}
}

int is_full(StackType *s) { //가득찼니?
	return (s->top == (MAX_STACK_SIZE - 1));
}

int count(StackType *s) { //주기억장치가 다 찼을 때 사용된 횟수를 비교하여 제일 작은 값을 사용하고 사용된 횟수가 같을경우 더 먼저 입력된 값을 사용한다
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
void ShowStack(StackType *s) { //주기억장치의 상태를 보여주는 함수
	printf("Freq   Value\n");
	for (int i = 0; i <= s->top; i++) {
		printf("%d   %d \n", s->use_set[i], s->data[i], s->num[i]);
	}
}
int push(StackType*s, int val, int num) { // 주기억장치에 3개 이하의 데이터가 있을 때와 가득 차있을 때를 나눠준다
	int hit = 0;

	// 그렇지 않으면 같은 값이 있는지 검사하고 다음 인덱스에 넣어줘야함
	// 또 인덱스가 다 채워져있을 때는 가장 오래된 값을 카운트했던 것을 넣어줘야함
	if (s->top < 3) { // 스택이 아직 다 안채워져 있을 때
		for (int i = 0; i < MAX_STACK_SIZE; i++) {
			if (s->data[i] == val) {  // 같은 값이 있으면 hit!! Frequent  +1해주고 hit+1
				s->use_set[i] += 1;
				s->num[i] = num;//
				hit++;
				printf("hit\n\n");
				break;
			}
			else { //같은 값이 없으면 새로 추가해준다
				s->data[++(s->top)] = val;
				s->use_set[s->top] += 1;
				s->num[s->top] = num;//
				break;
			}
		}
	}
	else if (is_full(s)) {   // 스택이 다 채워져 있을 때, top은 움직이지 말고 새로운 데이터 추가
		int index = 0;
		int cnt = 0;
		for (int i = 0; i < MAX_STACK_SIZE; i++) {
			if (s->data[i] == val) { // 같은 값이 있으면 hit!! Frequent  +1해주고 hit+1
				s->use_set[i] += 1;
				s->num[i] = num;
				hit++;
				printf("hit\n\n");
				break;
			}
			else {
				cnt++; // 같은 값이 없을 때 그냥 카운트
			}
		}
		if (cnt == 4) { // 한 개 라도 같은 값이 없을 때 가장 오래된 값과 교체
			index = count(s); // 가장 오래된 데이터 인덱스 받아옴(들어온 값이 캐시에 없을때)
			s->data[index] = val;
			s->use_set[index] = 1; // 1으로 다시 초기화
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
		printf("실패");
		exit(1);
	}
	while (fscanf(fp, "%d", &buffer) != EOF) { //buffer가 끝날 때 까지 또는 30번 입력될 때 까지(과제의 입력조건)
		if (buffer == 99 || i++ >= 30)
			break;
		hit += push(&s, buffer, cnt++);
	}
	printf("%d / %d", hit, cnt);
	fclose(fp);
}