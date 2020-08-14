#include "node.h"

node_t* node_init(){

	node_t* node = malloc(sizeof(node_t));
	if(node == NULL)
		return NULL;
	memset(node,0,sizeof(node_t));	
	return node
}

int node_destroy(node_t* node){
	if(node ==NULL)
		return -1;
	free(node);
	return 0;
}

int node_get_data(node_t* node){
	if(node == NULL)
		return -1;
	return node->data
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

int node_set_data(node_t* node, int data){
	if(node == NULL)
		return -1;
	node->data = data;
	return 0;
}

int node_set_prev(node_t* node, node_t* prev){
	if(node == NULL)
		return -1;
	node->prev = prev;
	return 0;
}

int node_set_next(node_t* node, node_t* next){
	if(node == NULL)
		return -1;
	node->next = next;
	return 0;
}


