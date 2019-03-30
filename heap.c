#include "heap.h"

void swap(Node **a, Node **b){

	Node *aux;
	aux = *a;
	*a = *b;
	*b = aux;
}
/*Função para criar nós, recebendo a frequencia atual e o caracter*/
Node *create_node(char item, lli frequency){
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->item = item;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;
	return new_node;
}
/*Declaramos a heap dinamicamente, e fazemos todos as posições
"apontar" para nulo para depois "apontar para um nó"*/
Heap *create_heap(){
	Heap *new_heap = (Heap*)malloc(sizeof(Heap));
	new_heap->data = (Node**)malloc(256*sizeof(Node*));
	int i;
	for(i=1;i<256;i++){
		new_heap->data[i] = NULL;
	}
	new_heap->size = 0;
	return new_heap;
}


/*Função que verifica três nós, o nó pai, filho da esquerda e flho da direita,
e sempre verificando se esta dentro dos limites do array, o menor nó é trocado pela raiz,
até que ele seja a própria raiz, assim mantemos a propriedade de heap minima*/
void min_heap(Heap *heap, int i){

	int smallest;
	int left_index = 2 * i;
	int right_index = (2 * i) + 1;

	if (left_index <= heap->size && heap->data[left_index]->frequency <= heap->data[i]->frequency) {
		smallest = left_index;
	} else {
		smallest = i;
	}
	if (right_index <= heap->size && heap->data[right_index]->frequency <= heap->data[smallest]->frequency) {
		smallest = right_index;
	}
	if (i != smallest) {
		swap(&heap->data[i], &heap->data[smallest]);
		min_heap(heap,smallest);
	}
}


/*Receber as frequencias para criar a heap, criamos um novo nó e colocamos no fim da heap.
Como precisamos de uma heap mínima, enquanto o novo nó adicionado for menor que seu "pai",
fazemos a troca com o pai*/
void enqueue(Heap *heap, Node *new_node){
	
	heap->data[++heap->size] = new_node;
	int index = heap->size;
	int parent_index = heap->size/2;
	while(parent_index >= 1 && heap->data[index]->frequency <= heap->data[parent_index]->frequency){
        swap(&heap->data[index], &heap->data[parent_index]);   
		index = parent_index;
		parent_index = index/2;
	}
}

/*Função que retira um nó raiz da heap, colocamos o ultimo nó na raiz,
e diminui o tamanho da heap, dessa forma o excluindo, então restauramos 
a propriedade da heap*/
Node *dequeue (Heap *heap) {

	Node *item = heap->data[1];
	heap->data[1] = heap->data[heap->size];
	heap->size--;
	min_heap(heap,1);
	return item;
}