#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define SIZE1 10
#define SIZE2 100
#define SIZE3 1000

typedef int element;

// implementation partition with pivot
int partition(element arr[], int start, int end) {
	element x = arr[start]; // setting pivot as first member of array
	int i = start;

	for (int j = start + 1; j <= end; j++) {
		if (arr[j] <= x) {
			i++;
			element tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
		}
	}
	element tmp = arr[start];
	arr[start] = arr[i];
	arr[i] = tmp;
	return i;
}

// quick sort implementation
void quicksort(element arr[], int start, int end) {
	if (start < end) {
		int mid = partition(arr, start, end);	// setting mid index
		quicksort(arr, start, mid - 1);			// and recursion each part of original array
		quicksort(arr, mid + 1, end);
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
	quicksort(array1, 0, SIZE-1);
	QueryPerformanceCounter(&Endtime);
	int elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	printArray(array1, SIZE);
	printf("Duration time : %.30f\n\n", duringtime);
}


int main()
{
	printf("QuickSort\n");
	printf("Input size 10\n");
	SortProcess(SIZE1);	// SIZE 10
	printf("Input size 100\n");
	SortProcess(SIZE2); // SIZE 100
	printf("Input size 1000\n");
	SortProcess(SIZE3);	// SIZE 1000
}