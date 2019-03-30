#include "descompact.h"

/*Por ser uma árvore de huffman, ao recriarmos a árvore, sabemos quando um nó é uma folha
pois será diferente de "*", mas preciamos verificar se é realmente o caracter "*" na folha ou 
um "\", que foi definido para diferenciação*/
Node *create_tree_descompact (Node *tree, FILE *input) {
    uc item;
    fscanf(input,"%c", &item);
    if (item != '*') {
        if (item == '\\') {
            fscanf(input,"%c", &item);
        }
        return create_node(item,0);
    } else {
        tree = create_node(item,0);
        tree->left = create_tree_descompact(tree->left,input);
        tree->right = create_tree_descompact(tree->right,input);
    }
    return tree;
}
/*Função para verificar a quantidade de bytes no arquivo, para na descompactação, sabermos
onde é o ultimo byte está e através do lixo do cabeçalho sabermos onde parar*/
lli number_of_bytes (FILE *input) {

	lli count = 0;
	uc byte;
	while (fscanf(input,"%c", &byte) != EOF) {
		count += 1;
	}
	return count;
}
/*Função que recebe o byte atual e verifica em uma determinada posição se ele está "setado"*/
int is_bit_i_set (uc byte, int i) {
	uc mask = 1 << i;
	return mask & byte;
}
/*Função para criarmos o arquivo original, onde a partir dos bytes compactados verificamos bit a bit, e usamos uma
árvore auxiliar para percorremos até chegar em uma folha e adicionar ao arquivo, e no ultimo byte, se tivermos lixo
temos uma condição para trata-lo, e para verificarmos se é o ultimo byte, basta retirar-mos -1 da quantidade de bytes*/
void put_caracter_in_file (FILE *input, FILE *output, Node *tree, lli number_bytes, unsigned short int trash) {
	
	Node *tree_aux = tree;
	uc byte;
	int i;
	for (int j = 0; j < number_bytes; j++) {
		fscanf(input,"%c", &byte);
		if ((j == number_bytes - 1) && trash != 0) {
			for (i = 7; i >= trash; i--) {
			
				if (is_bit_i_set(byte,i)) {
					tree_aux = tree_aux->right;
				} else {
					tree_aux = tree_aux->left;
				}
				if (tree_aux->left ==  NULL && tree_aux->right == NULL) {
					fprintf(output,"%c", (uc)tree_aux->item);
					tree_aux = tree;
				} 	
			}
			break;
		} 
		
		for (i = 7; i >= 0; i--) {
			
			if (is_bit_i_set(byte,i)) {
				tree_aux = tree_aux->right;
			} else {
				tree_aux = tree_aux->left;
			}
			if (tree_aux->left ==  NULL && tree_aux->right == NULL) {
				fprintf(output,"%c", (uc)(tree_aux->item));
				tree_aux = tree;
			} 
		}	
	}
	fclose(output);
	fclose(input);
}

/*Primeiramente recebemos os dois bytes que são o tamanho da árvore e o lixo. Como são apenas 3 bits para
o lixo, e o resto para o tamanho da arvore, então separamos os dois bytes recebidos para o lixo e o tamanho 
da árvore*/
void descompact() {
	FILE *input;
	FILE *output;
	char name_file[100];
	printf("File name to descompress: \n");
	printf("===> ");
	scanf("%s", name_file);
	input = fopen(name_file,"rb");
	if (input == NULL ) {
		printf("Invalid file\n");
		return;
	}
	char name_file_output[100];
	int i;
	for (i = 0; i < strlen(name_file) - 5; i++) {
		name_file_output[i] = name_file[i];
	}
	name_file_output[i] = '\0';
	
	output = fopen(name_file_output,"wb");
	
	unsigned short int size_tree = 0;
	uc byte1, byte2, aux, trash;
	fscanf(input, "%c%c", &byte1, &byte2);
	aux = byte1 << 3;
	size_tree = aux;
	size_tree <<= 5;
	size_tree = size_tree | byte2;
	trash = byte1 >> 5;
	Node *tree = NULL;
	tree = create_tree_descompact(tree, input);
	lli number_bytes = number_of_bytes(input);
	fseek(input, size_tree + 2, SEEK_SET);
	put_caracter_in_file(input,output,tree,number_bytes,trash);
}