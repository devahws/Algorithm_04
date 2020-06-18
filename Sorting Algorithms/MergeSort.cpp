#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define SIZE1 10
#define SIZE2 100
#define SIZE3 1000

typedef int element;

// merge function implementation
void merge(int arr[], int start, int mid, int end) {
	int i = start; int j = mid + 1;
	int k = start;
	int* newArr = (int*)malloc(sizeof(int) * (start + end + 1));
	while (i <= mid && j <= end) {
		if (arr[i] <= arr[j])
			newArr[k++] = arr[i++];
		else
			newArr[k++] = arr[j++];
	}
	while (i <= mid)
		newArr[k++] = arr[i++];
	while (j <= end)
		newArr[k++] = arr[j++];
	for (int i = start; i <= end; i++)
		arr[i] = newArr[i];
}

// merge sort implementation
void mergesort(int arr[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;	// setting mid index
		mergesort(arr, start, mid);		// and resursion each part of origin array
		mergesort(arr, mid + 1, end);
		merge(arr, start, mid, end);	// finally merge the each sorted array
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
	mergesort(array1, 0, SIZE - 1);
	QueryPerformanceCounter(&Endtime);
	int elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	printArray(array1, SIZE);
	printf("Duration time : %.30f\n\n", duringtime);
}



int main()
{
	printf("MergetSort\n");
	printf("Input size 10\n");
	SortProcess(SIZE1);	// SIZE 10
	printf("Input size 100\n");
	SortProcess(SIZE2); // SIZE 100
	printf("Input size 1000\n");
	SortProcess(SIZE3);	// SIZE 1000
}