#include "dlist_void.h"

int main(){
	int i = 0;
	int rv = NO_ERR;
	//test nodes init
	node_t* test_node1 = node_init();
	if(test_node1 == NULL)
		printf("test_node1 NULL\n");
	node_t* test_node2 = node_init();
	if(test_node2 == NULL)
		printf("test_node2 NULL\n");
	node_t* test_node3 = node_init();
	if(test_node3 == NULL)
		printf("test_node3 NULL\n");
		//store test node addr
	
	//node.c test;
	int d1=1;
	int d2=2;
	int d3=3;
		//node setter test
		//set_data
		node_set_data(test_node1, &d1, sizeof(d1));
		if(rv != NO_ERR)
			printf("set_data, node1, rv :%d\n",rv);
		node_set_data(test_node2, &d2, sizeof(d2));
		if(rv != NO_ERR)
			printf("set_data, node2, rv :%d\n",rv);
		node_set_data(test_node3, &d3, sizeof(d3));
		if(rv != NO_ERR)
			printf("set_data, node3, rv :%d\n",rv);

		//set_prev;
		node_set_prev(test_node2, test_node1);
		if(rv != NO_ERR)
			printf("set_prev, node2, rv :%d\n",rv);
		node_set_prev(test_node3, test_node2);
		if(rv != NO_ERR)
			printf("set_prev, node3, rv :%d\n",rv);
		
		//set_next;
		node_set_next(test_node1, test_node2);
		if(rv != NO_ERR)
			printf("set_next, node1, rv :%d\n",rv);

		node_set_next(test_node2, test_node3);
		if(rv != NO_ERR)
			printf("set_next, node2, rv :%d\n",rv);
		printf("\n@set result@\n");
		node_print_node(test_node1);
		node_print_node(test_node2);
		node_print_node(test_node3);
		// clear node
		rv = node_clear_node(test_node1);
		if(rv != NO_ERR)
			printf("clear node, node1, rv : %d\n", rv);
		rv = node_clear_node(test_node2);
		if(rv != NO_ERR)
			printf("clear node, node2, rv : %d\n", rv);
		rv = node_clear_node(test_node3);												
		if(rv != NO_ERR)
			printf("clear node, node3, rv : %d\n", rv);
		node_print_node(test_node1);
		node_print_node(test_node2);
		node_print_node(test_node3);
		//compare data
		d2 = 1;
		rv = node_compare_data(test_node1, test_node2);
		if(rv != DATA_SAME && rv != DATA_NOT_SAME)
			printf("compare data, node1, node2, data :1, rv : %d\n",rv);
			//compare string
			char* s1=malloc(6);
			char* s2=malloc(7);
			strncpy(s1,"abc",strlen("abc")+1);
			strncpy(s2,"abc",strlen("abc")+1);
			node_set_data(test_node1,s1,strlen(s1)+1);
			node_set_data(test_node2,s2,strlen(s2)+1);
			rv = node_compare_data(test_node1, test_node2);
			if(rv == DATA_SAME || rv == DATA_NOT_SAME)
				printf("compare data, node1, node2, data :\"abc\", rv : %d\n",rv);		
			node_destroy(test_node1);
			node_destroy(test_node2);
			node_destroy(test_node3);
	// end node.c test
		
	//dlist.c test			
}



