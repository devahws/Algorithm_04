#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 100	// ���̺��� ũ�⸦ 100���� ����

int DArray[ARR_SIZE];	// ���� ������ ���̺� ����

void initArr() {		// �迭�� �ʱ�ȭ�ϴ� �Լ�
	for (int i = 0; i < ARR_SIZE; i++)
		DArray[i] = NULL;
	DArray[0] = 1;	// �Ǻ���ġ ������ ù ��° ��
	DArray[1] = 1;	// �Ǻ���ġ ������ �� ��° ��
}

int fibo(int find) {	// �Ǻ���ġ ������ ����ϴ� �Լ�
	int num = find - 1;	// 0���� �����ϴ� �迭�� �ε����� ����Ͽ� �Է¹޴� ���ڿ��� -1
	if (num == 0 || num == 1)	// ù ��° Ȥ�� �� ��° �Ǻ���ġ ������ �̹� ����� ���� ����
		return DArray[num];
	else {						// �� ��° �������ʹ� ������ ���� ����
		DArray[num] = fibo(find - 2) + fibo(find - 1);
		return DArray[num];
	}
}

int main() {
	initArr();
	printf("Fibonacci(5): %d\n", fibo(5));	// input: 5
	printf("Fibonacci(10): %d", fibo(10));	// input: 10
}