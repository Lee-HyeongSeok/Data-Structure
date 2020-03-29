#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	int count;
	int n;
}cache;

int main()
{
	int i, j, k, max, count = 0, hitcount = 0;
	FILE *f;
	int mblo[30];   // 주기억장치 블럭 갯수
	cache c[4] = { { 0,-1 },{ 0,-1 },{ 0,-1 },{ 0,-1 } };  //캐시블럭이 4개
	f = fopen("input.txt", "r");    // input 파일 불러오기
	if (f == NULL)
	{
		printf("실패");
		return 1;
	}
	for (i = 0; i < 30; i++)  // mblo 블럭의 갯수가 30개이하
	{
		fscanf(f, "%d", &mblo[i]);
		if (mblo[i] == 99)   // mblo 블럭의 값이 99면 읽어 오는 것 종료 
			break;
		count++;
	}
	for (i = 0; i < count; i++)
	{
		for (k = 0; k < 4; k++)
			c[k].count++;
		for (j = 0; j < 4; j++)
		{
			if (c[j].n == mblo[i])  // 주기억장치에서 불러온 값과 캐시의 값이 같은지  
			{						// 비교 후 히트 값 증가
				c[j].count = 0;
				hitcount++;
				break;
			}
			if (c[j].n == -1)      // 처음에 캐시의 빈공간을 채우기위한 조건함수
			{
				c[j].n = mblo[i];
				c[j].count = 0;
				break;

			}
			if (j == 3 && c[j].n != mblo[i]) //모든캐시블럭이 위의 두조건에 걸리지않았을 떄
			{
				max = c[0].count;
				for (k = 0; k < 4; k++) {
					if (max <= c[k].count)
						max = c[k].count;
				}
				for (k = 0; k < 4; k++) {    // 가장 큰 캐시블록을 찾기 위한 for문
					if (max == c[k].count) {
						c[k].count = 0;
						c[k].n = mblo[i];
						break;
					}

				}
			}
		}
	}
	printf("캐시블록 : (주기억장치 블록번호)\n");   //여기서부터는 출력문
	for (i = 0; i < 4; i++) printf("%d : [%d]\n", i, c[i].n);
	printf("적중률: %d/%d, %.2f", hitcount, count, ((double)hitcount / (double)count));
	fclose(f);
	getch();
	return 0;
}