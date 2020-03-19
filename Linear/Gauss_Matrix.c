/*#include <stdio.h>

#include <stdlib.h>



void Input(double **matrix, int size);
void swap(double **matrix, int size, int num1, int num2);
void print(double **matrix, int size);
void gauss_jordan(double **matrix, int size);



int main(void)

{

	int size;
	double **matrix;
	double **identity_matrix;
	printf("Matrix size: ");
	scanf("%d", &size);

	if (!(size >= 2 && size <= 10))
	{
		printf("������ 2~10! ���Է��ϼž��մϴ�\n");
		printf("Matrix size: ");
		scanf("%d", &size);
	}

	matrix = (double**)malloc(sizeof(double*)*size);
	identity_matrix = (double**)malloc(sizeof(double*)*size);

	for (int i = 0; i < size; i++)
		matrix[i] = (double*)malloc(sizeof(double)*(size + 1));

	Input(matrix, size);
	printf("\n");
	gauss_jordan(matrix, size);
	print(matrix, size);
	for (int i = 0; i < size; i++)
		free(matrix[i]);
	free(matrix);
    return 0;

}

void Input(double **matrix, int size) //�Է�

{
	printf("input Elements:\n");
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size + 1; j++)
			scanf("%lf", &matrix[i][j]);

}

void swap(double **matrix, int size, int num1, int num2)
{
	for (int i = 0; i < size + 1; i++) //���� �ٲ��ش�
	{
		double temp = matrix[num1][i];
		matrix[num1][i] = matrix[num2][i];
		matrix[num2][i] = temp;
	}

}

void print(double **matrix, int size) //���
{
	printf("output result: \n");

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
			printf("%.6f ", matrix[i][j]);
		printf("\n");
	}
}

void gauss_jordan(double **matrix, int size) //���콺 ���� �ҰŹ�
{
	for (int i = 0; i < size - 1; i++)
	{
		if (!matrix[i][i]) //R(i)�� i��° ����� 0�� ��� ���� �ٲ�����մϴ�
		{
			for (int j = i + 1; j < size; j++)
			{
				if (matrix[j][i])
				{
					swap(matrix, size, i, j); //���� �ٲٰ�
					break;
				}
			}
			i--; //swap�� �����Ƿ� ���������� �۵��� �� ���� �ƴϴ�.
		}
		else //R(i)�� ù��° ����� 0�� �ƴ� ���
		{
			double divide = matrix[i][i]; //������ �ϸ鼭 i��° ����� �ٲ�Ƿ� �̸� �����س��ƾ��մϴ�
			for (int j = 0; j < size + 1; j++)
			{
				matrix[i][j] *= (1 / divide); //i��° �࿡ R(i)�� i��° ����� ������ ���մϴ�
			}
			for (int j = i + 1; j < size; j++)
			{
				double multiply = matrix[j][i]; //���������� matrix[j][i]�� ������ �ϸ鼭 ���� �ٲ�Ƿ� �̸� �����س��ƾ��մϴ�
			 //multiply�� �ʿ��� ����: i��° ����� 1�� ����� ����
				for (int k = 0; k < size + 1; k++)
				{
					matrix[j][k] -= (matrix[i][k] * multiply); //R(i)��° ��� R(j)��° ���� ���մϴ�
				}
			}
		}
	}
	double temp = matrix[size - 1][size - 1]; //������ ���� i��° ����� �����س����ϴ�.
	for (int i = 0; i < size + 1; i++)
		matrix[size - 1][i] *= (1 / temp); //������ �࿡ i��° ����� ������ŭ ���մϴ�
  //��������� ���콺 �ҰŹ�

 //���⼭���� ���콺 ���� �ҰŹ�

	for (int i = size - 1; i > 0; i--) //�Ųٷ�
	{
		for (int j = i - 1; j >= 0; j--)
		{
			double multiply = matrix[j][i]; //�����ϸ鼭 �ٲ�� ���̴� �̸� ����
			for (int k = i; k < size + 1; k++)
				matrix[j][k] -= (matrix[i][k] * multiply);
		}
	}

}
*/