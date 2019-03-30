#include "compact.h"

/*Para montarmos o cabeçalho, precisamos de 16 bits, sendo 3 reservados para o lixo, e o resto 
para a árvore, e como o lixo não pode ser maior que 6, sempre usaremos no max 3 bits, logo, no precisamos
de dar shift bit de 13 para a esquerda, com isso basta fazermos uma operação de "ou" para adicionar 
o tamanho da árvore, e então separamos novamente em dois bytes, para adicionar no arquivo*/
void header (FILE *output, unsigned short int trash, int size_tree) {
	
	unsigned short int trash_size_tree = 0;
	trash <<= 13;
	trash_size_tree = trash | size_tree;
	uc byte1, byte2;
	byte1 = trash_size_tree >> 8;
	byte2 = trash_size_tree;
	rewind(output);
	fprintf(output, "%c%c",byte1,byte2);
	fclose(output);
}

/*Coloca o caminho da árvore no arquivo tratando quando uma folha for '*' e '\', para diferenciar-mos
de um nó que não seja folha para a descompactação*/
void put_tree_in_file (Node *tree, FILE *output) {

	if (tree->left == NULL && tree->right == NULL) {
		if (tree->item == '*') {
			fprintf(output,"\\*");
		} else if (tree->item == '\\') {
			fprintf(output,"\\\\");
		} else {
			fprintf(output,"%c",tree->item);
		}
		return;
	} else {
		fprintf(output,"%c",tree->item);
		put_tree_in_file(tree->left, output);
		put_tree_in_file(tree->right, output);
	}
}

/*Recurssão para percorrer a árvore verificando se for um nó folha e for um "*" ou "\"
devemos por definição incrementar o tamanho da árvore pois colocaremos um caracter "\" adicional*/
void tree_size (Node *tree, int *size_tree) {

	if (tree == NULL) {
		return;
	} else {
		if (tree->left == NULL && tree->right == NULL) {
			if(tree->item == '*' || tree->item == '\\') {
				*size_tree += 1;
			}
		}
		*size_tree += 1;
		tree_size(tree->left, size_tree);
		tree_size(tree->right, size_tree);
	}	
}

/*Inicializamos o array de frequências de caracteres com zero, e incrementamos
a frequencia de acordo com o que se recebe do arquivo*/
void read_frequency(int *frequency, FILE *input) {
    int i;
    for(i = 0; i < 256; i++){
        frequency[i] = 0;
    }
    uc caracter = 0;
	while (fscanf(input, "%c",&caracter) != EOF) {
        frequency[caracter] += 1;
    }
	fclose(input);
}


/*Função que recebe o bit atual e "seta" o novo bit na posição a ser adicionado*/
uc set_bit (uc byte, int i) {
	uc mask = 1 << i;
	return mask | byte;
}
/*Nessa função, usamos para compactar o arquivo, nela, precisamos do nosso novo mapeamento e de lermos o arquivo novamente,
então iremos percorrer e adicionar o novo mapeamento em bytes zerados, quando completamos um byte, mandamos para o arquivo.
Começando pelo inicio do byte, decrementamos 1 no size do mapeamento na hash, pois na recursão do novo mapeamento inserimos 
1 a mais. Temos uma verificação para sabermos se sobrou lixo ou não. Verificamos se o bit está setado, dando shift bit de 
sua posição atual, se o numero da divisão por 2 for 1 ele está setado, caso contrario, não está*/
short int set_bits (HASH *hash_table, FILE *input, FILE *output) {
	uc caracter;
	uc byte = 0;
	int i = 7;
	rewind(input);
	bool flag = false;
	while (fscanf(input,"%c", &caracter) != EOF) {
		for (int j = hash_table->table[caracter]->size -1 ; j >= 0; j--) {
			flag = false;
			if(i == -1) {
				fprintf(output,"%c",byte);
				i = 7;
				byte = 0;
				flag = true;
			} 	
			if((hash_table->table[caracter]->bits >> j) % 2 != 0) {
				byte = set_bit(byte, i);
			}
			i -= 1;
		}
	}
	short int trash = 0;
	if (flag == false) { 
		fprintf(output,"%c",byte);
		trash = i + 1;
	} 
	return trash;
}

/*Primeiro é criado a fila de prioridade, monta a árvore, recebemos o novo tamanho da árvore
definimos o novo mapeamento e é colocado em uma hash, separa dois bytes para o cabeçalho
coloca a árvore no arquivo e os novos bytes, depois cria-se o cabeçalho*/
void compact () {
    FILE *input;
    FILE *output;
    char name_file[100];
    
    printf("File name to compress: \n");
    printf("===> ");
    scanf("%s",name_file);
    
    input = fopen(name_file,"rb");
    
    if (input == NULL) {
        printf("Invalid file\n");
        return;
    } 
    int frequency[256];
    read_frequency(frequency,input);
    Heap *heap1 = create_heap();
    int i;
    for (i = 0; i < 256; i++){
        if(frequency[i] != 0){
            Node *new_node = create_node(i,frequency[i]);
            enqueue(heap1, new_node);
        }
    }
    Node *tree = NULL;
    tree = create_tree_compact(heap1);
    int size_tree = 0;
    tree_size (tree, &size_tree);
    HASH *hash_table = create_hash();
    unsigned short bits = 0;
    define_new_bits(tree,hash_table,0,bits);
    uc byte = 0;
    char name_file2[100];
    strcpy(name_file2,name_file);
    strcat(name_file2,".huff");
    output = fopen(name_file2,"wb");
    fprintf(output,"%c%c",byte,byte);
    put_tree_in_file(tree, output);
    input = fopen(name_file,"rb");
    unsigned short int trash;
    trash = set_bits(hash_table,input,output);
    header(output,trash,size_tree);
}