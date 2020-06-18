#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#define SIZE1 10
#define SIZE2 100
#define SIZE3 1000
typedef int element;

// type struct bucket for making flexible 2-dimension array in C
typedef struct bucket {
	element *data;
	int pos;
}Bucket;

// using insertionSort as stable algorithm
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

// BucketSort Implementation
void BucketSort(int* array, int size, int bucketNum, int bucketSize) {
	Bucket* buckets = (Bucket*)malloc(sizeof(Bucket) * bucketNum);	// make struct type bucket 
	for (int i = 0; i < bucketNum; i++) {
		buckets[i].data = (int*)malloc(sizeof(int) * bucketSize);
		buckets[i].pos = 0;
	}
	for (int i = 0; i < size; i++) {
		if (buckets[array[i] / bucketSize].pos == bucketSize) {	// reallocating buckets[i] when it has no space for saving
			buckets[array[i] / bucketSize].data = (int*)realloc(buckets[array[i] / bucketSize].data, buckets[array[i] / bucketSize].pos * 2 * sizeof(int));
		}
		buckets[array[i] / bucketSize].data[buckets[array[i] / bucketSize].pos++] = array[i];
	}
	for (int i = 0; i < bucketNum; i++) {	// sorting every bucket with insertion sort
		insertionSort(buckets[i].data, buckets[i].pos);
	}
	int pos = 0;
	for (int i = 0; i < bucketNum; i++) {	// concatenate every bucket to original array
		for (int j = 0; j < buckets[i].pos; j++)
			array[pos++] = buckets[i].data[j];
	}
}

/* below functions are all same in other files */

void printArray(element* array, int size) {
	if (size == SIZE1) {
		for (int i = 0; i < size; i++)
			printf("%d ", array[i]);
		printf("\n");
	}
	else if (size == SIZE2) {
		for (int i = 0; i < size; i++)
			printf("%02d ", array[i]);
		printf("\n");
	}
}

element* makeArray(int SIZE) {
	element* newArr = (element*)malloc(sizeof(element) * SIZE);
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		newArr[i] = (rand() % SIZE)+1; // make random number between 1~SIZE
	}
	return newArr;
}

void SortProcess(int SIZE, int bucketNum, int bucketSize) {
	LARGE_INTEGER Frequency;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;
	QueryPerformanceFrequency(&Frequency);
	int* array1 = makeArray(SIZE);
	printArray(array1, SIZE);
	QueryPerformanceCounter(&BeginTime);
	BucketSort(array1, SIZE, bucketNum, bucketSize);
	QueryPerformanceCounter(&Endtime);
	int elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	printArray(array1, SIZE);
	printf("Duration time : %.30f\n\n", duringtime);
}

int main()
{
	// setting total buckets sizes as double size of original array
	printf("BucketSort\n");
	printf("Input size 10\n");
	SortProcess(SIZE1, 5, 4);	// SIZE: 10 // Total bucket numbers : 20
	printf("Input size 100\n");
	SortProcess(SIZE2, 10, 20);	// SIZE: 100 // Total bucket numbers : 200
	printf("Input size 1000\n");
	SortProcess(SIZE3, 20, 100); // SIZE: 1000 // Total bucket numbers : 2000
}