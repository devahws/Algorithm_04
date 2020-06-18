#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 16		// total capacity of kanpsack

typedef struct item {
	int N;			// item number
	int W;			// weight
	int V;			// value
	int VperW;		// value per weight
	bool put;		// if this item is put in knapsack 
	bool fraction;	// if this item splited
}Item;
typedef Item element;

// merge sort implementation
void merge(element arr[], int start, int mid, int end) {
	int i = start; int j = mid + 1;
	int k = start;
	element* newArr = (element*)malloc(sizeof(element) * (start + end + 1));
	while (i <= mid && j <= end) {
		if (arr[i].VperW > arr[j].VperW)
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

void mergesort(element arr[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;	// setting mid index
		mergesort(arr, start, mid);		// and resursion each part of origin array
		mergesort(arr, mid + 1, end);
		merge(arr, start, mid, end);	// finally merge the each sorted array
	}
}

// knapsack problem solving
int main() {
	int W[6] = { 6, 10, 3, 5, 1, 4 };		// weight of item
	int V[6] = { 60, 20, 12, 80, 30, 60 };	// value of item
	int VpW[6];		// value per weight
	for (int i = 0; i < 6; i++)
		VpW[i] = V[i] / W[i];

	Item* items = (Item*)malloc(sizeof(Item) * 6);
	// items 설정
	for (int i = 0; i < 6; i++) {
		items[i].N = i+1;
		items[i].W = W[i];
		items[i].V = V[i];
		items[i].VperW = V[i] / W[i];
		items[i].put = false;
		items[i].fraction = false;
	}

	// items를 무게당 가치(VperW)을 기준으로 내림차순 정렬 -> Decreasing order
	mergesort(items, 0, 5);

	int w = CAPACITY; // 가방의 용량
	int totalV = 0;	  // total Value
	int i = 0;
	while (w > 0) {
		if (items[i].W <= w) {	// 한 개 아이템이 fraction 없이 가방에 온전히 들어갈 수 있으면
			totalV += items[i].V;
			items[i].put = true;
			w -= items[i++].W;
			
		}
		else {	// item을 쪼개서 가방에 넣어야 할 때
			totalV += items[i].VperW * w;
			items[i].put = true;
			items[i].fraction = true;
			w = 0;
		}
	}
	printf("maximum value: %d \n", totalV);
	printf("Item number in the bag\n=======\n");
	for (int i = 0; i < 6; i++)
		if (items[i].put == true) {
			printf("Item %d | Weight: %d Value: %d", items[i].N, items[i].W, items[i].V);
			if (items[i].fraction)
				printf(" Fraction");
			printf("\n");
		}
}