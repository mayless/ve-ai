COMPACT = compact.h compact.c
DESCOMPACT = descompact.h descompact.c
TREE = tree.h tree.c
HEAP = heap.h heap.c 
HEADER = header.h
HASH = hash.h hash.c
MAIN = huff.c
TEST = Ctest.c

compile_huff:
	gcc $(HEADER) $(HEAP) $(TREE) $(HASH) $(COMPACT) $(DESCOMPACT) $(MAIN) -o huffman 
	
compile_cunit:
	gcc $(TEST) $(TREE) $(HEAP) $(HASH) -o tests -lcunit -w
