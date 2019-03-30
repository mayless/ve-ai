#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "heap.h"
#include "tree.h"

void create_heap_test()
{
	int i;
	 Heap * heap = create_heap();
	for(i=1;i<256;i++){
		CU_ASSERT_PTR_NULL(heap->data[i]);
	}
	CU_ASSERT_PTR_EQUAL(heap->size, 0);
}

void swap_test()
{
	unsigned char itemA='a',itemB='b';
	long long int freqA='1',freqB='2';

	Node * nodeA = create_node(itemA,freqA);
	Node * nodeB = create_node(itemB,freqB);

	CU_ASSERT_PTR_EQUAL(nodeA->item, itemA);
	CU_ASSERT_PTR_EQUAL(nodeA->frequency, freqA);

	CU_ASSERT_PTR_EQUAL(nodeB->item, itemB);
	CU_ASSERT_PTR_EQUAL(nodeB->frequency, freqB);

	swap(&nodeA,&nodeB);

	CU_ASSERT_PTR_EQUAL(nodeA->item, itemB);
	CU_ASSERT_PTR_EQUAL(nodeA->frequency, freqB);

	CU_ASSERT_PTR_EQUAL(nodeB->item, itemA);
	CU_ASSERT_PTR_EQUAL(nodeB->frequency, freqA);
}

void enqueue_test()
{
	unsigned char itemAux ='B';
	long long int freqAux = 1;
	Heap* heap = create_heap();
	Node* node = create_node(itemAux,freqAux);

	enqueue(heap,node);

    CU_ASSERT_PTR_EQUAL(heap->data[1]->item, itemAux);
	CU_ASSERT_PTR_EQUAL(heap->data[1]->frequency, freqAux);
}

void dequeue_test()
{
        unsigned char itemAux ='B';
	long long int freqAux = 1;
	Heap* heap = create_heap();
	Node* node = create_node(itemAux,freqAux);

    enqueue(heap,node);
    unsigned char itemTop = heap->data[1]->item;
    long long int freqTop = heap->data[1]->frequency;
    Node* nodeDequeue = dequeue(heap);

    CU_ASSERT_PTR_EQUAL(itemTop, nodeDequeue->item);
    CU_ASSERT_PTR_EQUAL(freqTop, nodeDequeue->frequency);
}




int main()
{

    if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    //CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testing heap features",0,0);
    CU_add_test(suite,"create_hash test",create_heap_test);
    CU_add_test(suite,"swap test",swap_test);
    CU_add_test(suite,"enqueue test",enqueue_test);
    CU_add_test(suite,"dequeue test",dequeue_test);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

  return 0;
}
