#ifndef compact_h
#define compact_h

#include "header.h"
#include "hash.h"
#include "tree.h"
#include "heap.h"


void header (FILE *output, unsigned short int trash, int size_tree);

void put_tree_in_file (Node *tree, FILE *output);

void tree_size (Node *tree, int *size_tree);

void read_frequency(int *frequency, FILE *input);

uc set_bit (uc  byte, int i);

short int set_bits (HASH *hash_table, FILE *input, FILE *output);

void compact ();


#endif

