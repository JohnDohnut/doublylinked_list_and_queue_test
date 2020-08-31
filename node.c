#include "node.h"

node_t* node_init(){

	node_t* node = malloc(sizeof(node_t));
	if(node == NULL)
		return NULL;
	memset(node,0,sizeof(node_t));	
	node->prev = NULL;
	node->next = NULL;
	return node;
}

int node_destroy(node_t* node){
	if(node ==NULL)
		return PARAM_NULL;
	free(node);
	return NO_ERR;
}

void* node_get_data(node_t* node){
	if(node == NULL)
		return NULL;
	return node->data;
}

int node_get_data_size(node_t* node){
	if(node == NULL)
		return PARAM_NULL;
	return node->data_size;
}
node_t* node_get_next(node_t* node){
	if(node == NULL)
		return NULL;
	return node->next;
}

node_t* node_get_prev(node_t* node){
	if(node == NULL)
		return NULL;
	return node->prev;
}

int node_set_data(node_t* node, void* data, int size){
	if(node == NULL)
		return PARAM_NULL;
	node->data = data;
	node->data_size = size;
	return NO_ERR;
}

int node_set_prev(node_t* node, node_t* prev){
	if(node == NULL)
		return PARAM_NULL;
	node->prev = prev;
	return NO_ERR;
}

int node_set_next(node_t* node, node_t* next){
	if(node == NULL)
		return PARAM_NULL;
	node->next = next;
	return NO_ERR;
}

int node_clear_node(node_t* node){
	if(node == NULL)
		return PARAM_NULL;
	memset(node,0,sizeof(node_t));
	return NO_ERR;
}

int node_compare_data(node_t* node1, node_t* node2){
	if(node1 == NULL || node2 == NULL)
		return PARAM_NULL;
	if(node1->data_size != node2->data_size)
		return DATA_NOT_SAME;
	else{
		if(test_memcmp(node1,node2,node1->data_size) != 0)
			return DATA_NOT_SAME;
		return DATA_SAME;
	}
}

void node_print_node(node_t* node){
	if(node == NULL){
		printf("node is NULL\n");
		return;
	}
	else{
		printf("--------node--------\n");
		printf("node addr : %p \n", node);
		printf("is_dummy : %d \n", node->is_dummy);
		printf("data ptr : %p \n", node->data);
		printf("prev : %p\n", node->prev);
		printf("next : %p\n", node->next);
		printf("--------------------\n");
		
	}
}












