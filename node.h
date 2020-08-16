#ifndef __NODE_H__
#define __NODE_H_


#include <memory.h>
#include <stdlib.h>
#include "error.h"

typedef struct node_s node_t;
struct node_s{
	int data;
	node_t* prev;
	node_t* next;
};

node_t* node_init();
int node_destroy(node_t* node);
#endif
