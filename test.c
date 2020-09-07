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
			rv = node_destroy(test_node1);
			if(rv != NO_ERR){
				printf("node_destroy rv : %d",rv);
				return -1;	
			}
			rv = node_destroy(test_node2);
			if(rv != NO_ERR){
				printf("node_destroy rv : %d",rv);
				return -1;	
			}
			rv = node_destroy(test_node3);
			if(rv != NO_ERR){
				printf("node_destroy rv : %d",rv);
				return -1;	
			}
			free(s1);
			free(s2);
	// end node.c test
		
	//dlist.c test
	node_t* node_rv;

	dlist_t* dlist = dlist_init();
	if(dlist == NULL){
		printf("dlist_init() NULL\n");
		return -2;
	}
	//dlist_get_head test
	node_rv = dlist_get_head(NULL);
	if(node_rv != NULL)
		printf("dlist_get_head(NULL), node_rv != NULL\n");
	node_rv = dlist_get_head(dlist);			
	if(node_rv == NULL){
		printf("dlist_get_head, node_rv : NULL\n");
	}
	//dlist_get_tail test
	node_rv = dlist_get_tail(NULL);
	if(node_rv != NULL)
		printf("dlist_get_tail(NULL), node_rv != NULL\n");
	node_rv = dlist_get_tail(dlist);			
	if(node_rv == NULL){
		printf("dlist_get_tail, node_rv : NULL\n");
	}
	//delete head node;
	node_destroy(dlist->head);
	dlist->head =NULL;
	//check dlist_check_consistency()
	rv = dlist_check_consistency(NULL);
	if(rv!=PARAM_NULL)
		printf("dlist_check_consistency(NULL), rv != PARAM_NULL\n");
	rv = dlist_check_consistency(dlist);
	if(rv!=DLIST_INCONSISTENT)
		printf("dlist_check_consistency(dlist), dlist->head == NULL, rv != DLIST_INCONSISTENT\n");
	//check dlist_set_head()
	node_t* test_node = node_init();
	test_node->is_dummy = 1;
	dlist_set_head(dlist,test_node);
	node_set_next(dlist->head, dlist->tail);
	node_set_prev(dlist->tail, dlist->head);	
	rv = dlist_check_consistency(dlist);
	if(rv != NO_ERR)
		printf("dlist_check_consistency(dlist), dlist is consistent, rv : %d (rv != NO_ERR)\n",rv);
	printf("dlist setter checked\n");
	//check dlist_insert_node_to_head()/tail() 
	int a=1;
	int b=2;
	printf("&a : %p, &b : %p\n",&a,&b);
	test_node = node_init();
	test_node2 = node_init();
	test_node->data = &a;
	test_node2->data = &b;
	test_node->data_size = 4;
	test_node2->data_size = 4;
	//add test_node to head
	dlist_insert_node_to_head(dlist,test_node);
	//add test_node_to_tail
	dlist_insert_node_to_tail(dlist,test_node2);
	test_node = dlist->head;
	dlist_print_dlist(dlist);
	
	//merge two dlists
	dlist_t* dlist2 = dlist_init();
	if(dlist2 == NULL){
		printf("dlist2 NULL\n");
		return -2;
	}
	test_node3 = node_init();
	node_t* test_node4 = node_init();
	if(test_node3 == NULL || test_node4 == NULL){
		printf("test_node3 || test_node4 == NULL");
	}
	test_node3->data = 3;
	test_node4->data = 4;
	rv = dlist_insert_node_to_tail(dlist2,test_node4);
	if(rv != NO_ERR)
		printf("dlist_insert_node_to_tail, rv : %d\n",rv);
	rv = dlist_insert_node_to_head(dlist2,test_node3);
	if(rv != NO_ERR)
		printf("dlist_insert_node_to_head, rv : %d\n",rv);
	dlist_t* new_dlist = dlist_merge_dlist(dlist, dlist2);
	dlist_print_dlist(new_dlist);
	//check swap node
	rv = dlist_swap_node(new_dlist, new_dlist->head, new_dlist->tail);
	if(rv != NO_ERR)//modifying head and tail using dlist_swap_node() is forbidden.
		printf("dlist_swap_node, rv : %d\n",rv);
	rv = dlist_swap_node(new_dlist, new_dlist->head->next, new_dlist->tail->prev);
	rv = dlist_check_consistency(new_dlist);
	if(rv != NO_ERR)
		printf("dlist_swap_node, rv : %d\n",rv);
	dlist_print_dlist(new_dlist);
	

}
































