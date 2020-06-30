#include <stdio.h>
#include <stdlib.h>

int** makeMatrix(int r, int c) {	// make int type matrix func
	int** matrix = (int**)malloc(sizeof(int*) * r);
	for (int i = 0; i < r; i++)
		matrix[i] = (int*)malloc(sizeof(int) * c);

	return matrix;
}

char** makeCMatrix(int r, int c) {	// make char type matrix func
	char** matrix = (char**)malloc(sizeof(char*) * r);
	for (int i = 0; i < r; i++)
		matrix[i] = (char*)malloc(sizeof(char) * c);

	return matrix;
}

void printMatrix(int** matrix, int r, int c) {	// print matrix func
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

void printCMatrix(char** matrix, int r, int c) {	// print char type matrix func
	for (int i = 1; i < r; i++) {
		for (int j = 1; j < c; j++)
			printf("%c ", matrix[i][j]);
		printf("\n");
	}
}

void printLCS(char** b, char* X, int i, int j) {	// print LCS func
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 'a') {
		printLCS(b, X, i - 1, j - 1);
		printf("%c ", X[i]);
	}
	else if (b[i][j] == 'u')
		printLCS(b, X, i - 1, j);
	else
		printLCS(b, X, i, j - 1);
}

void LCS(char* X, char* Y, int sizeX, int sizeY) {	// LCS func
	int m = sizeX;	// size of array X
	int n = sizeY;	// size of array Y
	char** b = makeCMatrix(m+1, n+1);
	int** c = makeMatrix(m+1, n+1);

	for (int i = 1; i < m + 1; i++)
		c[i][0] = 0;
	for (int j = 0; j < n + 1; j++)
		c[0][j] = 0;

	for (int i = 1; i < m + 1; i++)
		for (int j = 1; j < n + 1; j++)
			if (X[i] == Y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 'a';
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 'u';
			}
			else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 's';
			}

	printCMatrix(b, m + 1, n + 1);
	printf("\n");
	printLCS(b, X, m, n);
}



int main() {
	printf("u: ¡è / a: ¢Ø / s: ¡ç\n\n");
	char X[9] = "0ABCBDAB";
	char Y[8] = "0BDCABA";
	LCS(X, Y, 8, 7);
}