#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define SIZE1 10
#define SIZE2 100
#define SIZE3 1000

typedef int element;

// power function implementation
int power(int base, int expo) {
	int p = 1;
	for (int i = 0; i < expo; i++)
		p *= base;
	return p;
}

// countingSort implementation for using as stable algorithm in Radix sort
void countingSort(int array[], int n, int d)
{
	int* newArr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		newArr[i] = array[i] % power(10, d);
	}

	int max = 0;
	int* B = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		if (newArr[i] > max)
			max = newArr[i];

	int* C = (int*)malloc(sizeof(int) * (max + 1));
	for (int i = 0; i <= max; i++)
		C[i] = 0;

	for (int i = 0; i < n; i++)
		C[newArr[i]]++;

	for (int i = 1; i <= max; i++)
		C[i] += C[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		B[C[newArr[i]] - 1] = array[i];
		C[newArr[i]]--;
	}
	for (int i = 0; i < n; i++)
		array[i] = B[i];
}

// radixSort implementation
void radixSort(int array[], int n, int d) {
	for (int i = 1; i < d; i++) {	// counting sort by every digit
		countingSort(array, n, d);
	}
}

/* below functions are all same in other files */

void printArray(element* array, int size) {
	if (size == SIZE1) {
		for (int i = 0; i < size; i++)
			printf("%02d ", array[i]);
		printf("\n");
	}
	else if(size==SIZE2){
		for (int i = 0; i < size; i++)
			printf("%03d ", array[i]);
		printf("\n");
	}
}

element* makeArray(int SIZE) {
	element* newArr = (element*)malloc(sizeof(element) * SIZE);
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		newArr[i] = (rand() % SIZE) + 1; // make random number between 1~SIZE
	}
	return newArr;
}

void SortProcess(int SIZE) {
	LARGE_INTEGER Frequency;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;
	int* array1 = makeArray(SIZE);
	printArray(array1, SIZE);
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BeginTime);
	radixSort(array1, SIZE, 10);
	QueryPerformanceCounter(&Endtime);
	int elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	printArray(array1, SIZE);
	printf("Duration time : %.30f\n\n", duringtime);
}

int main()
{
	printf("RadixSort\n");
	printf("Input size 10\n");
	SortProcess(SIZE1);	// SIZE 10
	printf("Input size 100\n");
	SortProcess(SIZE2); // SIZE 100
	printf("Input size 1000\n");
	SortProcess(SIZE3);	// SIZE 1000
}