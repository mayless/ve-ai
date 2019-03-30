#ifndef heap_h
#define heap_h

#include "header.h"

typedef unsigned char uc;
typedef long long int lli;

typedef struct node{
	//Item deve ser ponteiro para void
	uc item;
	lli frequency;
	struct node *left;
	struct node *right;
}Node;

typedef struct heap{
	int size;
	Node **data;
}Heap;

void swap(Node **a, Node **b);

Node *create_node(char item, lli frequency);

Heap *create_heap();

void min_heap(Heap *heap, int i);

void enqueue(Heap *heap, Node *new_node);

Node *dequeue (Heap *heap);

#endif

