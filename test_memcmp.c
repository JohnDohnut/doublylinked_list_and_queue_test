#include "test_memcmp.h"
#include "error.h"
int test_memcmp(void* ptr1, void* ptr2, int size){
	int offset = 0;
	if(size<0)
		return NEGATIVE_SIZE;
	if(ptr1 == NULL || ptr2 == NULL)
		return DATA_NOT_SAME;
	const char* p1 = (const char*) ptr1;
	const char* p2 = (const char*) ptr2;
	while(offset < size){
		if(p1[offset] != p2[offset])
			return DATA_NOT_SAME;
		offset++;
	}
	return DATA_SAME;
}

