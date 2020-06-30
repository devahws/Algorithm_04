#include <stdio.h>
#include <stdlib.h>
#include "myqueue.h"
#define MAX_VERTICES 50
#define INFINITY 10000

typedef struct node {
	int num;			// number of vertex
	char name;			// name of vertex
	struct node* link;	// adjacent node
}Node;

typedef struct Graph {
	Node* vertex[MAX_VERTICES];	// store initiated vertexes
	int n;						// number of initiated vertexes
	int sn;						// number of vertexes contruct subset S
	bool visited[MAX_VERTICES];	// check if vertex[i] is visited during Dijkstra
	int dist[MAX_VERTICES];		// store distance from source vertex
	char phi[MAX_VERTICES];		// store parent of vertex
	int weight[MAX_VERTICES][MAX_VERTICES];
}Graph;

Node* initNode() {		// initiate Node func
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->link = NULL;
	return tmp;
}

Graph* initGraph() {	// initiate graph func
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->n = 0;
	g->sn = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->vertex[i] = NULL;	
		g->visited[i] = false;
	}

	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->weight[i][j] = 0;

	return g;
}

void initSingleSrc(Graph* g, int v) {	// init single source func
	for (int i = 0; i < g->n; i++) {
		g->dist[i] = INFINITY;
		g->phi[i] = 'N';
	}
	g->dist[v] = 0;
}

void relax(Graph* g, int u, int v) {	// relax func
	if (g->dist[v] > g->dist[u] + g->weight[u][v]) {
		g->dist[v] = g->dist[u] + g->weight[u][v];
		g->phi[v] = g->vertex[u]->name;
	}
}

void insert_vertex(Graph* g, int n, char name) {	// insert vertex to graph
	if ((g->n) + 1 > MAX_VERTICES) {	// when capacity of graph is full
		fprintf(stderr, "graph capacity is full");
		return;
	}
	g->vertex[n] = initNode();
	g->vertex[n]->num = n;
	g->vertex[n]->name = name;
	g->n++;	// increase number of vertex
}

void insert_edge(Graph* g, int start, int end, int w) {
	if (g->vertex[start] == NULL || g->vertex[end] == NULL) {
		fprintf(stderr, "vertest number error");
		return;
	}
	Node* tmp1 = g->vertex[start];
	while (tmp1->link != NULL)
		tmp1 = tmp1->link;
	Node* newNode1 = initNode();
	newNode1->num = end;		// connect vertex[start] with vertex[end]
	newNode1->name = g->vertex[end]->name;
	tmp1->link = newNode1;

	g->weight[start][end] = w;
}

// implementation partition with pivot
int partition(int arr[], int start, int end, Graph* g) {
	int x = g->dist[start]; // sort array by value of dist[i]
	int i = start;

	for (int j = start + 1; j <= end; j++) {
		if (g->dist[j] <= x) {
			i++;
			int tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
		}
	}
	int tmp = arr[start];
	arr[start] = arr[i];
	arr[i] = tmp;
	return i;
}

// quick sort implementation
void quicksort(int arr[], int start, int end, Graph* g) {
	if (start < end) {
		int mid = partition(arr, start, end, g);	// setting mid index
		quicksort(arr, start, mid - 1,g);			// and recursion each part of original array
		quicksort(arr, mid + 1, end, g);
	}
}

void sortQueue(Queue* q, Graph* g) {
	int size = g->n - g->sn;
	if (size == 0)
		return;
	int* tmpnums = (int*)malloc(sizeof(int) * (size));
	int index = 0;
	for (int i = 0; i < g->n; i++)
		if (g->visited[i] != true)	// when vertex is not in subset S
			tmpnums[index++] = i;
	quicksort(tmpnums, 0, size-1, g);
	for (int i = 0; i < size; i++)
		enqueue(q, tmpnums[i]);
}

void printPhi(Graph* g) {	// print parent of vertex
	printf("\nV  phi\n=========\n");
	for (int i = 0; i < g->n; i++) {
		printf("%c   %c\n", g->vertex[i]->name, g->phi[i]);
	}
}

void dijkstra(Graph* g, int v) {	// dijkstra algorithms
	initSingleSrc(g, v);
	int* S = (int*)malloc(sizeof(int) * g->n);
	int index = 0;
	char name;
	g->phi[v] = '-';
	Node* tmp;

	Queue* newQueue = initQ();
	sortQueue(newQueue, g);
	while (!isEmpty(newQueue)) {
		int u = dequeue(newQueue);
		S[index++] = u;
		tmp = g->vertex[u];
		g->visited[u] = true;
		g->sn++;
		name = tmp->name;
		while (tmp->link != NULL) {
			relax(g, u, tmp->link->num);
			tmp = tmp->link;
		}
		newQueue = initQ();
		sortQueue(newQueue, g);	// resort queue after relax
	}
	printf("s t y x z \n----------\n");
	for (int i = 0; i < g->n; i++)
		printf("%d ", g->dist[i]);

	printf("\n");
	printPhi(g);
	printf("\n");
	printf("#1 shortest path V(s) -> V(y): %c - y\n", g->phi[2]);
	printf("   total costs: %d\n", g->dist[2]);
	printf("#2 shortest path V(s) -> V(z): %c - %c - z\n", g->phi[2], g->phi[4]);
	printf("   total costs: %d\n", g->dist[4]);
}

void printMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int r, int c) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

int main() {
	Graph* g = initGraph();			// init graph
	char vertexes[] = { 's', 't', 'y', 'x', 'z' };
	for (int i = 0; i < 5; i++) {	// make 5 vertex
		insert_vertex(g, i, vertexes[i]);
	}

	insert_edge(g, 0, 1, 3);	// s->t
	insert_edge(g, 0, 2, 5);	// s->y
	insert_edge(g, 1, 3, 6);	// t->x
	insert_edge(g, 2, 4, 6);	// y->z
	insert_edge(g, 1, 2, 2);	// t->y
	insert_edge(g, 2, 1, 1);	// y->t
	insert_edge(g, 3, 4, 2);	// x->z
	insert_edge(g, 4, 3, 7);	// z->x
	insert_edge(g, 2, 3, 4);	// y->x
	insert_edge(g, 4, 0, 3);	// z->s

	dijkstra(g, 0);
	
}