#pragma once
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void error(const char* message) {
	fprintf(stderr, "%s\n", message);
}

typedef int element;
typedef struct queue {
	int data[SIZE];
	int front;
	int rear;
} Queue;

Queue* initQ() {
	Queue* newQ = (Queue*)malloc(sizeof(Queue));
	newQ->front = 0;
	newQ->rear = 0;

	return newQ;
}

bool isEmpty(Queue* queue) {
	if (queue->front == queue->rear)
		return 1;
	else
		return 0;
}

bool isFull(Queue* queue) {
	if ((queue->rear + 1) % SIZE == queue->front)
		return true;
	else
		return false;
}

void enqueue(Queue* queue, element data) {
	if (isFull(queue))
		error("Queue is full");
	else {
		queue->data[queue->rear] = data;
		queue->rear = (queue->rear + 1) % SIZE;
	}
}

element dequeue(Queue* queue) {
	if (isEmpty(queue))
		error("Queue is empty");
	else {
		element rdata = queue->data[queue->front];
		queue->front = (queue->front + 1) % SIZE;
		return rdata;
	}
}
