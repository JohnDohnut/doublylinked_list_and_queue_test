#ifndef __ERROR_H__
#define __ERROR_H__

#include <errno.h>

typedef enum errors_s errors_t;

enum errors_s{
	NO_ERR = 0,
	DATA_SAME = 0,
	PARAM_NULL = -1,
	DLIST_INCONSISTENT = -2,
	QUEUE_INCONSISTENT = -2,
	MODIFY_HEAD = -3,
	MODIFY_TAIL = -3,
	SWAP_SAME_NODE = -4,
	NODE_NOT_IN_DLIST = -5,
	NO_NODE_FOUND = -6,
	DATA_NOT_SAME = -7,
	NEGATIVE_SIZE = -8,
	UNKNOWN
};


#endif 
