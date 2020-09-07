#pragma once
#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdio.h>
#include "error.h"
#include "node.h"
#include "string.h"
typedef struct dlist_s dlist_t;

struct dlist_s{
	node_t* head;
	node_t* tail;	
};


dlist_t* dlist_init();
int dlist_destroy(dlist_t* dlist);

node_t* dlist_get_head(dlist_t* dlist);
node_t* dlist_get_tail(dlist_t* dlist);

int dlist_set_head(dlist_t* dlist, node_t* node);
int dlist_set_tail(dlist_t* dlist, node_t* node);

int dlist_clear_dlist(dlist_t* dlist);

#endif
