#pragma once
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include "error.h"
#include "node.h"

typedef struct queue_s queue_t;
/**
*@struct queue_s
*@brief struct for queue
*/
struct queue_s{
	node_t* rear; /// rear where node is pushed.
	node_t* front;/// front where node is popped.
};

queue_t* queue_init();
int queue_destroy();
#endif
