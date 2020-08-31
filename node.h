#ifndef __NODE_H__
#define __NODE_H_


#include <memory.h>
#include <stdlib.h>
#include "error.h"
#include "test_memcmp.h"

typedef struct node_s node_t;
struct node_s{
	int is_dummy; /// indicates if the node is a dummy node for head and tail node for dlist and rear node for queue
	void* data;
	int data_size;
	node_t* prev;
	node_t* next;
};

node_t* node_init();
int node_destroy(node_t* node);
#endif
