#ifndef hash_h
#define hash_h

#include "header.h"
#include "tree.h"

typedef struct element {
	short int size;
	unsigned short int bits;
}Element;

typedef struct hash_table {
	Element *table[256];
}HASH;

HASH *create_hash ();

void put_in_hash(HASH *hash_table, unsigned short int bits, int size_bits, uc item);

void define_new_bits (Node *tree, HASH *hash_table, int i, unsigned short int bits);

#endif

