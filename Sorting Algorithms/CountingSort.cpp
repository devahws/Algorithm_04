#include <stdio.h>
#include <stdlib.h>
void printArray(int array[], int n);

void countingSort(int array[], int n)
{	
	int max = 0;
	int* B = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		if (array[i] > max)
			max = array[i];

	int* C = (int*)malloc(sizeof(int) * (max+1));
	for (int i = 0; i <= max; i++)
		C[i] = 0;

	for (int i = 0; i < n; i++)
		C[array[i]]++;

	for (int i = 1; i <= max; i++) {
		C[i] += C[i - 1];
	}

	for (int i = n-1; i >= 0; i--) {
		B[C[array[i]]-1] = array[i];
		C[array[i]]--;
	}
	for (int i = 0; i < n; i++) {
		array[i] = B[i];
	}
}

void printArray(int array[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main()
{
	int array[] = { 392, 457, 657, 839, 436, 720, 355 };
	int n = sizeof(array) / sizeof(array[0]);

	printArray(array, n);
	countingSort(array, n);
	printArray(array, n);
}