#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int item;
    struct node *next;
}Node;

typedef struct heap{
	int size;
	int *data;
}Heap;

void print_queue (Node *priority_queue) {
    Node *cursor = priority_queue;
    while (cursor != NULL) {
        printf("%d ", cursor->item);
        cursor = cursor->next;
    }
    printf("\n");
}

Node *create_node (int number) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->item = number;
    new_node->next = NULL;
    return new_node;
}

Node *priority_queue_list (Node *priority_queue, Node *new_node, FILE *output_queue, int *count) {
    
    
    if (priority_queue == NULL) {
        *count = 1;
        return new_node;
    } else {
        Node *cursor = priority_queue;
        Node *prev;
        if (new_node->item < cursor->item) {
            *count += 1;
            new_node->next = cursor;
            return new_node;
        } else {

            while (cursor != NULL && new_node->item >= cursor->item) {
                *count += 1;
                prev = cursor;
                cursor = cursor->next;
            }
            prev->next = new_node;
            new_node->next = cursor;
            return priority_queue;
        }
    }
}

void swap(int *a, int  *b){

	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}


Heap *create_heap(int size){
	Heap *new_heap = (Heap*)malloc(sizeof(Heap));
	new_heap->data = malloc(size*sizeof(int));
	new_heap->size = 0;
	return new_heap;
}

/*Heap onde os pais são maiores que os filhos*/
void enqueue(Heap *heap, int item, FILE *output_heap, int *count){
	/*Recebe na ultima posição o item atual*/
	heap->data[++heap->size] = item;
    *count = 1;
	/*Recebe o indice do ultimo nó adicionado*/
	int index = heap->size;
	/*Pai no do nó inserido*/
	int parent_index = heap->size/2;
	/*Enquanto o nó inserido for menor que o seu pai, fazer as trocas*/
	while(parent_index >= 1 && heap->data[index] >= heap->data[parent_index]){
        *count += 1;
        swap(&heap->data[index], &heap->data[parent_index]);   
		/*Pai atual será o novo filho*/
		index = parent_index;
		/*Pai do novo filho*/
		parent_index = index/2;
	}
}

int main () {
    FILE *output;
    output = fopen("Datas.txt","w");
    //output_heap = fopen("Heap.txt","w");
    Node *priority_queue = NULL;
    int qnt, item, intervalo, i;
    srand(time(NULL));
    printf("Quantidade de numeros a serem inseridos: \n");
    scanf("%d", &qnt);
    Heap *heap = create_heap(qnt);
    printf("Intervalo maximo: \n");
    scanf("%d", &intervalo);
    fprintf(output,"Hp pq value\n");
    /*Mostrar o pior caso, onde a fila de prioridade sem heap será O(n) e a heap(logn)*/
    /*Inserir de forma aleatória*/
    for (i = 0; i < qnt; i++) {
        item = rand() % intervalo;
        int count_heap = 0;
        int count_pq = 0;
        Node *new_node = create_node(item);
        enqueue(heap,i,output, &count_heap);
        priority_queue = priority_queue_list(priority_queue, new_node,output, &count_pq);
        fprintf(output,"%d %d %d\n", count_heap, count_pq, item);
    }
    printf("Arquivo gerado!\n");
    fclose(output);

    return 0;
}