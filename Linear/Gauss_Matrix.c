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
		printf("범위는 2~10! 재입력하셔야합니다\n");
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

void Input(double **matrix, int size) //입력

{
	printf("input Elements:\n");
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size + 1; j++)
			scanf("%lf", &matrix[i][j]);

}

void swap(double **matrix, int size, int num1, int num2)
{
	for (int i = 0; i < size + 1; i++) //행을 바꿔준다
	{
		double temp = matrix[num1][i];
		matrix[num1][i] = matrix[num2][i];
		matrix[num2][i] = temp;
	}

}

void print(double **matrix, int size) //출력
{
	printf("output result: \n");

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size + 1; j++)
			printf("%.6f ", matrix[i][j]);
		printf("\n");
	}
}

void gauss_jordan(double **matrix, int size) //가우스 조던 소거법
{
	for (int i = 0; i < size - 1; i++)
	{
		if (!matrix[i][i]) //R(i)의 i번째 계수가 0일 경우 행을 바꿔줘야합니다
		{
			for (int j = i + 1; j < size; j++)
			{
				if (matrix[j][i])
				{
					swap(matrix, size, i, j); //행을 바꾸고
					break;
				}
			}
			i--; //swap만 했으므로 실질적으로 작동을 한 것은 아니다.
		}
		else //R(i)의 첫번째 계수가 0이 아닐 경우
		{
			double divide = matrix[i][i]; //연산을 하면서 i번째 계수가 바뀌므로 미리 저장해놓아야합니다
			for (int j = 0; j < size + 1; j++)
			{
				matrix[i][j] *= (1 / divide); //i번째 행에 R(i)의 i번째 계수의 역수를 곱합니다
			}
			for (int j = i + 1; j < size; j++)
			{
				double multiply = matrix[j][i]; //마찬가지로 matrix[j][i]도 연산을 하면서 값이 바뀌므로 미리 저장해놓아야합니다
			 //multiply가 필요한 이유: i번째 계수를 1로 만들기 위해
				for (int k = 0; k < size + 1; k++)
				{
					matrix[j][k] -= (matrix[i][k] * multiply); //R(i)번째 행과 R(j)번째 행을 더합니다
				}
			}
		}
	}
	double temp = matrix[size - 1][size - 1]; //마지막 행의 i번째 계수를 저장해놓습니다.
	for (int i = 0; i < size + 1; i++)
		matrix[size - 1][i] *= (1 / temp); //마지막 행에 i번째 계수의 역수만큼 곱합니다
  //여기까지가 가우스 소거법

 //여기서부터 가우스 조던 소거법

	for (int i = size - 1; i > 0; i--) //거꾸로
	{
		for (int j = i - 1; j >= 0; j--)
		{
			double multiply = matrix[j][i]; //연산하면서 바뀌는 값이니 미리 저장
			for (int k = i; k < size + 1; k++)
				matrix[j][k] -= (matrix[i][k] * multiply);
		}
	}

}
*/