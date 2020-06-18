#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INFINITY 1000000

// makeMatrix: ����� ���� �������ִ� �Լ�
int** makeMatrix(int r, int c) {
	int** matrix = (int**)malloc(sizeof(int*) * r);
	for (int i = 0; i < r; i++)
		matrix[i] = (int*)malloc(sizeof(int) * c);

	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			matrix[i][j] = 0;	// ���̺��� ��� 0���� ä����

	return matrix;
}

// printMatrix: ����� ����ϴ� �Լ�
void printMatrix(int** matrix, int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

// multMatrix: ��İ��� �����ϴ� �Լ�
int** multMatrix(int** mat1, int** mat2, int p1, int p2, int p3)
{
	int** newMat = makeMatrix(p1, p3);
	for (int r = 0; r < p1; r++){
		for (int c = 0; c < p3; c++){
			int sum = 0;
			for (int k = 0; k < p2; k++)
				sum += (mat1[r][k] * mat2[k][c]);
			newMat[r][c] = sum;
		}
	}
	return newMat;
}

// MatrixChainOrder
void MatrixChainOrder(int p[], int size, int*** matrixes) {	
	int n = size-1;
	int** m = makeMatrix(n+1, n+1);	// min cost�� ������ ���̺� m
	int** s = makeMatrix(n+1, n+1); // chain�� ������ ������ ���̺� s

	for (int i = 1; i <= n; i++)	// ���̺� m�� [n][n]�� ���� ��� 0���� ����
		m[i][i] = 0;	

	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			m[i][j] = INFINITY;
			for (int k = i; k <= j - 1; k++) {
				int q = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]);
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	int mc = m[1][n];	// minimum number of computation
	int oc = s[1][n];	// optimal chain order

	printf("Mininum number of computation: %d\n", mc);
	printMatrix(m, n + 1, n + 1);
	printf("\nOptimal chain order: %d\n", oc);
	printMatrix(s, n+1, n+1);

	int** interim = multMatrix(matrixes[oc], matrixes[oc+1], p[oc], p[oc+1], p[oc+2]);
	int** result = multMatrix(matrixes[oc-1], interim, p[oc-1], p[oc], p[oc+2]);

	printf("\n>> Rusult\n");
	printf("=========================\n");
	printMatrix(result, p[0], p[n]);
	printf("=========================\n");
}

int main() {

	int p[4] = { 5, 3, 7, 10 };		// ����� ��� ���� ����� p0 ~ p3 ������ ���� ���� 
	int** matrixes[3];				// 3���� ��� ����
	for (int i = 0; i < 3; i++) {
		matrixes[i] = makeMatrix(p[i], p[i + 1]);

		srand(time(NULL));
		for (int k = 0; k < p[i]; k++)
			for (int j = 0; j < p[i + 1]; j++)
				matrixes[i][k][j] = (rand() % 5) + 1;	// 1 ~ 5 ������ ������ ���� �Է�
		printMatrix(matrixes[i], p[i], p[i + 1]);		// ������� ��ĵ��� ���
		printf("\n");
	}

	MatrixChainOrder(p, sizeof(p) / sizeof(int), matrixes);	// Matrix chain order�� ���� ��İ��� ������� ���
}