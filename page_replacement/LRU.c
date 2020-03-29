#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 4

typedef struct { //주기억장치
	int data[MAX_STACK_SIZE]; //데이터
	int seq[MAX_STACK_SIZE]; // 순서, 제일 먼저 들어간 데이터의 값이 제일 높다
	int top; //캐쉬에 데이터가 몇개가 들어가있는지 카운트
}StackType;

void init_stack(StackType *s) { //캐시 메모리를 초기화 시켜주는 함수
	s->top = -1; //캐시 메모리에 아무 것도 들어있지 않음
	for (int i = 0; i < MAX_STACK_SIZE; i++) { //순서를 모두 0으로, 데이터는 모두 99로 초기화 시켜준다
		s->seq[i] = 0;
		s->data[i] = 99;
	}
}

void ShowCache(StackType *s) { //캐시 메모리의 상태를 보여주는 함수
	printf("캐시블록 주기억장치_블록번호\n");
	for (int i = 0; i <= s->top; i++) {
		printf("  %d		%d \n", i, s->data[i]);
	}
}

int Max(StackType *s) { //캐시메모리가 다 찼을 때 가장 오래된 것의 seq가 제일 크다.
	int max = 0; // 순서가 가장 큰 값 찾는 변수
	int index = 0; // 순서가 가장 큰 갑의 인덱스
	max = s->seq[0]; // 첫 번째 캐시 메모리를 넣어준다
	for (int i = 1; i < MAX_STACK_SIZE; i++) { //나머지 캐시 메모리의 블록들과 비교하여 가장 순서가 가장 큰 값을 찾는다
		if (max < s->seq[i]) {
			max = s->seq[i];
			index = i;
		}
	}
	return index;
}

int push(StackType*s, int data) { // 캐시 메모리에 3개 이하의 데이터가 있을 때와 가득 차있을 때로 나눠준다
	int hit = 0;
	if (s->top < 3) { // 캐시 메모리가 아직 다 안채워져 있을 때
		for (int i = 0; i <= s->top + 1; i++) { // top+1만큼동안 hit한 데이터가 있는지 탐색하고, 없다면 새로 추가해준다
			if (s->data[i] == data) {   //hit된다면
				if (s->seq[i] != 1) { //hit한 것의 시간이 1이면 나머지에 1을 더해줄 필요가 없이 그대로 가면된다
					for (int j = 0; j <= s->top + 1; j++) { //나머지 캐시메모리에 +1씩 해준다.
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
		if (hit == 0) { //hit가 안되면 새로 추가해준다
			s->data[++(s->top)] = data;
			s->seq[s->top] = 1;
			for (int i = 0; i < s->top; i++)
				s->seq[i]++;
		}
	}
	else if (s->top==3) {   // 캐시 메모리가 다 채워져 있을 때
		int index = 0;
		for (int i = 0; i < MAX_STACK_SIZE; i++) { //hit 인지 ?
			if (s->data[i] == data) {
				if (s->seq[i] != 1) { //hit한 것의 시간이 1이면 나머지에 1을 더해줄 필요가 없이 그대로 가면된다
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
		if (hit==0) { //hit가 안되면 새로 추가해준다
			index = Max(s); // 가장 오래된 데이터 인덱스 받아옴(들어온 값이 캐시에 없을때)
			s->data[index] = data; //가장 오래된 데이터를 바꿔줌
			s->seq[index] = 1; // 1으로 다시 초기화
			for (int i = 0; i < MAX_STACK_SIZE; i++) {
				if (index == i)
					continue;
				else
					s->seq[i]++;
			}
		}
	}
	
	return hit; //hit가 됐으면 1,아니면 0을 반환
}

void readfile(StackType*s) {
	int cnt = 0,hit=0,block=0;
	FILE *fp;
	fp = fopen("c:\\input.txt", "r"); //파일 입출력
	int buffer;
	if (fp == NULL) {
		printf("실패");
		exit(1);
	}
	while (fscanf(fp, "%d", &buffer) != EOF) { //buffer가 끝날 때 까지 또는 30번 입력될 때 까지(과제의 입력조건)
		if (buffer == 99 || block++ >= 30) //99가 입력되거나 30개 보다 많은 블록이 입력되면 break
			break;
		hit += push( s, buffer); //hit된 수만큼 누적하여 더해준다.
		cnt++;  //총 몇개의 주기억장치 블록이 입력되었는지
	}
	ShowCache(s);
	printf("-----------------------\n");
	printf("적중률 : %d / %d\n", hit, cnt);
	printf("-----------------------\n");
	fclose(fp);
}

int main() {
	StackType s;
	init_stack(&s);
	readfile(&s);
	system("pause");
}