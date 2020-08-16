#ifndef __ERROR_H__
#define __ERROR_H__

#include <errno.h>

typedef enum errors_s errors_t;

enum errors_s{
	NO_ERR = 0,
	PARAM_NULL = -1,
	DLIST_INCONSISTENT = -2;
};


#endif 
