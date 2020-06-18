#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// setting input size
#define SIZE1 10	
#define SIZE2 100
#define SIZE3 1000

typedef int element;

// bubble sort implementation
void bubbleSort(element* array, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size - i; j++) {
			if (array[j] > array[j + 1]) {
				element tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}

/* below functions are all same in other files */

// print function
void printArray(element* array, int size) {
	if (size != SIZE3) {
		for (int i = 0; i < size; i++)
			printf("%d ", array[i]);
		printf("\n");
	}
}

// make array function
element* makeArray(int SIZE) {
	element* newArr = (element*)malloc(sizeof(element)*SIZE);
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		newArr[i] = (rand() % SIZE)+1; // make random number between 1~SIZE
	}
	return newArr;
}

// process fuction 
void SortProcess(int SIZE) {
	LARGE_INTEGER Frequency;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER Endtime;
	QueryPerformanceFrequency(&Frequency);
	int* array1 = makeArray(SIZE);
	printArray(array1, SIZE);
	QueryPerformanceCounter(&BeginTime);
	bubbleSort(array1, SIZE);
	QueryPerformanceCounter(&Endtime);
	int elapsed = Endtime.QuadPart - BeginTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;
	printArray(array1, SIZE);
	printf("Duration time : %.30f\n\n", duringtime);
}

int main()
{
	printf("BubbleSort\n");
	printf("Input size 10\n");
	SortProcess(SIZE1);	// SIZE 10
	printf("Input size 100\n");
	SortProcess(SIZE2); // SIZE 100
	printf("Input size 1000\n");
	SortProcess(SIZE3);	// SIZE 1000
}