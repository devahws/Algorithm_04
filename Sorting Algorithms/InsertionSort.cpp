#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define SIZE1 10
#define SIZE2 100
#define SIZE3 1000
typedef int element;

// insertion sort implementation
void insertionSort(int arr[], int size) {
	int i, key, j;
	for (i = 1; i < size; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

/* below functions are all same in other files */

void printArray(element* array, int size) {
	if (size != SIZE3) {
		for (int i = 0; i < size; i++)
			printf("%d ", array[i]);
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
	insertionSort(array1, SIZE);
	QueryPerformanceCounter(&Endtime);
	int elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	printArray(array1, SIZE);
	printf("Duration time : %.30f\n\n", duringtime);
}

int main()
{
	printf("InsertionSort\n");
	printf("Input size 10\n");
	SortProcess(SIZE1);	// SIZE 10
	printf("Input size 100\n");
	SortProcess(SIZE2); // SIZE 100
	printf("Input size 1000\n");
	SortProcess(SIZE3);	// SIZE 1000
}