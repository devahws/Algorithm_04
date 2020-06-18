#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 100	// 테이블의 크기를 100으로 설정

int DArray[ARR_SIZE];	// 전역 변수로 테이블 선언

void initArr() {		// 배열을 초기화하는 함수
	for (int i = 0; i < ARR_SIZE; i++)
		DArray[i] = NULL;
	DArray[0] = 1;	// 피보나치 수열의 첫 번째 항
	DArray[1] = 1;	// 피보나치 수열의 두 번째 항
}

int fibo(int find) {	// 피보나치 수열을 계산하는 함수
	int num = find - 1;	// 0부터 시작하는 배열의 인덱스를 고려하여 입력받는 숫자에서 -1
	if (num == 0 || num == 1)	// 첫 번째 혹은 두 번째 피보나치 수열은 이미 저장된 값을 리턴
		return DArray[num];
	else {						// 세 번째 수열부터는 연산을 통해 리턴
		DArray[num] = fibo(find - 2) + fibo(find - 1);
		return DArray[num];
	}
}

int main() {
	initArr();
	printf("Fibonacci(5): %d\n", fibo(5));	// input: 5
	printf("Fibonacci(10): %d", fibo(10));	// input: 10
}