#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// �����Լ�
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}
// ��ũ�Լ�
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top];
}
// �������� �켱������ ��ȯ�Ѵ�.
int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
int change_val(char *num, int *index) {
	int value = 0;
	char temp[100];
	int i, k;
	for (i = 0; num[i] != ' '; i++) {
		temp[i] = num[i];
	}
	temp[i] = '\0';
	value = atoi(temp);
	k = *index;
	*index = k + i;
	return value;
}
// ���� ǥ�� ���� -> ���� ǥ�� ����
void infix_to_postfix(char *exp, char *postfix)
{
	StackType s;
	init(&s);

	while (*exp != '\0') {
		if (*exp == '(') {
			push(&s, *exp);
			exp++;
		}
		else if (*exp == ')') {
			while (peek(&s) != '(') {
				*postfix++ = pop(&s);
				*postfix++ = ' ';
			}
			pop(&s);
			exp++;
		}
		else if (*exp == '+' || *exp == '-' || *exp == '*' || *exp == '/') {
			while (!is_empty(&s) && (prec(*exp) <= prec(peek(&s)))) {
				*postfix++ = pop(&s);
				*postfix++ = ' ';
			}
			push(&s, *exp);
			exp++;
		}
		else if (*exp >= '0' && *exp <= '9') {
			do {
				*postfix++ = *exp++;
			} while ((*exp >= '0' && *exp <= '9'));
			*postfix++ = ' ';
		}
		else {
			exp++;
		}
	}
	while (!is_empty(&s)) {
		*postfix++ = pop(&s);
		*postfix++ = ' ';
	}
	postfix--;
	*postfix = '\0';
}
// ���� ǥ�� ���� ��� �Լ�
element eval(char *exp)
{
	int value, op1, op2;
	int i;
	
	StackType s;

	init(&s);
	for (i = 0; exp[i] != '\0'; i++) {
		if (exp[i] == ' ') {
			i++;
		}
		if (exp[i] >= '0' && exp[i] <= '9') {
			value = change_val(&exp[i], &i);
			push(&s, value);
		}
		else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'){
			op2 = pop(&s);
			op1 = pop(&s);
			switch (exp[i]) {
			case '+' : 
				push(&s, op1 + op2);
				break;
			case '-' :
				push(&s, op1 - op2);
				break;
			case '*' : 
				push(&s, op1 * op2);
				break;
			case '/' :
				push(&s, op1 / op2);
				break;
			}
		}
		
	}
	return pop(&s);
}
void Reset(char *str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		str[i] = 0;
	}
}


int main()
{
	char postfix[100];
	char changed_post[100];

	int result = 0;
	char ch;
	char ch_d = 'd';
	int cmp = 0;


	do {
		Reset(postfix);
		Reset(changed_post);
		system("cls");
		printf("������ �Է��ϼ��� : ");
		scanf("%s", postfix);

		printf("\n");
		infix_to_postfix(postfix, changed_post);
		printf("���� ǥ��� : %s \n", changed_post);

		result = eval(changed_post);
		printf("�� : %d \n", result);

		printf("clear function... press 'd' \n");
		printf("exit... press 'e' \n");
		ch = _getch();
		if(ch == 'e'){
			system("cls");
			printf("���α׷� ���� \n");
			exit(1);
		}
	} while (ch == ch_d);
	

}
