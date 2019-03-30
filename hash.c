#include "hash.h"

HASH *create_hash () {
	HASH *new_hash = (HASH*)malloc(sizeof(HASH));
	int i = 0;
	for (i = 0; i < 256; i++) {
		new_hash->table[i] = NULL;
	}
	return new_hash;
}

/*Recebemos o novo mapeamento e adicionamos a hash, salvando o seu tamanho, pois
precisamos saber até onde o byte foi usado*/
void put_in_hash(HASH *hash_table, unsigned short int bits, int size_bits, uc item) {

	Element *new_element = (Element*)malloc(sizeof(Element));
	new_element->bits = bits;
	new_element->size = size_bits;
	hash_table->table[item] = new_element;
}

/*Define o novo mapeamento, caminhando pelo árvore, sendo 0 para esquerda e 1 para a direita
fazendo uma operação de shift bit de 1 para a esquerda pra "setarmos" zero quando para a esquerda,
e adicionamos 1 quando para direita*/
void define_new_bits (Node *tree, HASH *hash_table, int i, unsigned short int bits) {

	if (tree->left == NULL && tree->right == NULL) {
		put_in_hash(hash_table, bits, i, tree->item);
		return;
	} else {
		bits <<= 1;
		define_new_bits(tree->left, hash_table, i + 1, bits);
		bits += 1;
		define_new_bits(tree->right, hash_table, i + 1, bits);
	}
}