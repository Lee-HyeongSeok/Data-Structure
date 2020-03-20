#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print(short *list, int size);
void TruthValueSetting(short *list, int n, int size);

void TruthValueSetting(short *list, int n, int size) {
	if (n == 0)
		print(list, size);
	else {
		TruthValueSetting(list, n - 1, size);
		list[n - 1] = 1;
		TruthValueSetting(list, n - 1, size);
		list[n - 1] = 0;
	}
}

void print(short *list, int size) {
	int i = size - 1;

	for (; i >= 0; i--) {
		if (list[i] == 0)
			printf("Flase");
		else
			printf("True");
	}
	printf("\n");
}
int main() {
	int n = 0;

	short *list;

	printf("input number\n");
	scanf("%d", &n);

	list = (short*)malloc(sizeof(short)*n);

	for (int i = 0; i < n; i++) {
		list[i] = 0;
	}
	TruthValueSetting(list, n, n);
	return 0;
}

