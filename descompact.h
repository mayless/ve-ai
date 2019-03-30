#ifndef descompact_h
#define descompact_h

#include "header.h"
#include "tree.h"
#include "heap.h"


Node *create_tree_descompact (Node *tree, FILE *input);

lli number_of_bytes (FILE *input);

int is_bit_i_set (uc byte, int i);

void put_caracter_in_file (FILE *input, FILE *output, Node *tree, lli number_bytes, unsigned short int trash);

void descompact();

#endif