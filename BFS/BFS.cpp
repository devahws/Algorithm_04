#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"
#define MAX_VERTICES 50

typedef struct node {
	int num;			// number of vertex
	char name;			// name of vertext
	struct node* link;	// adj list
}Node;

typedef struct Graph {
	Node* vertex[MAX_VERTICES];	// store initiated vertexes
	int n;						// number of initiated vertexes
	bool visited[MAX_VERTICES];	// check if vertex[i] is visited during BFS
	int dist[MAX_VERTICES];		// store distance from source vertex
	char phi[MAX_VERTICES];		// store parent of vertex
}Graph;

Node* initNode() {		// initiate Node func
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->link = NULL;
	return tmp;
}

Graph* initGraph() {	// initiate Graph func
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->vertex[i] = NULL;	// set vertex array to NULL
		g->visited[i] = false;
	}
	return g;
}

void insert_vertex(Graph* g, int n, char name) {	// insert vertex into graph
	if ((g->n) + 1 > MAX_VERTICES) {	// when vertext array is full
		fprintf(stderr, "graph capacity is full");
		return;
	}
	g->vertex[n] = initNode();
	g->vertex[n]->num = n;
	g->vertex[n]->name = name;
	g->n++;	// increase number of vertexes
}

void insert_edge(Graph* g, int start, int end) {	// add edge between vertexes
	if (g->vertex[start] == NULL || g->vertex[end] == NULL) {
		fprintf(stderr, "vertest number error");
		return;
	}
	Node* tmp1 = g->vertex[start];
	while (tmp1->link != NULL)
		tmp1 = tmp1->link;
	Node* newNode1 = initNode();
	newNode1->num = end;		// link V(end) with V(start)
	newNode1->name = g->vertex[end]->name;
	tmp1->link = newNode1;

	Node* tmp2 = g->vertex[end];
	while (tmp2->link != NULL)
		tmp2 = tmp2->link;
	Node* newNode2 = initNode();
	newNode2->num = start;		// link V(start) with V(end)
	newNode2->name = g->vertex[start]->name;
	tmp2->link = newNode2;
}

void bfs(Graph* g, int v) {	// BFS func
	Queue* newQueue = initQ();
	Node* tmp;
	int num;
	char name;
	int d = 0; // distance from source vertex
	g->visited[v] = true;
	g->dist[v] = 0;
	g->phi[v] = '-';
	enqueue(newQueue, v);
	
	while (!isEmpty(newQueue)) {	// stop before queue is empty state

		tmp = g->vertex[dequeue(newQueue)];	
		num = tmp->num;		// number of vertex which index is dequeued
		name = tmp->name;	// name of vertex which index is dequeued
		printf("V(%c) -> ", name);

		// enqueue all node that adjacent to vertex tmp
		while (tmp != NULL) {
			if (g->visited[tmp->num] == false) {	
				enqueue(newQueue, tmp->num);	
				g->phi[tmp->num] = name;				// setting parents node
				g->dist[tmp->num] = g->dist[num] + 1;	// store distance from source node
				g->visited[tmp->num] = true;			// check this vertex is visited
			}
			tmp = tmp->link;	// change tmp to another adjacent vertex from tmp
		}
	}
	printf("\n");
}

void printDistPhi(Graph* g) {	// print dist from source and parent of vertex
	printf("\nV  d  phi\n=========\n");
	for (int i = 0; i < g->n; i++) {
		printf("%c  %d   %c\n", g->vertex[i]->name, g->dist[i], g->phi[i]);
	}
}

int main() {
	Graph* g = initGraph();			// initiate graph
	char vertexes[] = { 'r', 's', 't', 'u', 'v', 'w', 'x', 'y' };
	for (int i = 0; i < 8; i++) {	// make 8 vetexes
		insert_vertex(g, i, vertexes[i]);
	}

	insert_edge(g, 0, 1);	// r-s
	insert_edge(g, 2, 3);	// t-u
	insert_edge(g, 0, 4);	// r-v
	insert_edge(g, 1, 5);	// s-w
	insert_edge(g, 2, 5);	// w-t
	insert_edge(g, 5, 6);	// w-x
	insert_edge(g, 2, 6);	// t-x
	insert_edge(g, 6, 3);	// x-u
	insert_edge(g, 3, 7);	// y-u
	insert_edge(g, 6, 7);	// x-y
	bfs(g, 1);	// src -> vertext(s)
	printDistPhi(g);
}