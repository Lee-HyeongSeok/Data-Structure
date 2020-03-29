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
	int mblo[30];   // �ֱ����ġ �� ����
	cache c[4] = { { 0,-1 },{ 0,-1 },{ 0,-1 },{ 0,-1 } };  //ĳ�ú��� 4��
	f = fopen("input.txt", "r");    // input ���� �ҷ�����
	if (f == NULL)
	{
		printf("����");
		return 1;
	}
	for (i = 0; i < 30; i++)  // mblo ���� ������ 30������
	{
		fscanf(f, "%d", &mblo[i]);
		if (mblo[i] == 99)   // mblo ���� ���� 99�� �о� ���� �� ���� 
			break;
		count++;
	}
	for (i = 0; i < count; i++)
	{
		for (k = 0; k < 4; k++)
			c[k].count++;
		for (j = 0; j < 4; j++)
		{
			if (c[j].n == mblo[i])  // �ֱ����ġ���� �ҷ��� ���� ĳ���� ���� ������  
			{						// �� �� ��Ʈ �� ����
				c[j].count = 0;
				hitcount++;
				break;
			}
			if (c[j].n == -1)      // ó���� ĳ���� ������� ä������� �����Լ�
			{
				c[j].n = mblo[i];
				c[j].count = 0;
				break;

			}
			if (j == 3 && c[j].n != mblo[i]) //���ĳ�ú��� ���� �����ǿ� �ɸ����ʾ��� ��
			{
				max = c[0].count;
				for (k = 0; k < 4; k++) {
					if (max <= c[k].count)
						max = c[k].count;
				}
				for (k = 0; k < 4; k++) {    // ���� ū ĳ�ú���� ã�� ���� for��
					if (max == c[k].count) {
						c[k].count = 0;
						c[k].n = mblo[i];
						break;
					}

				}
			}
		}
	}
	printf("ĳ�ú�� : (�ֱ����ġ ��Ϲ�ȣ)\n");   //���⼭���ʹ� ��¹�
	for (i = 0; i < 4; i++) printf("%d : [%d]\n", i, c[i].n);
	printf("���߷�: %d/%d, %.2f", hitcount, count, ((double)hitcount / (double)count));
	fclose(f);
	getch();
	return 0;
}